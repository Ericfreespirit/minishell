# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eriling <eriling@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/01 10:17:51 by eriling           #+#    #+#              #
#    Updated: 2021/11/10 09:28:43 by eriling          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
HEAD := -Iincludes/
# CFLAGS = -Wall -Wextra -Werror
SRC := \
	ft_atoi.c \
	ft_atoi_2.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_memset.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strlen.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_realloc.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strcmp.c \
	ft_strlcpy.c \
	ft_strcpy.c \
	ft_strlcat.c \
	ft_strnstr.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strjoinfree.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	get_next_line.c \
	ft_atof.c \
	ft_atof_2.c \
	free_arr_pointer.c \
	ft_strjoinfree.c \
	
SRCBNS :=  \
ft_lstmap_bonus.c \
ft_lstiter_bonus.c \
ft_lstclear_bonus.c \
ft_lstlast_bonus.c \
ft_lstdelone_bonus.c \
ft_lstsize_bonus.c \
ft_lstadd_back_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstnew_bonus.c \

all :	$(NAME)

$(NAME) :	
			@gcc -c ${CFLAGS} ${HEAD} ${SRC} 
			@ar rc $(NAME) *.o
			@ranlib $(NAME)

clean :
			@rm -f *.o

bonus :	
			@gcc -c ${CFLAGS} ${HEAD} ${SRC} ${SRCBNS}
			@ar rc $(NAME) *.o
			@ranlib $(NAME)
			

fclean :	clean
			@rm -f $(NAME)

re :		fclean all
