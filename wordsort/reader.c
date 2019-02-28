#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "dict.h"

#define READER_BUF_SIZE 1024


int reader_process(hash_table *table, char *buf, size_t buf_s)
{
	char *buf_2 = malloc(READER_BUF_SIZE);
	char *ptr_1 = buf;
	char *ptr_2 = buf_2;
	size_t len = 0;
	size_t *data;


	for (ptr_1 = buf; ptr_1 <= buf + buf_s && (*ptr_1 != '\0'); ptr_1++) {
		if (isalpha(*ptr_1)) {
			*ptr_2 = *ptr_1;
			ptr_2++;
			len++;
		} else {
			*ptr_2 = '\0';
			len++;
			ptr_2 = buf_2;
			int hash_case = hash_insert_data(table, ptr_2, len, &data);
			if (hash_case != -1)
				(*data)++;
			else 
				return -1;
			len = 0;
		}
	}			
	return 0;
}


int reader(FILE *stream, hash_table *table) 
{
	char *buf = malloc(READER_BUF_SIZE);
	size_t unused = 0;
	size_t ret;
	do {
		ret = fread(buf + unused, 1, READER_BUF_SIZE - unused, stream);
		size_t buf_s = ret + unused;
		unused = 0;
		for (char *tmp = buf + buf_s;
	             isalpha(*tmp) && tmp <= buf; tmp--)
			unused++;
		if(reader_process(table, buf, buf_s - unused) == -1)
			return -1;
		if (unused)	
			memmove(buf, buf + buf_s - unused, unused);
	} while (ret);

	return 0;
}
