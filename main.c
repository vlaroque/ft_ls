#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

typedef struct environment_s
{
	char *path;
	bool long_listing_option; /* -l */
	bool recursive_option;    /* -R */
	bool all_option;          /* -a */
	bool reverse_option;      /* -r */
	bool time_sorting_option; /* -t */
} environment_t;

environment_t g_env = {0};

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

bool parse_args(environment_t *env, int ac, char **av)
{
	environment_t res = {0};

	res.path = ".";

	for (int i = 1; i < ac; i++)
	{
		if ( av[i][0] == '-' && av[i][1] == '-' )
		{
			if ( strcmp(&av[i][2], "recursive") == 0 )
				res.recursive_option = true;
			else
				return false;
		}
		else if ( av[i][0] == '-' )
		{
			for (int j = 1; av[i][j] != '\0'; j++)
			{
				switch (av[i][j])
				{
					case 'l':
						res.long_listing_option = true;
						break;
					case 'R':
						res.recursive_option = true;
						break;
					case 'a':
						res.all_option = true;
						break;
					case 'r':
						res.reverse_option = true;
						break;
					case 't':
						res.time_sorting_option = true;
						break;
					default:
						return false;
				}
			}
		}
		else
		{
			res.path = av[i];
		}
	}

	*env = res;

	return true;
}

void 

int main(int ac, char **av)
{
	if ( !parse_args(&g_env, ac, av) )
		return 1;

	printf("beacon\n");
	printf("long_list = %b\n", g_env.long_listing_option);
	printf("recursive = %b\n", g_env.recursive_option);
	printf("path = %s\n", g_env.path);
	DIR *dir_ptr;
	dir_ptr = opendir(g_env.path);
	while (1)
	{
		struct dirent *dirent_ptr = readdir(dir_ptr);
		if (dirent_ptr == NULL)
			break;
		printf("'%s' type = '%s'\n", dirent_ptr->d_name, d_type_to_str(dirent_ptr->d_type) );
	}

	return 0;
}
