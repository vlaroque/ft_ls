#ifndef __PRINT_FILENAME_H
#define __PRINT_FILENAME_H

#include <stddef.h>
#include "stream.h"

char *dump_escaped_filename(char *original_filename);
void stream_out_filename(stream_out_t *stream, char *full_path);

#endif /* __PRINT_FILENAME_H */ 

