#include <stdio.h>
#include <stdlib.h>

#include "Parser/Parser.h"

int main(int argc, char *argv[]) {
	if (argc < 2) return 1;

	parser(argv[1]);

	return 0;
}

