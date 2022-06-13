#include "minishell.h"

static void	parsing_errors(int error)
{
	if (error == OPEN_QUOTE)
		printf("Error : unclosed quote\n");
	exit(EXIT_FAILURE);
}

static void	exit_errors(int error, char *arg)
{
	printf("exit: ");
	if (error == NUM)
		printf("%s : numeric argument required\n", arg);
	else if (error == TOO_MANY_ARGS)
		printf("too many arguments\n");
}

void	send_error(int function, int error, char *arg)
{
	printf("minishell-obama :");
	if (function == EXIT)
		exit_errors(error, arg);
	else if (function == PARSING)
		parsing_errors(error);
}
