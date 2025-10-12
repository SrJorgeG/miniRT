NAME = libft
NAME_STATIC = libft.a
CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror
ARFLAGS = rcs

# ==== Archivos ====
LIBFT_SRC = ft_atodbl.c ft_isascii.c ft_lstdelone.c  ft_memchr.c ft_putnbr_fd.c ft_strjoin.c ft_strncpy.c \
ft_atoi.c  ft_isdigit.c ft_lstiter.c ft_memcmp.c ft_putstr_fd.c ft_strlcat.c ft_strnstr.c ft_strstr.c\
ft_atol.c  ft_isprint.c ft_lstlast.c ft_memcpy.c ft_split.c ft_strlcpy.c ft_strrchr.c ft_strndup.c\
ft_bzero.c ft_itoa.c ft_lstmap.c ft_memmove.c  ft_strchr.c  ft_strlen.c ft_strtrim.c ft_strreplace.c \
ft_calloc.c ft_lstadd_back.c ft_lstnew.c  ft_memset.c ft_strdup.c  ft_strlower.c ft_substr.c \
ft_isalnum.c  ft_lstadd_front.c  ft_lstsize.c ft_putchar_fd.c ft_strisdbl.c ft_strmapi.c ft_tolower.c \
ft_isalpha.c  ft_lstclear.c ft_lstsort_int.c  ft_putendl_fd.c  ft_striteri.c ft_strcmp.c ft_strncmp.c ft_toupper.c \
ft_free_split.c ft_lststrlen.c ft_lstfind_cmp.c ft_lstclearnodes.c ft_lst_to_strlist.c ft_strisnum.c \
get_next_line.c get_next_line_utils.c ft_stack.c ft_stack_aux.c

LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

# ==== Targets ====
all: $(NAME_STATIC)

$(NAME_STATIC): $(LIBFT_OBJ)
	$(AR) $(ARFLAGS) $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIBFT_OBJ) *.o

fclean: clean
	rm -f $(NAME_STATIC)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
