/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anggonza <anggonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:45:12 by itaouil           #+#    #+#             */
/*   Updated: 2022/07/14 18:16:00 by anggonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_all	g_all;

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*str;

	(void)argc;
	(void)argv;
	g_all.fd_to_close = -1;
	env = create_env(envp);
	g_all.env = env;
	//detect_signals();
	while (1)
	{
		str = readline("minishell obama is waiting for instructions > ");
		if (ft_strlen(str) == 0)
			continue ;
		if (!ft_strncmp(str, "exit", 4))
		{
			free(str);
			break ;
		}
		add_history(str);
		ft_lexer(str);
		free(str);
	}
	free_env(&env);
}

	//system("leaks minishell");
// COMMENTAIRE D'AU DESSUS
// ft_export(&env, "VARTEST", "lol");
	// ft_export(&env, NULL, NULL);
	//ft_unset("PATH=", &env);
	// ft_env(&env);


