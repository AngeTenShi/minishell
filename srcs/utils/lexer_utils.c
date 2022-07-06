/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:28:01 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/06 21:07:34 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isnotspecial(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (0);
	return (1);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

char	*ft_chardup(char c)
{
	char	*ret;

	ret = malloc(sizeof(char) * 2);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}

void	get_index(char *line, int *i, int type)
{
	if (type == TOKEN_DQUOTE)
		while (line[*i] && line[*i] != '\"')
			(*i)++;
	else if (type == TOKEN_SQUOTE)
		while (line[*i] && line[*i] != '\'')
			(*i)++;
	else if (type == TOKEN_DOLLAR)
	{
		while (line[*i] && ft_isnotspecial(line[*i]) && !ft_isspace(line[*i])
			&& line[*i] != '\"' && line[*i] != '\'')
			(*i)++;
	}
}

char	*find_end(char *line, int i)
{
	char	*end;

	while (line[i] && !ft_isspace(line[i]))
		i++;
	end = ft_substr(line, i, ft_strlen(line) - i);
	return (end);
}

void	uncapitalize_cmd(t_list **lexer_list)
{
	t_list	*tmp;
	t_lexer	*caster;
	char	*uncapitalized;

	tmp = (*lexer_list);
	caster = NULL;
	uncapitalized = NULL;
	while (tmp)
	{
		caster = (t_lexer *)(tmp->content);
		if (caster->token == TOKEN_TEXT || caster->token == TOKEN_DOLLAR
			|| caster->token == TOKEN_DQUOTE || caster->token == TOKEN_SQUOTE)
		{
			if (caster->text)
			{
				uncapitalized = uncapitalize_str(caster->text);
				free(caster->text);
				caster->text = ft_strdup(uncapitalized);
				free(uncapitalized);
			}
		}
		tmp = tmp->next;
	}
}
