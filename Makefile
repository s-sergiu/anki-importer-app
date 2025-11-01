# binary name
NAME=	anki-importer

# variables
SHELL=	/bin/sh
VPATH=

# flags
CFLAGS=		-Wall -Werror -Wextra -Iinclude

# libraries
SUBDIRS=	

# object files
OBJ=	$(NAME).o \
		gui.o \
		scraper.o \
		struct.o \
		parser.o

# rules
all: $(NAME)

$(NAME): $(OBJ) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lcurl -lraygui

clean: 
	$(RM) $(OBJ)

fclean: clean 
	$(RM) $(NAME)

re: clean all

# special built-in targets
.PHONY: all check clean fclean re
