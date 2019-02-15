#ifndef DICT_H_ 

#include <stddef.h>

typedef struct hash_table hash_table;

typedef struct hash_fn { 
	int(*hash_insert_data)(hash_table * table, char *key, size_t key_s,
				size_t **data);
	void(*hash_dump)(hash_table table);
	void(*hash_delete_table)(hash_table *table);
} hash_fn;

hash_table *hash_table_new(size_t n_buckets);

#endif //DICT_H_
