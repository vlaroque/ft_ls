#include <stdbool.h>
#include <sys/types.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "libft.h"

#include "entries_list.h"
#include "stream.h"
#include "parse_args.h"
#include "files_exploration.h"

environment_t g_env = {0};

int main(int ac, char **av)
{
	if (!parse_args(&g_env, ac, av))
		return 1;

	g_env.stream = stream_init(STDOUT_FILENO);

	entry_t *entry = g_env.root_entries_list.first;

	while (entry != NULL)
	{
		recursive_traversal(entry->full_path, &g_env);
		entry = entry->next;
		if (entry != NULL)
		{
			stream_cat_end_of_line(g_env.stream, "");
		}
	}

	stream_close(g_env.stream);

	return 0;
}
