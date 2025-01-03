#include "debug.h"

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


