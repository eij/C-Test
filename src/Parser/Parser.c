#include <stdio.h>
#include <stdlib.h>

#include "Parser.h"

#define D(string) if (DEBUG == 1) dbg(string);

void parser(const char *filename) {
	init(filename);

	while (1) {
		Token *t = malloc(sizeof(Token));

		t = token();

		switch (t->type) {

			case EOS: {
				D("Done.\n");

				//	TODO: Gentle exit.

				exit(EXIT_SUCCESS);
			}

			case IDENTIFIER: {
				//printf("%s\n", t->value);

				keyword(t->value);

				break;
			}

		}

		//printf("%d\n", t->type);

		free(t);
	}

	done();
}

void keyword(TokenValue id) {
	printf("K: %s\n", id);
}

