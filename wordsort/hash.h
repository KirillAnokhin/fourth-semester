#ifndef DICT_H_ 

#include <stddef.h>

struct hash_table;

typedef struct hash_table hash_table;

/* Polymorphic class */
typedef struct dict { 
	int  (*insert_data)(struct dict *dc, char *key, size_t key_s,
		            size_t **data);
	void (*delete_table)(struct dict *dc);
	void (*dump)(struct dict *dc);
} dict;

int hash_insert_data(hash_table *table, char *key, size_t key_s,
			 size_t **data);
void hash_dump(hash_table *table);
void delete_table(hash_table *table);

hash_table *hash_table_new(size_t n_buckets);

#endif //DICT_H_
