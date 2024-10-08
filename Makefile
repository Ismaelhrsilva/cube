# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 18:43:11 by ishenriq          #+#    #+#              #
#    Updated: 2024/10/07 16:16:14 by rde-mour         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

RED					:= $(shell tput setaf 1)
GREEN				:= $(shell tput setaf 2)
YELLOW				:= $(shell tput setaf 3)
BLUE				:= $(shell tput setaf 4)
MAGENTA				:= $(shell tput setaf 5)
RESET				:= $(shell tput sgr0)

NAME				:= cub3d

SRCSDIR				:= ./src
OBJSDIR				:= ./build
LIBFTXDIR			:= ./lib/libftx
LIBMLXDIR			:= ./lib/MLX42

FILES				:= main.c \
					   init.c \
					   utils.c \
					   parser/parser.c \
					   parser/getter.c \
					   parser/floodfill.c \
					   parser/validate.c \
					   movement/key.c \
					   movement/move.c \
					   movement/mouse.c \
					   movement/door.c \
					   render/animation.c \
					   render/minimap.c \
					   render/raycast.c \
					   render/wall.c \
					   render/utils.c

SRCS				:= $(FILES:%.c=$(SRCSDIR)/%.c)
OBJS				:= $(FILES:%.c=$(OBJSDIR)/%.o)

LIBS 				:= $(LIBMLXDIR)/build/libmlx42.a \
					  $(LIBFTXDIR)/libftx.a

HEADERS				:= -I ./include \
					   -I ./src/parser \
					   -I $(LIBFTXDIR)/includes \
					   -I $(LIBMLXDIR)/include/MLX42

LDFLAGS				:= $(HEADERS) $(LIBS)

COMPILER			:= clang-12 
CFLAGS				:= -Wall -Wextra -Werror -g3 -Ofast
MLXFLAGS 			:= -ldl -lglfw -lm
NFLAGS				:= -R CheckForbiddenSourceHeader

all: 				$(NAME)

$(NAME):			$(LIBS) $(OBJS)
					@$(COMPILER) $(CFLAGS) $(HEADERS) $(OBJS) $(LIBS) $(MLXFLAGS) -o $(NAME) \
						&& echo "$(BLUE)Compiled $(NAME) successfully$(RESET)"

$(OBJSDIR)/%.o: 	$(SRCSDIR)/%.c
					@mkdir -p $(@D)
					@$(COMPILER) $(CFLAGS) $(HEADERS) -c $< -o $@ \
						&& echo "$(GREEN)Compiled $(RESET)$(notdir $<)"

$(LIBS):
					@make libftx libmlx --no-print-directory 

libftx:
					@git submodule sync $(LIBFTXDIR)
					@git submodule update --init --force --remote $(LIBFTXDIR)
					@make -sC $(LIBFTXDIR)

libmlx:
					@git submodule sync $(LIBMLXDIR)
					@git submodule update --init --force --remote $(LIBMLXDIR)
					@cd $(LIBMLXDIR) && cmake -B build && make -sC build -j4

clean:
					@rm -rf $(OBJSDIR) \
						&& echo "$(RED)Removing $(RESET)$(NAME) objects"

fclean: 			clean
					@rm -rf $(NAME) \
						&& echo "$(RED)Removing $(RESET)$(NAME)"
					@make fclean -sC $(LIBFTXDIR)
					@rm -rf $(LIBMLXDIR)/build \
						&& echo "$(RED)Removing $(RESET)libmlx42.a"

re: 				fclean all

norm:
					@norminette $(NFLAGS) $(SRCSDIR) ./include | grep -v "OK!" \
						|| true

.PHONY: 			all, clean, fclean, re, libmlx, libftx
