#ifndef __ENTRIES_LIST_H
#define __ENTRIES_LIST_H

#include <sys/stat.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct entry_s entry_t;

typedef struct entry_s
{
	char *full_path; /* allocated string */
	char *filename;
	char *printable_filename;
	struct stat stats;
	entry_t *prev;
	entry_t *next;
	bool full_path_option;
} entry_t;

typedef struct entry_list_s
{
	entry_t *first;
	entry_t *last;
	uint64_t directory_size;
	bool full_path_option;
} entry_list_t;

void debug_entry_list(entry_list_t *list);
bool entry_list_push_from_allocated_path(entry_list_t *list, char *path);
bool entry_list_push_from_weak_path(entry_list_t *list, char *path);
bool entry_list_is_empty(entry_list_t *list);
void entry_list_free(entry_list_t *entry_list);

#endif /* __ENTRIES_LIST_H */
