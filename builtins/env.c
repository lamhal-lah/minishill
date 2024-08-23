/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:53:54 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/23 16:20:11 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prepare(t_execute *exec)
{
	(1) && (exec->fake_in = dup(0), exec->fake_out = dup(1), exec->status = 0);
	return (0);
}

void	handle_fds(t_cmds *cmd)
{
	t_cmds	*tmp;

	cmd->fdin = 0;
	tmp = ft_lstlast_cmd(cmd);
	tmp->fdout = 1;
}

int	open_rediractions(t_cmds *cmds)
{
	t_list	*red;

	red = cmds->red;
	while (red)
	{
		if (red_in_out(cmds, red) < 0 || red_app_ambg(cmds, red) < 0)
			exit(1);
		if (red->type == nofile)
		{
			(cmds->fdin > 0 && cmds->fdout > 1) && (close(cmds->fdout),
			close(cmds->fdin));
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(red->content, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(1);
		}
		red = red->next;
	}
	return (0);
}

int	ft_print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		else if (tmp->printed == 1 && tmp->key && tmp->value == NULL)
			printf("%s=\n", tmp->key);
		tmp = tmp->next;
	}
	return (0);
}
