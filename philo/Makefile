ifeq ($(OS), Windows_NT)
	DIRSEP	= \\
	CP		= copy
	RM		= del -f
else
	DIRSEP	= /
	CP		= cp
	RM		= rm -f
endif

NAME		= philo

SRCS		= src${DIRSEP}converter.c \
			src${DIRSEP}main.c \
			src${DIRSEP}manager.c \
			src${DIRSEP}parsing.c \
			src${DIRSEP}philo.c \
			src${DIRSEP}philo_utils.c \
			src${DIRSEP}utils.c

OBJ_PATH	= obj${DIRSEP}

OBJ_NAME	= ${SRCS:%.c=%.o}

OBJS		= ${addprefix ${OBJ_PATH}, ${OBJ_NAME}}

CC			= gcc

HEAD		= include

CFLAGS		= -I ${HEAD} -Wall -Wextra -Werror

${OBJ_PATH}%.o : %.c
	mkdir -p ${@D} 2> ${DIRSEP}dev${DIRSEP}null || true
	${CC} ${CFLAGS} -o $@ -c $<

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all: ${NAME}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
	${RM} -r ${OBJ_PATH} 2> ${DIRSEP}dev${DIRSEP}null || true

fclean:
	${RM} -r ${OBJ_PATH} 2> ${DIRSEP}dev${DIRSEP}null || true
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
