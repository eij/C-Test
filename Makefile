#CFLAGS = -g -O2 -fpcc-struct-return -freg-struct-return

all:
	gcc \
		src/Token/Token.h \
		src/Debug/Debug.h \
		src/Debug/Debug.c \
		src/Error/Error.h \
		src/Error/Error.c \
		src/Reader/Reader.h \
		src/Reader/Reader.c \
		src/Lexer/Lexer.h \
		src/Lexer/Lexer.c \
		src/Parser/Parser.h \
		src/Parser/Parser.c \
		src/Main.c \
		$(CFLAGS) \
		-o t

