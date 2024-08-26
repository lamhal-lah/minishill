/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:55:22 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/26 03:23:05 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signo)
{
	printf("\n");
	if (signo == SIGINT && g_i == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **args, char **env)
{
	t_list		*lst;
	t_line		lol;
	t_cmds		*cmds;
	t_execute	exec;
	static int	i;

	(1) && (g_i = 0, rl_catch_signals = 0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	(1) && ((void)ac, (void)args, lst = NULL, cmds = NULL,
	lol.env_lst = ft_env(env), lol.line = readline("minishell:  "));
	while (lol.line)
	{
		if (ft_strlen(lol.line) > 0)
			add_history(lol.line);
		(count_words(lol.line) > 0) && (cmds = proccess_line(lol.line, lol.env_lst));
		if (cmds && cmds->args && !ft_strncmp(cmds->args[0],
				"exit", 5) && cmds->args[1] == NULL)
			exit(i);
		if (cmds && cmds->args && cmds->red)
			printf("red = %s-----%d\n", cmds->red->content, cmds->red->type);
		(cmds) && (i = execute(cmds, &lol.env_lst, 0, &exec));
		(1) && (free(lol.line), ft_lstclear(&lst), 0, rl_catch_signals = 0);
		(1) && (lol.line = readline("minishell:  "), cmds = NULL);
	}
}
