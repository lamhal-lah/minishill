/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:55:22 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/15 13:39:49 by aboulakr         ###   ########.fr       */
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
		if (count_words(line) > 0)
			cmds = proccess_line(line, &lst, env_lst);
		if (cmds && cmds->red)
			printf("red = %s-----%d\n", cmds->red->content, cmds->red->type);
		free(line);
		ft_lstclear(&lst);
		//ft_is_builtin(cmds, env_lst);
		execute(cmds, &env_lst, 0);
		// ft_lstclear_cmds(&cmds);
		cmds = NULL;
		line = readline("minishell:  ");
	}
}
