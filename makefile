# Projekt: League of Legends štatistiky
# Autor:   Daniel Pitek

CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = lolstatsproj.c nacitat.c html.c
OBJ = $(SRC:.c=.o)
HLAVNY = lolstats

$(HLAVNY): $(OBJ)
	$(CC) $(OBJ) -o $(HLAVNY) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(HLAVNY)

rebuild: 
	clean $(HLAVNY)
