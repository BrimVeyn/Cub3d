NAME			:= minishell

LIBFT			:= libftprintf/libftprintf.a
CC 				:= cc
LDFLAGS			:= -lreadline -lncurses
CFLAGS 			:= -Wall -Werror -Wextra
SRC 			:= source/main.c

GCL				:= git clone
MINILIBX_SRC	:= https://github.com/42Paris/minilibx-linux.git source/minilibx
MINILIBX		:= source/minilibx/libmlx_Linux.a

OBJ 			:= $(SRC:source/%.c=objects/%.o)

PARSING_DIR		:= parsing

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

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ)
	@echo "$(GREEN)Making binary: $(NAME)"
	@printf "$(MAGENTA)"
	@$(CC) $(OBJ) $(LIBFT) $(CFLAGS) $(LDFLAGS) -o $(NAME)
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
	@make --no-print-directory -C libftprintf/ fclean
	@printf "$(RED)Binary deleted !$(DEF_COLOR)\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(OBJDIR)/$(PARSING_DIR)

$(LIBFT):
	@make --no-print-directory -C libftprintf/

re: fclean all

.PHONY: all clean fclean re 
