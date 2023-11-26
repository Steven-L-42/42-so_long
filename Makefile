NAME		=	so_long

#CC			=	cc -fsanitize=address -fno-omit-frame-pointer -Wall -Werror -Wextra

CC			=	cc

INCLUDE		=	libs/libft/

CFLAGS		=	-Wall -Werror -Wextra

SRC_FOLDER	=	srcs/

SRC_BFOLDER	=	srcs_bonus/

OBJ_FOLDER	=	objs/

OBJ_BFOLDER	=	objs_bonus/

SRCS		=	main.c ft_pathfinding.c ft_draw_text.c ft_init_one.c \
				ft_init_two.c ft_create_map.c ft_ghost_behaviour.c ft_player_behaviour.c ft_keybind.c ft_fill_map.c \
				ft_helper.c ft_free_all.c ft_fill_map_helper.c ft_pathfinding_helper.c

SRCS_BONUS	=	main_bonus.c ft_pathfinding_bonus.c ft_draw_text_bonus.c ft_init_one_bonus.c \
				ft_init_two_bonus.c ft_create_map_bonus.c ft_ghost_behaviour_bonus.c ft_player_behaviour_bonus.c ft_keybind_bonus.c ft_fill_map_bonus.c \
				ft_helper_bonus.c ft_free_all_bonus.c ft_fill_map_helper_bonus.c ft_pathfinding_helper_bonus.c

OBJS		=	$(addprefix $(OBJ_FOLDER),$(SRCS:%.c=%.o))

OBJS_BONUS	=	$(addprefix $(OBJ_BFOLDER),$(SRCS_BONUS:%.c=%.o))

COLOR_RESET	=	\033[0m
COLOR_CYAN	=	\033[36m
COLOR_GREEN	=	\033[32m
COLOR_RED	=	\033[31m

$(NAME): 		install_mlx $(INCLUDE) $(OBJS)
				@cd $(INCLUDE) && make
				@$(CC) $(INCLUDE)libft.a $(CFLAGS) -o $(NAME) $(OBJS) ./libs/MLX42/build/libmlx42.a -Iinclude -lglfw
				@echo "$(COLOR_CYAN)SO_LONG Compilation completed: $(NAME)$(COLOR_RESET)"

libs/MLX42:
				@mkdir -p libs
				@cd libs && git clone https://github.com/codam-coding-college/MLX42.git
				@cd libs/MLX42 && cmake -B build && cmake --build build -j4

install_mlx: 	libs/MLX42

objs/%.o:		$(SRC_FOLDER)%.c
				@mkdir -p objs
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo "$(COLOR_GREEN)SO_LONG Compilation completed: $@$(COLOR_RESET)"

objs_bonus/%.o:	$(SRC_BFOLDER)%.c
				@mkdir -p objs_bonus
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo "$(COLOR_GREEN)SO_LONG Compilation completed: $@$(COLOR_RESET)"

all:			$(NAME)

clean:
				@rm -rf $(OBJS)
				@rm -rf $(OBJS_BONUS)
				@cd $(INCLUDE) && make clean
				@echo "$(COLOR_RED)Cleanup completed.$(COLOR_RESET)"

fclean:			clean
				@rm -f $(NAME)
				@rm -rf objs
				@rm -rf objs_bonus
				@cd $(INCLUDE) && make fclean
				@echo "$(COLOR_RED)Removal completed.$(COLOR_RESET)"

re:				fclean install_mlx all

bonus: 			install_mlx $(INCLUDE) $(OBJS_BONUS)
				@cd $(INCLUDE) && make
				@$(CC) $(INCLUDE)libft.a $(CFLAGS) -o $(NAME) $(OBJS_BONUS) ./libs/MLX42/build/libmlx42.a -Iinclude -lglfw
				@echo "$(COLOR_CYAN)SO_LONG Compilation completed: $(NAME)$(COLOR_RESET)"
