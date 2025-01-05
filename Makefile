# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/20 10:33:13 by vlaroque          #+#    #+#              #
#    Updated: 2019/10/10 06:50:48 by vlaroque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GLOBAL

NAME = ft_ls
CC = gcc
CFLAGS = -Wextra -Werror -Wall -g

# SOURCES

SRC_FILES = main.c debug.c entries_list.c stream.c parse_args.c entries_list_sort.c files_exploration.c path_operations.c print.c print_filename.c
LIBFT_SRCS := $(shell find libft -name '*.c')

# PATH

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = inc

# ASSIGNATION

SRC_FILES_FULL_PATH = $(addprefix $(SRC_PATH)/,$(SRC_FILES))
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_FILES_FULL_PATH = $(addprefix $(OBJ_PATH)/,$(OBJ_FILES))
DEPENDS = $(OBJ_FILES_FULL_PATH:.o=.d)

# LIBRAIRIES
LIBFT = libft/libft.a
INC_LIBFT = -Ilibft/includes
LINK_LIBFT = -Llibft -lft

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ_FILES_FULL_PATH) $(LIBFT)
	@echo "\tLinking $@'s files"
	@$(CC) $(OBJ_FILES_FULL_PATH) $(LINK_LIBFT) -o $@ $(CFLAGS)
	@echo "\t\tDone !"

-include $(DEPENDS)

$(LIBFT): $(LIBFT_SRCS)
	@echo "\t\tMaking Libft !"
	@$(MAKE) -C libft
	@echo "\t\tLibft built successfully !"


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@echo "\tCompiling $@"
	@$(CC) $(CFLAGS) -I$(INC_PATH) $(INC_LIBFT) -MMD -c $< -o $@

.PHONY: clean
clean:
	@echo "\tCleaning object files for binary and libraries..."
	@rm -f $(OBJ_FILES_FULL_PATH)
	@rm -f $(DEPENDS)
	@$(MAKE) -C libft clean
	@echo "\t\tDone !"

.PHONY: fclean
fclean: clean
	@echo "\tCleaning binary and libraries..."
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean

.PHONY: re
re: fclean all
