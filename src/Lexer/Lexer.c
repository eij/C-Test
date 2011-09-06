#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "Lexer.h"

#define D(string) if (DEBUG >= 2) dbg(string);

int line = 0;

void init(const char *filename) { open(filename); }

Token *token() {
	char t;

	scan:

	t = next();

	switch (t) {
		//	EOF

		case EOF: return make_token(0, (TokenValue)EOF);

		//	Newline

		case '\n':
			line++;

			goto scan;

		//	Junk

		case ' ': case '\t': case '\r': case '\v': case '\f':
			goto scan;

		//	Comment

		case '#': {
			while ((t = next()) != EOF) {
				if (t == '\n') {
					line++;

					break;
				}
			}

			goto scan;
		}

		//	String

		case '"': case '\'': {
			D(" STR");

			return string(t);
		}

		//	Variable

		case '$': {
			D(" VAR");

			return variable();
		}

		//	Symbol

		case '=': {
			D(" =");

			return make_token(ASSIGN, (TokenValue)t);
		}

		case '(': {
			D(" (");

			return make_token(LPAREN, (TokenValue)t);
		}

		case ')': {
			D(" )");

			return make_token(RPAREN, (TokenValue)t);
		}

		case '{': {
			D(" {");

			return make_token(LBRACE, (TokenValue)t);
		}

		case '}': {
			D(" }");

			return make_token(RBRACE, (TokenValue)t);
		}

		case '[': {
			D(" [");

			return make_token(LBRACKET, (TokenValue)t);
		}

		case ']': {
			D(" ]");

			return make_token(RBRACKET, (TokenValue)t);
		}

		case ',': {
			D(",");

			return make_token(COLON, (TokenValue)t);
		}

		case ';': {
			D(";\n");

			return make_token(SEMICOLON, (TokenValue)t);
		}

		//	Operational

		case '+': {
			D(" +");

			return make_token(PLUS, (TokenValue)t);
		}

		case '-': {
			D(" -");

			return make_token(MINUS, (TokenValue)t);
		}

		case '*': {
			D(" *");

			return make_token(STAR, (TokenValue)t);
		}

		case '/': {
			D(" /");

			return make_token(SLASH, (TokenValue)t);
		}

		case '%': {
			D(" %");

			return make_token(MODULE, (TokenValue)t);
		}

		case '>': {
			D(" >");

			return make_token(MAJOR, (TokenValue)t);
		}

		case '<': {
			D(" <");

			return make_token(MINOR, (TokenValue)t);
		}

		default: {
			if (isalpha(t) || t == '_') {
				D(" ID");

				return identifier(t);
			}

			else if (isdigit(t)) {
				D(" NUM");

				return number(t);
			}
		}
	}
}

void done() { close(); }

static Token *make_token(int type, TokenValue value) {
	Token *t = malloc(sizeof(Token));

	t->type = type;

	t->value.s = malloc(sizeof(value.s));

	t->value.s = value.s;

	return t;
}

static Token *identifier(char t) {
	char buffer[ID_NAME_LIMIT]; size_t size = 0;

	do {
		if (!isalpha(t) && !isdigit(t) && t != '_') {
			buffer[size++] = '\0';

			break;
		}

		buffer[size++] = t;
	}

	while ((t = next()) != EOF);

	return make_token(IDENTIFIER, (TokenValue)buffer);
}

static Token *string(char delimiter) {
	char *buffer; size_t size = 0; size_t buffer_size = 50;

	buffer = malloc(buffer_size);

	char t;

	while ((t = next()) != EOF) {
		if (t == delimiter) {
			buffer[size++] = '\0';

			break;
		}

		if (size >= buffer_size) {
			char *tmp;

			buffer_size *= 2;

			tmp = realloc(buffer, buffer_size);

			if (tmp == NULL) {
				free(buffer);
				free(tmp);

				printf("out of mem\n");

				exit(1);
			}

			buffer = tmp;
		}

		buffer[size++] = t;
	}

	return make_token(STRING, (TokenValue)buffer);
}

static Token *variable() {
	char buffer[VAR_NAME_LIMIT]; size_t size = 0;

	char t;

	while ((t = next()) != EOF) {
		if (!isalpha(t) && !isdigit(t) && t != '_') {
			buffer[size++] = '\0';

			prev(t);

			break;
		}

		buffer[size++] = t;
	}

	return make_token(VARIABLE, (TokenValue)buffer);
}

static Token *number(char t) {
	char buffer[50]; int size = 0;

	do {
		if (!isdigit(t) && t != '.') {
			buffer[size++] = '\0';

			prev(t);

			break;
		}

		buffer[size++] = t;
	}

	while ((t = next()) != EOF);

	return make_token(INTEGER, (TokenValue)buffer);
}

