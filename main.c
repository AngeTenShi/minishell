/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:12 by itaouil           #+#    #+#             */
/*   Updated: 2022/05/30 16:04:01 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	(void)argc;
	(void)argv;

	env = create_env(envp);
	ft_export(&env, NULL, NULL);
	// ft_env(&env);
	// free_list(&env);
	//ft_free_list(&env);
	//print_env(env);
	//system("leaks a.out");
}
