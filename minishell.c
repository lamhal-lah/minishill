/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:55:22 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/11 11:15:13 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **args, char **env)
{
	t_list	*lst;
	t_env	*env_lst;
	t_cmds	*cmds;
	char	*line;

	(void)ac;
	(void)args;
	lst = NULL;
	env_lst = ft_env(env);
	line = readline("minishell:  ");
	while (line && ft_strncmp(line, "exit", 5))
	{
		//printf("line = %s\n", line);
		if (ft_strlen(line) > 0)
			add_history(line);
		// system("leaks minishell");
		cmds = proccess_line(line, &lst, env_lst);
		free(line);
		ft_lstclear(&lst);
		execute(cmds, env_lst, 0);
		line = readline("minishell:  ");
	}
}
