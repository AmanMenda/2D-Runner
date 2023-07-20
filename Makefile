BIN	:=	2D_Runner

SOURCES  :=	Sources

SRC :=	$(SOURCES)/main.c		\
		$(SOURCES)/window.c		\
		$(SOURCES)/main_menu.c

OBJ :=	$(SRC:.c=.o)

CC	:=	gcc

CFLAGS	:=	-Wall -Wextra

RAYFLAGS	:=	-pthread -lGL -lraylib -lm -ldl -fPIC

all: ${BIN}

${BIN}:	${OBJ}
	$(CC) -o $@ $^ $(CFLAGS) $(RAYFLAGS)

clean:
	rm -f $(SOURCES)/*.o

fclean:	clean
	rm -f ${BIN}

re:	fclean all

.PHONY: all fclean re

.SILENT: clean fclean