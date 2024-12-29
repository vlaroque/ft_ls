typedef int flags;

const flags L_LLO = 1 << 0; /* long listing option -l */
const flags L_REC = 1 << 2; /* recursive option -R */
const flags L_ALL = 1 << 3; /* all option -a */
const flags L_REV = 1 << 4; /* reverse option -r */
const flags L_TMS = 1 << 5; /* time sort option -a */

#define SET_FLAG(flags, flag) flags = flags | flag
#define IS_FLAG_SET(flags, flag) ( flags & flag )

