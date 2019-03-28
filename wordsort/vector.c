typedef struct vector_entry {
	size_t data;
	char *word;
	size_t word_s;
} vector_entry;

typedef struct vector {
	size_t n_entries;
	vector_entry *arr;
	size_t arr_s;
} vector;

vector *vector_new (size_t arr_s)
{
	vector *vec = calloc(1, sizeof(vector));
	vec->arr_s  = arr_s;
	vec->arr = calloc(arr_s, sizeof(vector_entry));

	return vec;
}

static vector_entry *vector_entry_new (char *word, size_t word_s)
{
	vector_entry *entry = calloc(1, sizeof(vector_entry));
	entry->word = malloc(word_s);
	memcpy(entry->word, word, word_s);
	entry->word_s = word_s;

	return entry;
}

int vector_insert_data(vector *vec, char* word, size_t word_s)
{
	if(vec->arr_s > vec->n_entries++)
		return -1;
	vector_entry *entry = vec->arr[n_entries];
	entry->word = malloc(word_s);
	memcpy(entry->word, word, word_s);

	return 0;	
}


