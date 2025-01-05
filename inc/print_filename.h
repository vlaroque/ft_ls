#ifndef __PRINT_FILENAME_H
#define __PRINT_FILENAME_H

#include <stddef.h>

typedef enum quote_type_e
{
	NONE_QUOTE,
	SIMPLE_QUOTES,
	DOUBLE_QUOTES
} quote_type_t;

typedef struct to_printable_s
{
	char *printable;
	size_t len;
	quote_type_t quote_type;
} to_printable_t;

to_printable_t *give_printable_for_char(char c);

#endif /* __PRINT_FILENAME_H */ 
