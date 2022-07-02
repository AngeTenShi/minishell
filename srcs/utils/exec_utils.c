/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:23 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/02 14:41:13 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*uncapitalize_str(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			ret[i] = (str[i] + 32);
		else
			ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strndup(char *str, int start, int end)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * (end - start + 2));
	i = start;
	j = 0;
	if (!ret)
		return (NULL);
	while (str[j] && i <= end)
	{
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_strjoin_with_space(char *s1, char *s2)
{
	size_t	total_length;
	char	*ret;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	total_length = ft_strlen(s1) + ft_strlen(s2) + 2;
	ret = malloc(sizeof(char) * total_length);
	i = 0;
	j = 0;
	while(s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = ' ';
	i++;
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}
