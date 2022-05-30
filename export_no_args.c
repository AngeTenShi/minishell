/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:14 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/30 16:02:54 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	comes_first_in_ascii(char *one, char *two)
{
	int	i;

	i = 0;
	while (one[i] && two[i])
	{
		if (one[i] < two[i])
			return (1);
		else if (two[i] < one[i])
			return (2);
		else
			i++;
	}
	if (!one[i])
		return (1);
	else
		return (2);
}

static void	delete_first_from_env(t_list **env, t_env **line, t_list **tmp)
{
	if (ft_lstsize(*env) == 1)
	{
		(*line) = (t_env *)(ft_lstnew((*line))->content);
		ft_lstclear(env, delete_element);
	}
	else if ((*line) == (*env)->content)
	{
		(*line) = (t_env *)(ft_lstnew((*line))->content);
		(*tmp) = (*env);
		(*env) = (*env)->next;
		ft_lstdelone((*tmp), delete_element);
	}
}

static t_env	*first_var_in_ascii(t_list **env)
{
	t_env	*line;
	t_list	*tmp;
	t_list	*first;
	t_list	*previous;

	line = (*env)->content;
	tmp = (*env);
	first = tmp;
	while (tmp && tmp->next)
	{
		if (comes_first_in_ascii(line->variable,
				((t_env *)(tmp->next->content))->variable) == 2)
		{
			line = tmp->next->content;
			first = tmp->next;
			previous = tmp;
		}
		tmp = tmp->next;
	}
	if ((ft_lstsize(*env) == 1) || (line == (*env)->content))
		delete_first_from_env(env, &line, &tmp);
	else
		delete_element_from_list(&previous, &first);
	return (line);
}

static t_list	*recreate_sorted_env(t_list *env)
{
	t_list	*duplicated_env;
	t_list	*sorted_env;

	duplicated_env = duplicate_list(env);
	sorted_env = ft_lstnew(first_var_in_ascii(&duplicated_env));
	while (duplicated_env)
	{
		ft_lstadd_back(&sorted_env,
			ft_lstnew(first_var_in_ascii(&duplicated_env)));
	}
	ft_lstclear(&duplicated_env, &delete_element);
	return (sorted_env);
}

void	print_env_in_ascii_order(t_list *env)
{
	t_list	*sorted_env;
	t_list	*tmp;

	sorted_env = recreate_sorted_env(env);
	tmp = sorted_env;
	while (tmp)
	{
		printf("declare -x %s=", ((t_env *)(tmp->content))->variable);
		printf("\"%s\"\n", ((t_env *)(tmp->content))->value);
		tmp = tmp->next;
	}
	free_list(&sorted_env);
}
