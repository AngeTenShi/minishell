/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_from_zero.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:42:59 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/07 19:24:34 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	identify_token(char c, char next)
{
	if (!next)
		next = '\0';
	if (c == '\"')
		return (TOKEN_DQUOTE);
	else if (c == '\'')
		return (TOKEN_SQUOTE);
	else if (c == '$')
		return (TOKEN_DOLLAR);
	else if (c == '|')
		return (TOKEN_PIPE);
	else if (c == '<' && next != '<')
		return (TOKEN_INFILE);
	else if (c == '<' && next == '<')
		return (TOKEN_HEREDOC);
	else if (c == '>' && next != '>')
		return (TOKEN_OUTFILE);
	else if (c == '>' && next == '>')
		return (TOKEN_APPEND);
	else if (ft_isnotspecial(c) && !ft_isspace(c))
		return (TOKEN_TEXT);
	return (0);
}

char	*check_for_envvar(char *line)
{
	int		i;
	char	*end;
	char	*begin;
	char	*tmp;
	int		before_var;

	i = 0;
	end = NULL;
	begin = NULL;
	tmp = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			before_var = i;
			end = find_end(line, i + 1);
			begin = ft_strndup(line, 0, i - 1);
			line = retrieve_variable(line, &i, 0);
			tmp = ft_strjoin(begin, line);
			line = ft_strjoin(tmp, end);
			free(tmp);
			free(end);
			free(begin);
			i = before_var;
		}
		i++;
	}
	return (line);
}

char	*retrieve_filename(char *line, int *i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;

	ret = NULL;
	tmp = NULL;
	tmp2 = NULL;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (line[*i])
	{
		ret = ft_chardup(line[*i]);
		(*i)++;
	}
	while (line[*i] && !ft_isspace(line[*i]) && ft_isnotspecial(line[*i]))
	{
		tmp = ft_strdup(ret);
		tmp2 = ft_chardup(line[*i]);
		free(ret);
		ret = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		(*i)++;
	}
	return (ret);
}

int	interpret_token(char *line, int token, int *i, t_list **list)
{
	char	*content;
	int		single_quoted;

	content = NULL;
	single_quoted = 0;
	check_sometoken(line, token, &content, i);
	if (token == TOKEN_SQUOTE)
	{
		single_quoted = 1;
		content = retrieve_squoted_text(line, i);
	}
	else if (token == TOKEN_DOLLAR)
		content = retrieve_variable(line, i, single_quoted);
	else if (token == TOKEN_INFILE || token == TOKEN_OUTFILE)
		content = retrieve_filename(line, i);
	else if (token == TOKEN_APPEND)
	{
		while (line[*i] && line[*i] == '>')
			(*i)++;
		content = retrieve_filename(line, i);
	}
	if (!check_error_or_update(content, list, token))
		return (0);
	return (1);
}

void	ft_lexer(char *line)
{
	int		i;
	int		token;
	t_list	*lexer_list;

	i = 0;
	lexer_list = NULL;
	if (ft_strlen(line) < 3)
	{
		all_check_errors(line);
		return ;
	}
	if (check_error(line))
		return ;
	while (line[i])
	{
		token = identify_token(line[i], line[i + 1]);
		if (!interpret_token(line, token, &i, &lexer_list))
			return ;
		while (line[i] && ft_isspace(line[i]))
			i++;
	}
	// print_lexer_list(lexer_list);
	uncapitalize_cmd(&lexer_list);
	ft_parser(&lexer_list);
	free_lexer(&lexer_list);
}
