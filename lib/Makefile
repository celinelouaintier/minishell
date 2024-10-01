LIBC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_calloc.c\
ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strnstr.c \
ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_atoi.c ft_strdup.c

FSUPP = ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
ft_striteri.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_split.c

LIST = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

PRINTF = ft_printf.c ft_print_hexa.c ft_print_ptr.c ft_print_unbr.c

GNL = ft_gnl.c

NAME = libft.a

SRCS = $(LIBC) $(FSUPP) $(PRINTF) $(LIST) $(GNL)

OBJS = $(SRCS:.c=.o)

all: ${NAME}

$(NAME): ${OBJS}
	ar rc ${NAME} ${OBJS}
	printf "$(ERASE)$(CYAN)$(BOLD)$@$(RESET) $(GREEN)created!\n$(RESET)"

%.o: %.c
	${CC} -I../includes/ -c $< -o $@
	printf "$(ERASE)$(BLUE) > Compilation: $(RESET) $<"

clean:
	printf "$(ERASE)$(GREEN)Cleaning up...$(RESET)"
	rm -rf ${OBJS}
	printf "$(ERASE)$(GREEN)Clean finished!\n$(RESET)"

fclean:
	printf "$(GREEN)Fcleaning up...$(RESET)"
	rm -rf ${NAME}
	printf "$(ERASE)$(GREEN)Fclean finished!\n\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re 
.SILENT:

# COLORS
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
ERASE = \033[2K\r
RESET = \033[0m
