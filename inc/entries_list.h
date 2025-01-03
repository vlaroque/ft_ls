#ifndef __ENTRIES_LIST_H
#define __ENTRIES_LIST_H

#include <sys/stat.h> 
#include <stdbool.h> 

typedef struct entry_s entry_t;

typedef struct entry_s
{
	char *filename;
	char *full_path;       /* allocated string */
	struct stat stats;
	entry_t* prev;
	entry_t* next;
} entry_t;

typedef struct entry_list_s
{
	entry_t *first;
	entry_t *last;
} entry_list_t;


void debug_entry_list(entry_list_t *list);
bool entry_list_push_from_allocated_path(entry_list_t *list, char *path);
bool entry_list_push_from_weak_path(entry_list_t *list, char *path);
bool entry_list_is_empty(entry_list_t *list);

#endif /* __ENTRIES_LIST_H */
