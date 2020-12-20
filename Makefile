NAME = cub3D

FLAGS = -Wall -Werror -Wextra

DIR_S = sources

INCLUDES = -Ilibft -Imlx -Iincludes

B_INCLUDES = Ilibft -Imlx -Iincludes_bonus

SOURCES = 	main.c tools.c initializator.c init_textures.c create_bmp.c holy_free.c\
			parser/parser.c parser/parse_map_config.c parser/parse_r_no_so_we_ea.c parser/parse_s_f_c.c\
			parser/validate_map.c parser/validate_conf.c parser/parse_sprites.c\
			graphics/draw_map.c graphics/draw_walls.c graphics/draw_sprites.c graphics/sprites_calculation.c\
			engine/key_action.c engine/raycast.c engine/key_release_action.c

BONUS_SOURCES = main_bonus.c tools_bonus.c initializator_bonus.c init_textures_bonus.c create_bmp_bonus.c holy_free_bonus.c\
			parser/parser_bonus.c parser/parse_map_config_bonus.c parser/parse_r_no_so_we_ea_bonus.c parser/parse_s_f_c_bonus.c\
			parser/validate_map_bonus.c parser/validate_conf_bonus.c parser/parse_sprites_bonus.c\
			graphics/draw_map_bonus.c graphics/draw_walls_bonus.c graphics/draw_sprites_bonus.c graphics/sprites_calculation_bonus.c\
			engine/key_action_bonus.c engine/raycast_bonus.c engine/key_release_action_bonus.c

SRCS = $(addprefix $(DIR_S)/, $(SOURCES))

B_SRCS = $(addprefix $(DIR_S)/,$(BONUS_SOURCES))

LIBFT = libft

MLX = mlx

MLX_PATH = ./mlx/libmlx.a

OBJS = $(SRCS:.c=.o)

B_OBJS = $(B_SRCS:.c=.o)

CC_FLAGS = -Llibft -lft -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT)
	@make -C $(MLX)
	cp  $(MLX_PATH) ./
	gcc $(CC_FLAGS) -o $(NAME) $(OBJS)

bonus: $(B_OBJS)
	@make bonus -C $(LIBFT)	
	@make -C $(MLX)
	@cp  $(MLX_PATH) ./
	@gcc $(CC_FLAGS) -o $(NAME) $(B_OBJS)

%.o: %.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -f $(B_OBJS)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx.a
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY:	all clean fclean re bonus