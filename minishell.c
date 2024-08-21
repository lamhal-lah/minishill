/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:55:22 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/21 22:07:24 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **args, char **env)
{
	t_list		*lst;
	t_env		*env_lst;
	t_cmds		*cmds;
	char		*line;
	t_execute	exec;

	(1) && ((void)ac, (void)args, lst = NULL, cmds = NULL,
	env_lst = ft_env(env), line = readline("minishell:  "));
	while (line && ft_strncmp(line, "exit", 5))
	{
		(ft_strlen(line) > 0) && (add_history(line));
		(count_words(line) > 0) && (cmds = proccess_line(line, env_lst));
		if (cmds && cmds->args && cmds->red)
			printf("red = %s-----%d\n", cmds->red->content, cmds->red->type);
		(1) && (free(line), ft_lstclear(&lst), 0);
		(cmds) && (execute(cmds, &env_lst, 0, &exec));
		(1) && (line = readline("minishell:  "), cmds = NULL);
	}
}
