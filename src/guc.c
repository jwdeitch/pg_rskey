#include "guc.h"

void _guc_init(void) {
	static char *pltcl_start_proc = NULL;

	elog(DEBUG1, "loading GUCs....");
	
	DefineCustomStringVariable("rskey.collision_sensitivity",
							   "grow the key size at this percent chance of colliding random keys",
							   NULL,
							   &pltcl_start_proc,
							   "20",
							   PGC_USERSET,
							   0,
							   NULL,
							   NULL,
							   NULL);
}