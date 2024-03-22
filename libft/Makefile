# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dianamavlutova <dianamavlutova@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/21 13:52:16 by dmavliut          #+#    #+#              #
#    Updated: 2024/03/22 18:08:54 by dianamavlut      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS =	ft_memset.c ft_bzero.c ft_memcpy.c \
		ft_memmove.c ft_memchr.c ft_memcmp.c \
		ft_strlen.c ft_isalpha.c ft_isdigit.c \
		ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_strlcpy.c \
		ft_strlcat.c ft_strnstr.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c

# Object files
OBJS = $(SRCS:.c=.o)

# Name of the library
NAME = libft.a

.PHONY: all clean fclean re

# Default rule
all: $(NAME)

# Build the library
$(NAME): $(OBJS)
	@echo "Building library..."
	ar rcs $(NAME) $(OBJS)
	@echo "Done! Libft is ready."

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJS)
	@echo "Object files removed."

# Clean everything (object files and library)
fclean: clean
	rm -f $(NAME)
	@echo "Library removed."

# Rebuild everything
re: fclean all
