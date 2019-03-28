#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

//#include "dict.h"
#include "reader.h"

int main(int argc, char* argv[])
{
	size_t n_buckets = 10;
	//dict *dict = hash_table_new(n_buckets);
	hash_table *table = hash_table_new(n_buckets);
	FILE *stream;
	stream = fopen("test_read", "r");
	if (reader(stream, table) == -1) {
		printf("reader error\n");
		return -1;
	}
	hash_dump(table);
	fclose(stream);
	return 0;
}
