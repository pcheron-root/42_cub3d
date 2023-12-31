
# Project
NAME = cub3D

# Compiler
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -MMD -MP -g3 -Ofast -ffast-math

# Paths
SRC_PATH = ./src/
BIN_PATH = ./bin/
MLX_PATH = ./minilibx-linux/

# Includes
MLX			= libmlx.a
LIBFT		= libft/libft.a
INCLUDES	= include/

# Clean
RM	= rm -rf

# Files
SRC =	main.c \
		setup_mlx.c \
		setup_world.c \
		setup_player.c \
		mlx_handling.c \
		parsing_utils.c \
		fill_world.c \
		checkup_map.c \
		checkup_map_utils.c \
		render.c \
		minimap.c \
		draw.c \

# Object files
OBJ		= $(addprefix $(BIN_PATH), $(SRC:.c=.o))
DEPS	= $(OBJ:.o=.d)

.c.o :	
		${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o ${<:.c=.o}

$(BIN_PATH)%.o: $(SRC_PATH)%.c
		mkdir -p $(dir $@)
		@ $(CC) $(CFLAGS) -c $< -o $@

${NAME} : ${OBJ}
		make all -C libft
		make -sC $(MLX_PATH)
		${CC} -o ${NAME} -g ${CFLAGS} ${OBJ} ${LIBFT} ${MLX_PATH}${MLX} -lXext -lX11 -lm
		@clear
		@toilet --gay "cub3D"

all : ${NAME}

clean :
		${RM} ${BIN_PATH}
		make clean -sC ${MLX_PATH}
		make clean -C libft

fclean : clean
		make fclean -C libft
		${RM} ${NAME}

re :		fclean all

.PHONY :	all clean fclean re

-include $(DEPS)