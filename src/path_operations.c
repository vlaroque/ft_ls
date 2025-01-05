#include "path_operations.h"

#include <stdlib.h> /* for size_t and NULL */
#include <assert.h> /* for assert */
#include <stdint.h> /* for assert */

#include "libft.h"


void remove_tailing_slashes(char *str)
{
	assert(str != NULL);

	size_t len = ft_strlen(str);

	if (len == 0)
		return;

	size_t last_idx = len - 1;

	while (str[last_idx] == '/')
	{
		str[last_idx] = '\0';
		last_idx--;
	}
}

char *file_path_cat(char *directory_path, char *file_name)
{
	assert(directory_path != NULL);
	assert(file_name != NULL);

	size_t dir_path_len = ft_strlen(directory_path);
	size_t file_name_len = ft_strlen(file_name);

	char *new_str = ft_strnew(dir_path_len + file_name_len + 2);
	if (new_str == NULL)
		return NULL;

	ft_strncpy(new_str, directory_path, dir_path_len);
	remove_tailing_slashes(new_str);
	ft_strncat(new_str, "/", 1);
	ft_strncat(new_str, file_name, file_name_len);

	return new_str;
}

