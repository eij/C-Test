
typedef union TokenValue {
	int i;

	float f;

	char c;

	char *s;
} TokenValue;

typedef struct Token {
	TokenValue value;

	int type;
} Token;

