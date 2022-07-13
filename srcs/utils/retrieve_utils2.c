/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:14:52 by anggonza          #+#    #+#             */
/*   Updated: 2022/07/12 16:58:45 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	squote_utils(char *line, int *i, int i_tmp, char **ret)
{
	if (*i == (int)ft_strlen(line))
		return (0);
	if (*i != i_tmp)
		return (1);
	if (ft_strlen(&(line[*i])) > 1)
		(*i)++;
	else
		return (1);
	if (line[*i] && line[*i] != '\'')
	{
		*ret = ft_chardup(line[*i]);
		(*i)++;
	}
	return (0);
}

void	check_unclose_squoted(char *line, char **ret, int *i)
{
	if (**ret == '\0')
		return ;
	if (!line[*i])
	{
		free(*ret);
		send_error(PARSING, OPEN_QUOTE, line);
		*ret = ft_strdup("error");
	}
	else
		(*i)++;
}

int	check_doublequote(char *line, int *i)
{
	if ((int)ft_strlen(&line[*i]) >= 2)
	{
		if (line[*i] == '\"' && line[*i + 1] == '\"')
		{
			(*i) += 2;
			return (1);
		}
	}
	return (0);
}

int	check_singlequote(char *line, int *i, int *i_tmp)
{
	*i_tmp = *i;
	if ((int)ft_strlen(&line[*i]) >= 2)
	{
		if (line[*i] == '\'' && line[*i + 1] == '\'')
		{
			(*i) += 2;
			return (1);
		}
	}
	return (0);
}
