NAME = philo

#NAME_BONUS = checker

CC = cc

FLAGS = -Wall -Wextra -Werror -fsanitize=thread

SRC =  philo.c get_time.c parsing.c start_emulation.c atoi.c utils.c


OBJS = ${SRC:.c=.o}



all: ${NAME}

${NAME}: ${OBJS} philo.h Makefile
	${CC} ${FLAGS} ${OBJS} -o ${NAME} 


%.o:%.c
	${CC} ${FLAGS} -c  $< -o $@

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all 

.PHONY: all clean fclean re #bonus