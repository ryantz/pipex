# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 16:26:03 by ryatan            #+#    #+#              #
#    Updated: 2025/12/02 22:07:27 by ryatan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# variables
NAME = libftprintf.a
ARCHIVE = ar
ARCHIVE_FLAGS = rcs
COMPILER = cc
CFLAGS = -Wall -Werror -Wextra

SOURCE_FILES = ft_printf.c print_functions.c  more_print_functions.c

OBJECT_FILES = $(SOURCE_FILES:%.c=%.o)

#TEST_FILE = test.c
#EXEC = test

# rules
%.o: %.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECT_FILES)
	$(ARCHIVE) $(ARCHIVE_FLAGS) $(NAME) $(OBJECT_FILES)

# testing with an exe
#$(EXEC): $(TEST_FILE) $(NAME) $(LIBFT)
#	$(COMPILER) $(TEST_FILE) -L. -lftprintf -L$(LIBFT_DIR) -lft -o $(EXEC)

all: $(NAME) $(EXEC)

clean:
	rm -rf $(OBJECT_FILES)

fclean: clean
	rm -rf $(NAME) $(EXEC)

re: fclean all

.PHONY : all clean fclean re
