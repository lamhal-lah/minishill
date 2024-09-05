/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:55:22 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/05 10:44:44 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signo)
{
	if (signo == SIGINT && (g_i == 0 || g_i == 2))
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_i = 2;
	}
	else if (g_i == 1)
	{
		close(0);
		g_i = 3;
	}
}

static void	initialize(t_line *lol, t_execute *exec, char **env)
{
	g_i = 0;
	rl_catch_signals = 0;
	exec->status = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	lol->line = readline("minishell:  ");
	tcgetattr(0, &lol->original_term);
	lol->env_lst = ft_env(env);
}

static void	ft_exit_now(t_cmds *cmds, int i)
{
	if (cmds && cmds->args && cmds->args[0] && !ft_strncmp(cmds->args[0],
			"exit", 5) && cmds->args[1] == NULL
		&& cmds->next == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		if (g_i == 2)
		{
			g_i = 0;
			exit(1);
		}
		exit(i);
	}
}

void	ft_free_line_prompt(t_line *lol, t_cmds *cmds,
	t_list *lst, t_execute exec)
{
	free(lol->line);
	ft_lstclear(&lst);
	cmds = NULL;
	rl_catch_signals = 0;
	if (g_i == 2)
	{
		lol->line = readline("minishell:  ");
		tcsetattr(0, TCSANOW, &lol->original_term);
	}
	else
	{
		tcsetattr(0, TCSANOW, &lol->original_term);
		lol->line = readline("minishell:  ");
	}
	(g_i == 2) && (exec.status = 1);
}

int	main(int ac, char **args, char **env)
{
	t_list		*lst;
	t_line		lol;
	t_cmds		*cmds;
	t_execute	exec;
	static int	i;

	initialize(&lol, &exec, env);
	(1) && ((void)ac, (void)args, lst = NULL, cmds = NULL,
	signal(SIGINT, sig_handler));
	while (lol.line && isatty(0))
	{
		(g_i == 2) && (exec.status = 1, g_i = 0);
		if (ft_strlen(lol.line) > 0)
			add_history(lol.line);
		cmds = proccess_line(lol.line, &exec.status, lol.env_lst);
		ft_exit_now(cmds, i);
		(cmds) && (i = execute(cmds, &lol.env_lst, 0, &exec));
		ft_free_line_prompt(&lol, cmds, lst, exec);
	}
	(g_i == 2) && (exec.status = 1, i = 1);
	exit(i);
}
