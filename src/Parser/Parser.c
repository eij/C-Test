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
				//	TODO: gentle exit?

				exit(EXIT_SUCCESS);
			}

			case ERROR: {
				exit(EXIT_FAILURE);
			}

			case IDENTIFIER: {
				keyword(t->value);

				break;
			}

		}

		free(t);
	}

	done();
}

void keyword(TokenValue id) {
	if (strcmp("print", id) == 0) __print();
}

static void __print() {
	Token *t = malloc(sizeof(Token));

	TokenValue string;

	t = token();

	if (t->type == STRING) string = t->value;

	t = token();

	if (t->type != SEMICOLON) {
		printf("expected semicolon\n");

		exit(1);
	}
	else
		printf("%s", string);

	free(t);
}

