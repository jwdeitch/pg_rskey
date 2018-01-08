#include "extension.h"

void
_PG_init(void) {
	elog(DEBUG1, "loading RSKEY extension....");
	srand(time(NULL) + getpid());
	_guc_init();
}

char *
generate_token(size_t desired_str_length, int collision_sensitivity) {

	if (likelihood_of_collision(12, 12)) {
		char *test_key = palloc0(sizeof(char) * desired_str_length);
		gen_rand_string(test_key, desired_str_length);
		printf("trying -- %s \r\n", test_key);
	}
}

static char *
gen_rand_string(char *str, size_t size) {
	if (size) {
		--size;
		for (size_t n = 0; n < size; n++) {
			long key = random() % (int) (sizeof charset - 1);
			str[n] = charset[key];
		}
		str[size] = '\0';
	}
	return str;
}

double
likelihood_of_collision(size_t key_length_count, int record_count) {
	return (record_count / pow(sizeof(charset), key_length_count)) * 100;
}
