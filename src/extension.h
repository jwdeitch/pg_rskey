#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "guc.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

extern void _PG_init(void);

const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

double likelihood_of_collision(size_t, int);
// https://codereview.stackexchange.com/questions/29198/random-string-generator-in-c
static char * gen_rand_string(char *str, size_t size);
char * generate_token();