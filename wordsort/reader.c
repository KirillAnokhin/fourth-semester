#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "dict.h"

#define READER_BUF_SIZE 1024


int reader_process(hash_table *table, char *buf, size_t buf_s);
/*
{
	char *buf_2 = malloc(READER_BUF_SIZE);
	size_t len;
	size_t *data;
	while (1) {
		len = 1;
		char *ptr_1 = buf;
		char *ptr_2 = buf_2;
		if (isalpha(*ptr)) {
			*ptr_2 = *ptr;
			ptr++;
			ptr_2++;
			len++;
		} else
			*ptr_2 = '\0';
		hash_insert_data(table, buf_2, buf_s, &data);
	} 
	
	while (1) {
		char *ptr = buf;
		if(!isalpha(*ptr))
			*ptr = '\0';
		ptr++;
	}
		
	return 0;
}
*/

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
		//reader_process(table, buf, buf_s - unused);
		if (unused)	
			memmove(buf, buf + buf_s - unused, unused);
	} while (ret);

	return 0;
}
