#ifndef READER_H_
#include "dict.h"

int reader(FILE *stream, hash_table *table);
int reader_process(hash_table *table, char *buf, size_t buf_s);

#endif //READER_H_
