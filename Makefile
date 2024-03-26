NAME		:= minishell
CFLAGS		:= -g #-Wall -Wextra -Werror
CC 			:= cc

LIBFT_PATH	:= ./lib/Libft/
LIBFT_NAME	:= libft.a
LIBFT		:= $(LIBFT_PATH)$(LIBFT_NAME)

INC_LIBFT	:= -I ./libft

SRC_PATH	:= src/

SRC			:= minishell.c envp.c \
			lexer/create_and_add_tokens.c lexer/lexer_utils.c lexer/lexer.c lexer/tokenizer.c\
			parser/parser_draft.c parser/command.c parser/expand.c #parser/parser.c
SRCS		:= $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH:= obj/
OBJ			:= ${SRC:.c=.o}
OBJS		:= $(addprefix $(OBJ_PATH), $(OBJ))

BOLD =	\033[1m
GREEN =	\033[32m
RED =	\033[31m
BCYAN =	\033[96m
NC =	\033[0m

all: libft $(NAME)

$(OBJ_PATH)%.o :$(SRC_PATH)%.c

	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_LIBFT)

$(OBJS): | $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)lexer
	@mkdir -p $(OBJ_PATH)parser

libft:
	@echo "$(BOLD)$(BCYAN)[ Making libft... ]$(NC)"
	@make -sC $(LIBFT_PATH)
	@echo "$(BOLD)$(GREEN)[ Libft ready! ]$(NC)"

$(NAME): $(OBJS)
	@echo "$(BOLD)$(BCYAN)[ Compiling $(NAME)... ]$(NC)"
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(BOLD)$(GREEN)[ $(NAME) ready! ]$(NC)"

clean:
	@rm -Rf $(OBJ_PATH)
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)
	@echo "$(BOLD)$(RED)[ Obj files deleted ]$(NC)"

fclean: clean
	@rm -rf $(NAME) $(NAME_B)
	@echo "$(BOLD)$(RED)[ Program deleted ]$(NC)"

re: clean all

party:
					@printf "\033c"
					@echo "\n\033[35m♪┏(・o･)┛♪"
					@sleep 1
					@printf "\033c"
					@echo "\033[1;33m♪┗(・o･)┓♪"
					@sleep 1
					@printf "\033c"
					@echo "\n\033[36m♪┏(・o･)┛♪"
					@sleep 1
					@printf "\033c"
					@echo "\033[34m♪┗(・o･)┓♪\n"

.PHONY: all, clean, fclean, re, libft
