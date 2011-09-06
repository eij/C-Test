#include "../Data/Parameters.h"
#include "../Reader/Reader.h"

#include "../Debug/Debug.h"
#include "../Error/Error.h"

#include "../Token/Token.h"
#include "../Token/Code.h"

void init(const char *);

void done();

Token *token();

static Token *make_token(int, TokenValue);

static Token *identifier(char);

static Token *string(char);

static Token *variable();

static Token *number(char);

