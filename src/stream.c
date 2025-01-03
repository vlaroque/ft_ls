#include <unistd.h>
#include <assert.h>
#include "stream.h"
#include "libft.h"

stream_out_t *stream_init(int fd)
{
	if ( fd < 0 )
		return NULL;

	static stream_out_t stream = {0};
	ft_bzero(&stream, sizeof(stream));
	stream.fd = fd;

	return &stream;
}

bool stream_flush(stream_out_t *stream)
{
	if ( write(stream->fd, stream->buffer, stream->head) == -1 )
		return false;

	ft_bzero(stream->buffer, stream->head);
	stream->head = 0;

	return true;
}

bool stream_add_char(stream_out_t *stream, char letter)
{
	if ( stream->head >= BUFF_SIZE -1 )
	{
		if ( !stream_flush(stream) )
			return false;
	}

	stream->buffer[stream->head] = letter;
	stream->head++;

	return true;
}

bool stream_cat(stream_out_t *stream, char *str)
{
	if ( str == NULL )
		return false;
	
	size_t len = ft_strlen(str);
	/* case string > buffer size */
	if ( len >= BUFF_SIZE )
	{
		if ( !stream_flush(stream) )
			return false;

		if ( write(stream->fd, stream->buffer, len) == -1 )
			return false;
		
		return true;
	}
	else if ( len + stream->head >= BUFF_SIZE )
	{
		if ( !stream_flush(stream) )
			return false;
	}

	ft_strncpy( stream->buffer + stream->head, str, len);
	stream->head += len;

	return true;
}

bool stream_cat_end_of_line(stream_out_t *stream, char *str)
{
	assert(stream != NULL);
	assert(str != NULL);
	
	if ( !stream_cat(stream, str)
	     || !stream_add_char(stream, '\n')
	     || !stream_flush(stream) )
	{
		return false;
	}

	return true;
}

void stream_close(stream_out_t *stream)
{
	assert (stream != NULL);
	stream_flush(stream);
}
