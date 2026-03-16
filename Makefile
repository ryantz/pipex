# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 08:56:45 by ryatan            #+#    #+#              #
#    Updated: 2026/03/15 15:02:51 by ryatan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
COMPILER = cc
INCLUDES = -Iincludes -Ilibft -Ift_printf
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj
SRC_DIR = src

SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/error_handling.c \
	  $(SRC_DIR)/processes.c \

# pattern substitution
# $(patsubst WHAT_TO_MATCH,WHAT_TO_REPLACE_IT_WITH,WHERE_TO_LOOK)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT_DIR = libft
PRINTF_DIR = ft_printf

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(COMPILER) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(OBJ_DIR): 
	mkdir -p $(OBJ_DIR)

#To build any object file inside obj/,
#compile the matching source file inside src/,
#and create the needed subfolder first.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
