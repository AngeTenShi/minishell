NAME		=	minishell
CC			=	gcc -g
RED			=	\033[0;31m
CYAN		=	\033[0;36m
COLOR_OFF	=	\033[0m\0
YELLOW		=	\033[0;33m
FLAGS		=	-Wall -Wextra -Werror
LFT			=	libft/libft.a
INC			=	-I ./libft
LIB			=	-L ./libft -lft
SRCS_DIR	=	./srcs
OBJS_DIR	=	objs
SRCS			= builtins/env.c builtins/export_no_args.c builtins/export.c builtins/pwd.c builtins/unset.c builtins/cd.c builtins/echo.c builtins/exit.c \
				error/error.c error/free.c error/free2.c \
				env/shell_env.c \
				utils/exec_utils.c utils/env_utils.c utils/lexer_utils.c utils/lexer_utils2.c utils/retrieve_utils.c utils/retrieve_utils2.c utils/lexer_utils3.c utils/cd_utils.c\
				lexer/lexer.c lexer/lexer_list.c lexer/retrieve_all.c lexer/retrieve_second.c \
				parser/parser.c parser/parser2.c parser/parser3.c\
				expand/expand.c \
				exec/exec.c exec/exec2.c exec/exec3.c exec/heredoc.c\
				main.c signal.c

OBJS		=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

# IF NEEDED at 42 on MacOS10 Install :
#  rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
#  brew install readline
HEADER     = -I./src -I /Users/$(USER)/.brew/opt/readline/include
LDFLAGS    = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
# @HOME on MacOS12 Monterey
#HEADER      =   -I${INC_DIR} -I/usr/local/opt/readline/include
#LDFLAGS     =   -L${SRC_DIR} -L/usr/local/opt/readline/lib


all:	$(NAME)

$(NAME):	$(LFT) $(OBJS)
			$(CC) $(FLAGS) -o  $@ $^ $(LIB) $(LDFLAGS)

$(LFT):
			@echo
			@make bonus -s -C libft
			@echo "$(CYAN)[**] LIBFT READY !"

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
			@mkdir -p $(@D)
			@echo "$(RED)[**] Compiling $< [**] $(COLOR_OFF)"
#			@echo "$(COLOR_OFF)"
			@$(CC) $(FLAGS) $(INC) $(HEADER) -o $@ -c $<

clean:
			@make -s $@ -C libft
			@rm -rf $(OBJS_DIR)
			@echo "$(YELLOW)Objects Files has been removed."

fclean:		clean
			@make -s $@ -C libft
			@rm -rf $(NAME)
			@echo "$(YELLOW)Binary file has been removed."

re:			fclean all

.PHONY:		all clean fclean r
