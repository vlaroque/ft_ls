#include "files_exploration.h"

#include <stdio.h>	/* for perror() */
#include <dirent.h> /* for DIR opendir and dirent */
#include <assert.h>

#include "libft.h"

#include "entries_list_sort.h"
#include "path_operations.h"
#include "print.h"
#include "print_filename.h"

static bool is_hidden_file(char *filename)
{
	assert(filename != NULL);

	return (filename[0] == '.');
}

static bool explore_directory(char *path, entry_list_t *out_entry_list, environment_t *env)
{
	DIR *dir_ptr = opendir(path);

	if (dir_ptr == NULL)
		return false;

	while (1)
	{
		struct dirent *dirent_ptr = readdir(dir_ptr);

		if (dirent_ptr == NULL)
			break;

		if ( !IS_FLAG_SET(env->flags, L_ALL) && is_hidden_file(dirent_ptr->d_name) )
			continue;

		char *entry_path = file_path_cat(path, dirent_ptr->d_name);
		if (entry_path == NULL)
			return false;

		// no need to free entry_path here, now it was taken by the entry in entry_list
		entry_list_push_from_allocated_path(out_entry_list, entry_path);
	}

	closedir(dir_ptr);
	return true;
}

static void explore_subdirectories(entry_list_t *entries, environment_t *env)
{
	entry_t *one_entry = entries->first;

	while (one_entry != NULL)
	{
		if (ft_strcmp(".", one_entry->filename) == 0 || ft_strcmp("..", one_entry->filename) == 0)
		{
			one_entry = one_entry->next;
			continue;
		}

		if (S_ISDIR(one_entry->stats.st_mode))
		{
			// stream_cat_end_of_line(env->stream, "");

			recursive_traversal(one_entry->full_path, env);
		}

		one_entry = one_entry->next;
	}
}

static void print_dir_access_error(char *path)
{
	const char error_head[] = "ft_ls: cannot open directory '";

	const char error_tail[] = "'";
	char *err_str = ft_strnew(sizeof(error_head) + sizeof(error_tail) + ft_strlen(path) + 1);

	ft_strcat(err_str, error_head);
	ft_strcat(err_str, path);
	ft_strcat(err_str, error_tail);
	perror(err_str);
	ft_strdel(&err_str);
}

void recursive_traversal(char *path, environment_t *env)
{
	entry_list_t entries = {0};

	if (!explore_directory(path, &entries, env))
	{
		print_dir_access_error(path);
		return;
	}

	if (env->first_line == true)
	{
		env->first_line = false;
	}
	else
		stream_cat_end_of_line(env->stream, "");

	
	if (env->multiple_files || IS_FLAG_SET(env->flags, L_REC))
	{
		stream_out_filename(env->stream, path);
		stream_cat_end_of_line(env->stream, ":");
	}

	entries_list_qsort(entries.first, entries.last, env->comparison_function);

	print_entries_list(&entries, env);

	if (IS_FLAG_SET(env->flags, L_REC))
	{
		explore_subdirectories(&entries, env);
	}
	entry_list_free(&entries);
}

// bool explore_initial_entries(entry_list_t)
