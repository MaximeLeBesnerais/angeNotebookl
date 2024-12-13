CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = phonebook
SRC = src/$(wildcard *.c)
INC = -I include

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) $(INC) -o $(NAME)

clean:
	@rm -f $(NAME)

re: clean all

run:
	@./$(NAME)

crun: clean all run

.PHONY: all clean re run crun
