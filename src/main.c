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
#include "print.h"

environment_t g_env = {0};

bool is_last_dir(entry_t *entry)
{
	assert(entry != 0);

	entry = entry->next;
	while (entry != NULL)
	{
		if (S_ISDIR(entry->stats.st_mode))
			return false;
		entry = entry->next;
	}
	return true;
}

int main(int ac, char **av)
{
	if (!parse_args(&g_env, ac, av))
		return 1;

	g_env.stream = stream_init(STDOUT_FILENO);

	entries_list_qsort(g_env.root_entries_list.first,
					   g_env.root_entries_list.last,
					   g_env.comparison_function);

	entry_t *entry = g_env.root_entries_list.first;

	while (entry != NULL)
	{
		if (!S_ISDIR(entry->stats.st_mode))
		{
			g_env.first_line = false;
			if (IS_FLAG_SET(g_env.flags, L_LLO))
				print_long_format_line(entry, &g_env);
			else
				print_normal_format_line(entry, &g_env);
		}
		entry = entry->next;
	}

	entry = g_env.root_entries_list.first;

	while (entry != NULL)
	{
		if (S_ISDIR(entry->stats.st_mode))
		{
			recursive_traversal(entry->full_path, &g_env);
			if (!is_last_dir(entry))
			{
				//stream_cat_end_of_line(g_env.stream, "xxx1");
			}
		}
		entry = entry->next;
	}

	stream_close(g_env.stream);
	entry_list_free(&g_env.root_entries_list);

	return 0;
}
