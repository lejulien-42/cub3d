# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejulien <lejulien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 15:52:54 by lejulien          #+#    #+#              #
#    Updated: 2020/03/03 11:32:13 by lejulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
_GREY=$'\x1b[30m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_CYAN=$'\x1b[36m
_WHITE=$'\x1b[37m

SRCS	= srcs/cub_askloading.c ./srcs/cub_bmp.c ./srcs/cub_checkmap.c ./srcs/cub_checkmap2.c ./srcs/cub_draw_utils.c ./srcs/cub_draw_utils2.c ./srcs/cub_get_next_line.c ./srcs/cub_get_next_line_utils.c \
	  ./srcs/cub_getdata_img.c ./srcs/cub_loadimg.c ./srcs/cub_main.c ./srcs/cub_minimap.c ./srcs/cub_parse1.c ./srcs/cub_parse2.c ./srcs/cub_parse3.c ./srcs/cub_parse4.c ./srcs/cub_parse5.c \
	  ./srcs/cub_raycast.c ./srcs/cub_raycast2.c ./srcs/cub_raycast3.c ./srcs/cub_raycast4.c ./srcs/cub_utils.c ./srcs/cub_utils10.c ./srcs/cub_utils11.c ./srcs/cub_utils2.c ./srcs/cub_utils3.c \
	  ./srcs/cub_utils4.c ./srcs/cub_utils5.c ./srcs/cub_utils6.c ./srcs/cub_utils7.c ./srcs/cub_utils8.c ./srcs/cub_utils9.c \
	  libft-42/ft_atoi.c ./libft-42/ft_bzero.c ./libft-42/ft_calloc.c ./libft-42/ft_isalnum.c ./libft-42/ft_isalpha.c ./libft-42/ft_isascii.c ./libft-42/ft_isdigit.c libft-42/ft_isprint.c \
	  ./libft-42/ft_itoa.c ./libft-42/ft_memccpy.c ./libft-42/ft_memchr.c ./libft-42/ft_memcmp.c ./libft-42/ft_memcpy.c ./libft-42/ft_memmove.c libft-42/ft_memset.c ./libft-42/ft_putchar_fd.c \
	  ./libft-42/ft_putendl_fd.c ./libft-42/ft_putnbr_fd.c ./libft-42/ft_putstr_fd.c ./libft-42/ft_split.c ./libft-42/ft_split_charset.c ./libft-42/ft_strchr.c ./libft-42/ft_strdup.c \
	  ./libft-42/ft_strjoin.c ./libft-42/ft_strlcat.c ./libft-42/ft_strlcpy.c ./libft-42/ft_strlen.c ./libft-42/ft_strmapi.c ./libft-42/ft_strncmp.c ./libft-42/ft_strnstr.c ./libft-42/ft_strrchr.c \
	  ./libft-42/ft_strtrim.c ./libft-42/ft_substr.c ./libft-42/ft_tolower.c ./libft-42/ft_toupper.c

OBJS	= $(SRCS:.c=.o)

NAME	= Cub3D

GCC		= gcc

FLAGS	= -Wall -Wextra -Werror

INCLUDEH =  -framework OpenGL -framework AppKit

all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

cubheader:
	@echo ""
	@echo "${_PURPLE}'######::'##::::'##:'########:::'#######::'########::"
	@echo "##... ##: ##:::: ##: ##.... ##:'##.... ##: ##.... ##:"
	@echo "##:::..:: ##:::: ##: ##:::: ##:..::::: ##: ##:::: ##:"
	@echo "##::::::: ##:::: ##: ########:::'#######:: ##:::: ##:"
	@echo "##::::::: ##:::: ##: ##.... ##::...... ##: ##:::: ##:"
	@echo "##::: ##: ##:::: ##: ##:::: ##:'##:::: ##: ##:::: ##:"
	@echo ":######::. #######:: ########::. #######:: ########::"
	@echo ":......::::.......:::........::::.......:::........::"
	@echo ""
	@echo "${_RED}Start compiling ..."
	@echo ""

$(NAME): cubheader $(OBJS)
	gcc $(INCLUDEH) -o $(NAME) $(OBJS) ./minilibx/libmlx.a

bonus: $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

%.o: %.c
	@echo "${_CYAN}Passing from $< to .o ..."
	@$(GCC) -w -D BUFFER_SIZE=1024 $(INCLUDEH) -c $<  -o $(<:.c=.o)

run: fclean $(NAME) clean
	@echo "${_GREEN}Starting Cub3D :"
	@rm -f $(OBJS)
	@./cub3D ./maps/conf.cub

runsave: fclean $(NAME) clean
	@echo "${_GREEN}Starting Cub3D :"
	@rm -f $(OBJS)
	@./cub3d.out ./maps/conf.cub --save

