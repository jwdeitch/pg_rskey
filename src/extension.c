#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "guc.h"
#include "hashids.h"
#include "commands/sequence.h"
#include "utils/varlena.h"

PG_MODULE_MAGIC;

extern void _PG_init(void);

void
_PG_init(void) {
	elog(DEBUG1, "loading SUUID extension....");
	_guc_init();
}

#define DEFAULT_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                         "1234567890"


PG_FUNCTION_INFO_V1(suuid_in);
PG_FUNCTION_INFO_V1(suuid_out);
PG_FUNCTION_INFO_V1(id_encode);

Datum id_encode(PG_FUNCTION_ARGS);
Datum suuid_in(PG_FUNCTION_ARGS);
Datum suuid_out(PG_FUNCTION_ARGS);

Datum
id_encode(PG_FUNCTION_ARGS) {
	unsigned long long number;
	text *hash_string;
	hashids_t *hashids;

	unsigned int bytes_encoded;
	char *hash;

	number = DirectFunctionCall1(nextval, CStringGetTextDatum("suuid_sequence"));

	hashids = hashids_init3("", 5, DEFAULT_ALPHABET);

	hash = calloc(hashids_estimate_encoded_size(hashids, 1, &number), 1);

	bytes_encoded = hashids_encode_one(hashids, hash, number);
	hash_string = (text *) palloc(bytes_encoded);

	SET_VARSIZE(hash_string, bytes_encoded + VARHDRSZ);
	strncpy(VARDATA(hash_string), hash, bytes_encoded);

	hashids_free(hashids);
	
	PG_RETURN_TEXT_P(hash_string);

	free(hash);
}

Datum
suuid_in(PG_FUNCTION_ARGS) {
	DirectFunctionCall1(id_encode, NULL);
}

Datum
suuid_out(PG_FUNCTION_ARGS) {
	DirectFunctionCall1(id_encode, NULL);
}