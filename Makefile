NAME			:= cub3d

LIBFT			:= libftprintf/libftprintf.a
CC 				:= cc
CFLAGS 			:= -Wall -Werror -Wextra

SRC 			:= source/main.c \
				   source/parsing/utils.c

GCL				:= git clone
MINILIBX_SRC	:= https://github.com/42Paris/minilibx-linux.git
MINILIBX_PATH	:= source/minilibx
MINILIBX		:= source/minilibx/libmlx_Linux.a

OBJ 			:= $(SRC:source/%.c=objects/%.o)

OBJDIR			:= objects
PARSING_DIR		:= parsing

MINIFLAGS		:= -lX11 -lXext -lm -Ofast $(MINILIBX)

DEF_COLOR		:= \033[0;39m
GRAY			:= \033[0;90m
RED				:= \033[0;91m
GREEN			:= \033[0;92m
YELLOW			:= \033[0;93m
BLUE			:= \033[0;94m
MAGENTA			:= \033[0;95m
CYAN			:= \033[0;96m
WHITE			:= \033[0;97m

all: $(NAME)

$(NAME): $(MINILIBX) $(LIBFT) $(OBJDIR) $(OBJ)
	@echo "$(GREEN)Making binary: $(NAME)"
	@printf "$(MAGENTA)"
	@$(CC) $(OBJ) $(MINIFLAGS) $(LIBFT) $(CFLAGS) -o $(NAME)
	@printf "Done !$(DEF_COLOR)\n"

$(OBJDIR)/%.o: source/%.c
	@printf '$(YELLOW)Compiling : %-45s $(CYAN)-->	$(YELLOW)%-30s\n' "$<" "$@";
	@printf "$(BLUE)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(DEF_COLOR)"

clean:
	@rm -rf $(OBJDIR)
	@make --no-print-directory -C libftprintf/ clean 
	@printf "$(RED)Objects deleted !$(DEF_COLOR)\n"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(MINILIBX_PATH)
	@make --no-print-directory -C libftprintf/ fclean
	@printf "$(RED)Binary deleted !$(DEF_COLOR)\n"

$(MINILIBX):
	@if [ ! -d $(MINILIBX_PATH) ]; then $(GCL) $(MINILIBX_SRC) $(MINILIBX_PATH); make -C $(MINILIBX_PATH); fi;

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(OBJDIR)/$(PARSING_DIR)

$(LIBFT):
	@make --no-print-directory -C libftprintf/

re: fclean all

.PHONY: all clean fclean re 
