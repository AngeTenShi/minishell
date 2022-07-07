/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:34:57 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/07 18:04:34 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parsing_errors(int error, char *arg) // REMPLACER LES PRINTF PAR DES PUTSTR QUI ECRIVENT DANS STDERR
{
	if (error == OPEN_QUOTE)
		ft_putstr_fd("Error : unclosed quote\n", 2);
	else if (error == WRONG_FILE)
		printf("no such file or directory: %s\n", arg);
	else if (error == NEAR)
		printf("parse error near '%s'\n", arg);
	else if (error == BAD_ASSIGN)
		ft_putstr_fd("bad assignment\n", 2);
	else if (error == UNKNOWN_COMMAND)
		printf("%s: command not found\n", arg);
	else if (error == OPEN_REDIRECTION)
		printf("syntax error near unexpected token `newline'\n");
}

static void	exit_errors(int error, char *arg)
{
	printf("exit: ");
	if (error == NUM)
		printf("%s : numeric argument required\n", arg);
	else if (error == TOO_MANY_ARGS)
		printf("too many arguments\n");
}

static void	pwd_errors(int error)
{
	printf("pwd: ");
	if (error == TOO_MANY_ARGS)
		printf("too many arguments\n");
}

static void	env_errors(int error)
{
	printf("env: ");
	if (error == TOO_MANY_ARGS)
		printf("too many arguments\n");
}

static void	unset_errors(int error)
{
	printf("unset: ");
	if (error == NOT_ENOUGH_ARGS)
		printf("not enough arguments\n");
}

static void	cd_errors(int error, char *arg)
{
	printf("cd: ");
	if (error == TOO_MANY_ARGS)
		printf("too many arguments\n");
	else if (error == WRONG_FILE)
		printf("no such file or directory: %s\n", arg);
}

void	send_error(int function, int error, char *arg)
{
	printf("minishell-obama: ");
	if (function == EXIT)
		exit_errors(error, arg);
	else if (function == PARSING)
		parsing_errors(error, arg);
}
