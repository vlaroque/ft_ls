#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include "entries_list.h"
#include "path_operations.h"
#include "print_filename.h"
#include "libft.h"

void debug_entry_list(entry_list_t *list)
{
	printf("debugging entry list\n");

	entry_t *entry = list->first;

	while ( entry != NULL )
	{
		printf("\tEntry file '%s' path '%s'\n", entry->filename, entry->full_path);
		if (entry->next != NULL)
			assert(entry->next->prev == entry);

		entry = entry->next;
	}
}

static bool entry_list_push_entry(entry_list_t *list, entry_t *entry)
{
	assert(list != NULL);
	assert(entry != NULL);

	if ( list->first == NULL )
	{
		list->first = entry;
		list->last = entry;
		return true;
	}
	entry_t *first_elem = list->first;
	list->first = entry;
	entry->next = first_elem;

	first_elem->prev = entry;
	return true;
}

static char *find_file_name(char *full_path)
{
	assert(full_path != NULL);

	size_t len = ft_strlen(full_path);
	int cursor = (int)len - 1;

	if (full_path[cursor] == '/')
		cursor--;

	while (cursor >= 0)
	{
		if (full_path[cursor] == '/')
			return &full_path[cursor + 1];

		cursor--;
	}

	return full_path;
}

bool entry_list_push_from_allocated_path(entry_list_t *list, char *path)
{
	assert(list != NULL);
	assert(path != NULL);

	struct stat tmp_stats = {0};

	errno = 0;
	if (lstat(path, &tmp_stats) != 0)
	{
		printf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return false;
	}

	entry_t *new_entry = malloc(sizeof(entry_t));

	if ( new_entry == NULL )
		return false; // to manage this one !

	new_entry->full_path = NULL;
	new_entry->filename = NULL;
	new_entry->printable_filename = NULL;
	new_entry->next = NULL;
	new_entry->prev = NULL;
	new_entry->stats = tmp_stats;
	new_entry->full_path = path;
	new_entry->filename = find_file_name(new_entry->full_path);
	if ( new_entry->filename == NULL )
	{
		free(new_entry);
		return false;
	}
	new_entry->printable_filename = dump_escaped_filename(new_entry->filename);
	if ( new_entry->printable_filename == NULL )
	{
		free(new_entry->full_path);
		free(new_entry);
		return false;
	}

	entry_list_push_entry(list, new_entry);

	return true;
}

bool entry_list_push_from_weak_path(entry_list_t *list, char *path)
{
	char *allocated_str = ft_strdup(path);

	if ( allocated_str == NULL)
		return false;

	return ( entry_list_push_from_allocated_path(list, allocated_str));
}

bool entry_list_is_empty(entry_list_t *list)
{
	if ( ((list->first == NULL) && (list->last != NULL)) || ((list->first == NULL) && (list->last != NULL)))
		assert(false);

	if ( list->first == NULL )
		return true;

	return false;
}

void entry_list_free(entry_list_t *entry_list)
{
	assert( entry_list != NULL);

	entry_t *entry = entry_list->first;

	while ( entry != NULL )
	{
		free(entry->full_path);
		free(entry->printable_filename);
		entry_t *entry_to_free = entry;
		entry = entry->next;
		free(entry_to_free);
	}
}
