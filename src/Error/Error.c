#include <stdio.h>
#include <stdlib.h>

#include "Error.h"

void error(char *message) {
	fprintf(stderr, "[E] %s", message);
}

