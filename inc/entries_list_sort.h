#ifndef __ENTRIES_LIST_SORT_H
#define __ENTRIES_LIST_SORT_H

#include <stdlib.h>
#include "entries_list.h"

typedef int (*cmp_func_t)(entry_t *, entry_t *);

bool entries_list_qsort(entry_t *low, entry_t *high, cmp_func_t cmp);
int compare_by_name(entry_t *entry_a, entry_t *entry_b);

#endif /* __ENTRIES_LIST_SORT_H */
