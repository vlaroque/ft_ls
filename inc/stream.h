#ifndef __PRINT_LINE_H
#define __PRINT_LINE_H

#include <stdbool.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

typedef struct stream_out_s
{
	char buffer[BUFF_SIZE];
	size_t head;			/* l'index du \0 de la string actuelle */
	int fd;
} stream_out_t;

stream_out_t *stream_init(int fd);
bool stream_flush(stream_out_t *stream);
bool stream_add_char(stream_out_t *stream, char letter);
bool stream_cat(stream_out_t *stream, char *str);
bool stream_cat_end_of_line(stream_out_t *stream, char *str);
void stream_close(stream_out_t *stream);

#endif /* __PRINT_LINE_H */
