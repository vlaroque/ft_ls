#ifndef __PATH_OPERATIONS_H
#define __PATH_OPERATIONS_H

#include <stddef.h>
#include <stdbool.h>


void remove_tailing_slashes(char *str);
char *file_path_cat(char *directory_path, char *file_name);
bool copy_as_single_char_in_printable_filename(char c);


#endif
