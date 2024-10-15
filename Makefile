#------------<COLORS>---------------
GREEN	=	\033[38;5;154m
RED		=	\033[38;5;197m
NC		=	\033[0m
YELLOW	=	\033[38;5;190m

#-------------<COMMANDS>------------
CC 		= 	cc
CFLAGS 	= 	-Wall -Wextra -Werror -fsanitize=address

# Includes and libraries
INCLUDE	=	-I./inc -I./libft -I./mlx_42/include
LIBS	=	./mlx_42/build/libmlx42.a -ldl -lglfw -pthread -lm

#--------------<SRC>----------------
NAME	=	cub3d
SRC		=	src/
CFILES	=	main.c game.c

SRCC	=	$(addprefix $(SRC), $(CFILES))

DIR_O	= 	tmp/
OBJC	=	$(addprefix $(DIR_O), $(SRCC:.c=.o))

LIB_A		:=	libft/libft.a 
LIB_ADD_DIR	:=	-Llibft 
LIB_SEARCH	:=	-lft 

#-------------<RULES>-------------
all: makemlx makelibs $(DIR_O) $(NAME)

makelibs: 
	@$(MAKE) -C libft/ --no-print-directory
	
$(DIR_O):
	@mkdir -p $(DIR_O)

$(NAME): $(OBJC)
	@$(CC) $(CFLAGS) $(OBJC) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) $(LIBS) -o $(NAME)
	@echo "${GREEN}Cub Compiled${NC}"
	
$(DIR_O)%.o: %.c $(LIB_A) Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "${YELLOW}Compiling obj $@...${NC}"

makemlx:
		@echo " [ .. ] | Compiling minilibx.."
		@cd mlx_42 && cmake -B build && cmake --build build --parallel --config Release
		@echo " [ OK ] | Minilibx ready!"

clean: 
	@$(MAKE) -C libft clean --no-print-directory
	@rm -rf $(DIR_O)
	@printf "${RED}Objs deleted\n${NC}"

fclean: clean 
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean --no-print-directory
	@rm -rf mlx_42/build
	@printf "${RED}Cub deleted\n${NC}"

re: fclean all

.PHONY: all clean fclean re
