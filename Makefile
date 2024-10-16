# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 18:43:11 by ishenriq          #+#    #+#              #
#    Updated: 2024/10/16 15:57:48 by rde-mour         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

RED					:= $(shell tput setaf 1)
GREEN				:= $(shell tput setaf 2)
YELLOW				:= $(shell tput setaf 3)
BLUE				:= $(shell tput setaf 4)
MAGENTA				:= $(shell tput setaf 5)
RESET				:= $(shell tput sgr0)

NAME				:= cub3D

SRCSDIR				:= ./src
OBJSDIR				:= ./build
LIBFTXDIR			:= ./lib/libftx
LIBMLXDIR			:= ./lib/.MLX42

FILES				:= main.c \
					   init.c \
					   utils.c \
					   parser/parser.c \
					   parser/getter.c \
					   parser/floodfill.c \
					   parser/validate.c \
					   movement/key.c \
					   movement/move.c \
					   render/animation.c \
					   render/raycast.c \
					   render/wall.c \
					   render/utils.c

FILES_BONUS			:= main_bonus.c \
					   init_bonus.c \
					   utils_bonus.c \
					   parser/parser_bonus.c \
					   parser/getter_bonus.c \
					   parser/floodfill_bonus.c \
					   parser/validate_bonus.c \
					   movement/key_bonus.c \
					   movement/move_bonus.c \
					   movement/mouse_bonus.c \
					   movement/door_bonus.c \
					   render/animation_bonus.c \
					   render/minimap_bonus.c \
					   render/raycast_bonus.c \
					   render/wall_bonus.c \
					   render/utils_bonus.c

SRCS				= $(FILES:%.c=$(SRCSDIR)/%.c)
OBJS				= $(FILES:%.c=$(OBJSDIR)/%.o)
SRCS_BONUS			= $(FILES_BONUS:%.c=$(SRCSDIR)/bonus/%.c)
OBJS_BONUS			= $(FILES_BONUS:%.c=$(OBJSDIR)/bonus/%.o)

LIBS 				:= $(LIBMLXDIR)/build/libmlx42.a \
					  $(LIBFTXDIR)/libftx.a

HEADERS				:= -I ./include \
					   -I $(LIBFTXDIR)/includes \
					   -I $(LIBMLXDIR)/include/MLX42


LDFLAGS				:= $(HEADERS) $(LIBS)

COMPILER			:= cc
CFLAGS				:= -Wall -Wextra -Werror -g3 -Ofast
MLXFLAGS 			:= -ldl -lglfw -lm
NFLAGS				:= -R CheckForbiddenSourceHeader

DELETE 				:= $(OBJS_BONUS)
MESSAGE				:= mandatory

ifdef WITH_BONUS
	DELETE := $(OBJS)
	SRCS := $(SRCS_BONUS)
	OBJS := $(OBJS_BONUS)
	MESSAGE := bonus
endif

all: 				$(NAME)

$(NAME):			$(LIBS) $(OBJS)
					@rm -rf $(DELETE)
					@$(COMPILER) $(CFLAGS) $(HEADERS) $(OBJS) $(LIBS) $(MLXFLAGS) -o $(NAME) \
						&& echo "$(BLUE)Compiled $(MESSAGE) successfully$(RESET)"

$(OBJSDIR)/%.o: 	$(SRCSDIR)/%.c
					@mkdir -p $(@D)
					@$(COMPILER) $(CFLAGS) $(HEADERS) -c $< -o $@ \
						&& echo "$(GREEN)Compiled $(RESET)$(notdir $<)"

$(LIBS):
					@make libftx libmlx --no-print-directory 

libftx:
					@make -sC $(LIBFTXDIR)

libmlx:
					@cd $(LIBMLXDIR) && cmake -B build && make -sC build -j4

bonus:
					@make WITH_BONUS=TRUE --no-print-directory

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

.PHONY: 			all clean fclean re libmlx libftx
