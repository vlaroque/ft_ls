#ifndef __PARSE_ARGS_H
#define __PARSE_ARGS_H

#include <stdbool.h>
#include "entries_list.h"
#include "print_line.h"

typedef int flags;

typedef struct environment_s
{
	entry_list_t root_entries_list;
	flags flags;
	stream_out_t *stream;
	bool multiple_files;
} environment_t;


extern const flags L_LLO;
extern const flags L_REC;
extern const flags L_ALL;
extern const flags L_REV;
extern const flags L_TMS;



#define SET_FLAG(flags, flag) flags = flags | flag
#define IS_FLAG_SET(flags, flag) ( ( flags & flag ) )

bool parse_short_option(environment_t *env, char *option_str);
bool parse_args(environment_t *env, int ac, char **av);

#endif /* __PARSE_ARGS_H */
