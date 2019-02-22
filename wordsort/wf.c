#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include <stddef.h>

int main(int argc, char* argv[])
{
	size_t p;
	size_t *data;
	size_t n_buckets = 8;
	hash_table *table = hash_table_new(n_buckets);
	hash_insert_data(table, "string", sizeof("string"), &data);
	hash_insert_data(table, "string", sizeof("string"), &data);
	hash_insert_data(table, "string", sizeof("string"), &data);
	hash_dump(table);
	return 0;
}
