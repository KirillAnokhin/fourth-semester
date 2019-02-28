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
	struct hash_fn hash;
	hash_entry **buckets;
	size_t n_buckets;
} hash_table;

int hash_insert_data(hash_table *table, char *key, size_t key_s,
	       		size_t **data);
void hash_delete_table(hash_table *table);
void hash_dump(hash_table *table); 

hash_table *hash_table_new (size_t n_buckets)
{
	hash_table *table = calloc(1, sizeof(hash_table));
	table->n_buckets  = n_buckets;
	table->buckets    = calloc(n_buckets, sizeof(hash_entry*));

	table->hash.insert_data  = hash_insert_data;
	table->hash.dump = hash_dump;
	table->hash.delete_table = hash_delete_table;

	/*
	hash_table_t *ht = hash_table_new(10);
	ht->insert_data(...);
	ht->delete_table(ht);
	*/
	return table;
}

static hash_entry *hash_entry_new (char *key, size_t key_s)
{
	hash_entry *entry = calloc(1, sizeof(hash_entry));
	entry->key = malloc(key_s);
	//entry->data = 1;
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
	// first elem
	if(table->buckets[index] == NULL) {
		hash_entry *en = hash_entry_new(key, key_s);
		if (!en)
			return -1;
		table->buckets[index] = en;
		*data = &en->data;
	// there is an elem
	} else {
		hash_entry *tmp = table->buckets[index];
		while (1) {
			// new and old elems matched
			if (!hash_keys_cmp(key, key_s,
			    		   tmp->key, tmp->key_s)) {	
				*data = &tmp->data;
				return 0; 
			} 
			if (!tmp->next) {
				tmp->next = hash_entry_new(key, key_s);
				*data = &tmp->next->data;
				return 2;
			}
		}
		assert(0);
		return -1;
	}
	return 1;
}

void hash_dump(hash_table *table) 
{
	for (int i = 0; i < table->n_buckets; i++) {
		if (table->buckets[i]) { 
			//hash_entry* en = table->buckets[i];
			printf("[%d] ", i);
			printf("%s data: %lu \n", table->buckets[i]->key, table->buckets[i]->data);
		} else 
			printf("[%d] NULL\n", i);
	}
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
