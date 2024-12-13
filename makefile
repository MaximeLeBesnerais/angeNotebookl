CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = phonebook
SRC = $(wildcard *.c)

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -f $(NAME)

re: clean all

run:
	@./$(NAME)

crun: clean all run

.PHONY: all clean re run crun
