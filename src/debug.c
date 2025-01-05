#include "debug.h"
#include "parse_args.h"
#include <dirent.h>
#include <stdio.h>

char *d_type_to_str(unsigned char type)
{
	switch (type)
	{
		case DT_BLK:
			return "blocks perif";

		case DT_CHR:
			return "caracters perif";

		case DT_DIR:
			return "directory";

		case DT_FIFO:
			return "fifo";

		case DT_LNK:
			return "link";

		case DT_REG:
			return "regular";

		case DT_SOCK:
			return "socket";

		case DT_UNKNOWN:
			return "unknown";

		default:
			return "error"; 
	}
}

void debug_env(environment_t *env)
{
	printf("long_list = %b\n", IS_FLAG_SET(env->flags, L_LLO));
	printf("recursive = %b\n", IS_FLAG_SET(env->flags, L_REC));
	printf("all       = %b\n", IS_FLAG_SET(env->flags, L_ALL));
	printf("reverse   = %b\n", IS_FLAG_SET(env->flags, L_REV));
	printf("time sort = %b\n", IS_FLAG_SET(env->flags, L_TMS));
	printf("muliple_files = %b\n", env->multiple_files);
	debug_entry_list(&env->root_entries_list);
}

void debug_entry_list(entry_list_t *list)
{
	printf("debugging entry list\n");

	entry_t *entry = list->first;

	while ( entry != NULL )
	{
		printf("\tEntry file '%s' path '%s'\n", entry->filename, entry->full_path);
		if (entry->next != NULL)
			assert(entry->next->prev == entry);

		entry = entry->next;
	}
}
