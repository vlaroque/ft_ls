#include "parse_args.h"
#include "libft.h"
#include <stdlib.h>
#include <assert.h>

const flags L_LLO = 1 << 0; /* long listing option -l */
const flags L_REC = 1 << 2; /* recursive option -R */
const flags L_ALL = 1 << 3; /* all option -a */
const flags L_REV = 1 << 4; /* reverse option -r */
const flags L_TMS = 1 << 5; /* time sort option -a */



bool parse_short_option(environment_t *env, char *option_str)
{
	assert(option_str != NULL);

	for (int i = 0; option_str[i] != '\0'; i++)
	{
		switch (option_str[i])
		{
		case 'l':
			SET_FLAG(env->flags, L_LLO);
			break;
		case 'R':
			SET_FLAG(env->flags, L_REC);
			break;
		case 'a':
			SET_FLAG(env->flags, L_ALL);
			break;
		case 'r':
			SET_FLAG(env->flags, L_REV);
			break;
		case 't':
			SET_FLAG(env->flags, L_TMS);
			break;
		default:
			return false;
		}
	}
	return true;
}

bool parse_args(environment_t *env, int ac, char **av)
{
	bool target_found = false;

	env->root_entries_list.full_path_option = true;

	for (int i = 1; i < ac; i++)
	{
		if (av[i][0] == '-' && av[i][1] == '-')
		{
			if (ft_strcmp(&av[i][2], "recursive") == 0)
				SET_FLAG(env->flags, L_REC);
			else
				return false;
		}
		else if (av[i][0] == '-')
		{
			parse_short_option(env, &av[i][1]);
		}
		else
		{
			entry_list_push_from_weak_path(&env->root_entries_list, av[i]);
			target_found = true;
		}
	}

	if ( !target_found )
		entry_list_push_from_weak_path(&env->root_entries_list, ".");

	if ( env->root_entries_list.first == env->root_entries_list.last )
		env->multiple_files = false;
	else
		env->multiple_files = true;

	if ( IS_FLAG_SET(env->flags, L_TMS) && IS_FLAG_SET(env->flags, L_REV))
		env->comparison_function = compare_by_time_reverse;
	else if ( IS_FLAG_SET(env->flags, L_TMS) )
		env->comparison_function = compare_by_time_more_precise;
	else if ( IS_FLAG_SET(env->flags, L_REV) )
		env->comparison_function = compare_by_name_reverse;
	else
		env->comparison_function = compare_by_name;

	env->first_line = true;

	return true;
}

