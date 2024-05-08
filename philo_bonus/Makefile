NAME = philo_bonus

CC = cc

FLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

SRC = philo_bonus.c parsing_bonus.c atoi_bonus.c get_time_b.c utils_bonus.c start_emulation_bonus.c

OBJS = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} philo_bonus.h Makefile
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

%.o:%.c
	${CC} ${FLAGS} -c  $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re