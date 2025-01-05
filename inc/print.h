#ifndef __PRINT_H
#define __PRINT_H

#include "entries_list.h"
#include "parse_args.h"

void print_entries_list(entry_list_t *entries, environment_t *env);
void print_long_format_line(entry_t *entry, environment_t *env);
void print_normal_format_line(entry_t *entry, environment_t *env);

#endif /* __PRINT_H */
