#ifndef DICT_H_ 

#include <stddef.h>

struct hash_table;

typedef struct hash_table hash_table;


typedef struct hash_fn { 
	int  (*insert_data)(hash_table * table, char *key, size_t key_s,
				size_t **data);
	void (*dump)(hash_table *table);
	void (*delete_table)(hash_table *table);
} hash_fn;

/*
table.hash_insert_data()
*/

int hash_insert_data(hash_table *table, char *key, size_t key_s,
			 size_t **data);
void hash_dump(hash_table *table);
void delete_table(hash_table *table);

hash_table *hash_table_new(size_t n_buckets);

#endif //DICT_H_
