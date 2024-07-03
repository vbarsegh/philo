NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRC = philo.c parsing.c atoi.c get_time.c utils.c start_emulation.c 

OBJS = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} philo.h Makefile
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

bonus: ${NAME_BONUS}

%.o:%.c
	${CC} ${FLAGS} -c  $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}
re: fclean all

.PHONY: all clean fclean re