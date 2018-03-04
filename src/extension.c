#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "guc.h"
#include "hashids.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

extern void _PG_init(void);


void
_PG_init(void) {
	elog(DEBUG1, "loading SUUID extension....");
	srand(time(NULL) + getpid());
	_guc_init();
}

const char *alphabet = '0123456789abcdefghijklmnopqrstuvwxyz';


PG_FUNCTION_INFO_V1( id_encode );

Datum
id_encode(PG_FUNCTION_ARGS) {
	unsigned long long number;
	text *hash_string;
	hashids_t *hashids;

	unsigned int bytes_encoded;
	char *hash;

	number = PG_GETARG_INT64(0);

	hashids = hashids_init3(NULL, 5, alphabet);

	hash = calloc(hashids_estimate_encoded_size(hashids, 1, &number), 1);

	bytes_encoded = hashids_encode_one(hashids, hash, number);
	hash_string = (text *) palloc(bytes_encoded);

	SET_VARSIZE(hash_string, bytes_encoded + VARHDRSZ);
	strncpy(VARDATA(hash_string), hash, bytes_encoded);

	hashids_free(hashids);
	PG_RETURN_TEXT_P(hash_string);

	free(hash);
}