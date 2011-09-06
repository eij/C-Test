#include <stdio.h>
#include <stdlib.h>

#include "Reader.h"

FILE *handle;

void open(const char *filename) {
	handle = fopen(filename, "r");

	if (!handle) {
		printf("File not found.\n");

		exit(1);
	}
}

void close() { fclose(handle); }

char next() { return fgetc(handle); }

void prev(char c) { ungetc(c, handle); }

