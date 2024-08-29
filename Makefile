# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 18:43:11 by ishenriq          #+#    #+#              #
#    Updated: 2024/08/29 18:57:43 by ishenriq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3 -O3
CC	:= cc
LIBMLX	:= lib/MLX42/
PRINTF	:= lib/printf/
LIBFT	:= lib/libft/
GNL	:= lib/gnl/
BUILD_DIR = objects/
MKDIR  := mkdir -p

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBFT) -I $(PRINTF) $(LIBS) -I $(GNL)

LIBS 	:= $(LIBMLX)build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)libft.a \
	-lm $(PRINTF)libftprintf.a

LDFLAGS	:= $(HEADERS) $(LIBS)

SRCS += $(addprefix src/mandatory/, main.c)

SRCS_BONUS	+= $(addprefix src/bonus/, wildcard *.c)

OBJS	+=  $(SRCS:%.c=$(BUILD_DIR)%.o)
OBJS_BONUS	+= $(SRCS_BONUS:%.c=$(BUILD_DIR)%.o)

DELETE	=	$(OBJS_BONUS)

ifdef   WITH_BONUS
		DELETE := $(OBJS)
		OBJS = $(OBJS_BONUS)
endif

define create_dir
	$(MKDIR) $(dir $@)
endef

define bonus
	$(MAKE) WITH_BONUS=TRUE
endef

all: libmlx libft printf $(NAME)

$(BUILD_DIR)%.o: %.c
	@rm -rf $(DELETE)
	$(call create_dir)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)build && make -C $(LIBMLX)build -j4

libft:
	@make -C $(LIBFT)

printf:
	@make -C $(PRINTF)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

bonus:
	$(call bonus)

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) fclean
	@make -C $(PRINTF) fclean

re: clean all

re_bonus: clean bonus

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS) ./include

.PHONY: all, clean, fclean, re, libmlx, libft, printf, bonus
.DEFAULT_GOAL := all
