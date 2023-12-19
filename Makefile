NAME = philo

CFLAGS = -g -Wall -Werror -Wextra

SRCS = src/main.c\
	src/init.c\
	src/utils.c\
	src/philos.c\
	src/routine.c\
	src/time.c\

CC = gcc

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -g $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

// -fsanitize=thread -g3 meterlo en NAME antes de -g