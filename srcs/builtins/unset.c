/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:44:54 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/02 14:41:13 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	found_variable(t_list *element, char *variable)
{
	char	*_element;
	int		len;

	_element = ((t_env *)(element->content))->variable;
	len = ft_strlen(variable);
	if (!ft_strncmp(_element, variable, len)
		&& !_element[len + 1])
		return (1);
	return (0);
}

static void	remove_from_env(t_list **env, char *var)
{
	t_list	*tmp;

	tmp = (*env);
	if (found_variable(tmp, var))
	{
		(*env) = (*env)->next;
		ft_lstdelone(tmp, &empty_env_element);
		return ;
	}
	while (tmp->next)
	{
		if (found_variable(tmp->next, var))
		{
			ft_lstdelone(tmp->next, &empty_env_element);
			tmp->next = tmp->next->next;
			return ;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_unset(char *variable, t_list **env)
{
	t_list	*tmp;
	int		found;

	tmp = (*env);
	found = 0;
	if (!variable)
		return ;
	while (tmp)
	{
		if (found_variable(tmp, variable))
		{
			remove_from_env(env, variable);
			found = 1;
			return ;
		}
		tmp = tmp->next;
	}
}
