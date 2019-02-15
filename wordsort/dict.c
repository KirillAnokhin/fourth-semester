#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "dict.h"

typedef struct hash_entry {
	char  *key;
	size_t key_s;
	size_t data;
	struct hash_entry *next;
} hash_entry;

typedef struct hash_table {
	hash_entry **buckets;
	size_t n_buckets;
} hash_table;

hash_table *hash_table_new (size_t n_buckets)
{
	hash_table *table = calloc(1, sizeof(hash_table));
	table->n_buckets  = n_buckets;
	table->buckets    = calloc(n_buckets, sizeof(hash_entry*));
	return table;
}

static hash_entry *hash_entry_new (char *key, size_t key_s)
{
	hash_entry *entry = calloc(1, sizeof(hash_entry));
	entry->key = malloc(key_s);
	memcpy(entry->key, key, key_s);
	entry->key_s = key_s;
	return entry;
}

static int32_t dl_new_hash (const char *s)
{
	uint32_t h = 5381;

	for (unsigned char c = *s; c != '\0'; c = *++s)
		h = h * 33 + c;
	return h;
}

static inline int hash_keys_cmp(char *key_a, size_t key_a_s,
			        char *key_b, size_t key_b_s)
{
	if (key_a_s != key_b_s)
		return 1;
	return memcmp(key_a, key_b, key_a_s);
}

int hash_insert_data(hash_table *table, char *key, size_t key_s,
	       		size_t **data)
{
	size_t index = dl_new_hash(key) % table->n_buckets;
	if(table->buckets[index] == NULL) {
		hash_entry *en = hash_entry_new(key, key_s);
		if (!en)
			return -1;
		table->buckets[index] = en;
	} else {
		hash_entry *tmp = table->buckets[index];
		while (1) {
			if (!hash_keys_cmp(key, key_s, 
			    		   tmp->key, tmp->key_s)) {
				*data = &tmp->data;
				return 1; 
			} 
			if (!tmp->next) {
				tmp->next = hash_entry_new(key, key_s);
				*data = &tmp->next->data;
				return 0;
			}
		}
	}
	assert(0);
	return -1;
}

void hash_dump(hash_table table) 
{
	for(int i = 0; i < table.n_buckets; i++)
		printf("[%d] %s\n", i, table.buckets[i]->key);	
}

static void hash_delete_data(hash_table *table) 
{
	int count = 0;
	while(count != (table->n_buckets - 1)) {
		if(table->buckets[count]) {
			hash_entry *tmp = table->buckets[count];
			while(1) {
				if(!tmp->next) {	
					free(tmp);
					break;
				} else {
					hash_entry *old_tmp = tmp;
					tmp = tmp->next;
					free(old_tmp);
				}
			}
		}
		count++;
	}
}

void hash_delete_table(hash_table *table)
{
	hash_delete_data(table);
	free(table);
}
