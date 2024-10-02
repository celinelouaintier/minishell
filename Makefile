.SILENT:

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -I./includes
LIBFT = libft.a
LIBPATH = lib
SRCS_DIR	= srcs/

# Minishell

PROG		= minishell

SRCS		= main.c
SRC 		= ${addprefix ${SRCS_DIR}, ${SRCS}}
OBJS 		= ${SRC:.c=.o}

# Commands

CMD_NAME 	= commands

CMDS 		= commands.c
CMD 		= ${addprefix ${SRCS_DIR}, ${CMDS}}
CMDS_OBJS 	= ${CMD:.c=.o}


%.o: %.c
					@echo "\033[34mCompiling $<..."
					$(CC) $(CFLAGS) -c $< -o $@

all: 		${PROG}

${PROG}:	${OBJS} ${CMDS_OBJS}
					@echo "\033[33m----Compiling lib----"
					@make -s -C $(LIBPATH)
					@echo "\n"
					$(CC) -lreadline $(CFLAGS) ${OBJS} $(LIBPATH)/$(LIBFT) -o ${PROG}
					$(CC) -lreadline $(CFLAGS) ${CMDS_OBJS} $(LIBPATH)/$(LIBFT) -o ${CMD_NAME}
					@echo "\033[32m Minishell Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

clean:
					make -s clean -C ./lib
					rm -f ${OBJS}
					rm -f ${CMDS_OBJS}

fclean: 	clean
					make -s fclean -C ./lib
					rm -f ${PROG}
					rm -f ${CMD_NAME}
					@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re:			fclean all

party:
					@printf "\033c"
					@echo "\n\033[35m♪┏(・o･)┛♪"
					@sleep 1
					@printf "\033c"
					@echo "\033[1;33m♪┗(・o･)┓♪"
					@sleep 1
					@printf "\033c"
					@echo "\n\033[36m♪┏(・o･)┛♪"
					@sleep 1
					@printf "\033c"
					@echo "\033[34m♪┗(・o･)┓♪\n"

.PHONY: all clean fclean re re_bonus bonus party