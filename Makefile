BIN	:=	2D_Runner

SRC :=	main.c		\
		window.c	\
		main_menu.c

OBJ :=	$(SRC:.c=.o)

CC	:=	gcc

CFLAGS	:=	-Wall -Wextra

RAYFLAGS	:=	-pthread -lGL -lraylib -lm -ldl -fPIC

all: ${BIN}

${BIN}:	${OBJ}
	$(CC) -o $@ $^ $(CFLAGS) $(RAYFLAGS)

clean:
	rm -f *.o

fclean:	clean
	rm -f ${BIN}

re:	fclean all

.PHONY: all fclean re

.SILENT: clean fclean