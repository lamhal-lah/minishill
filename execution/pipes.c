/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:06:53 by aboulakr          #+#    #+#             */
/*   Updated: 2024/09/05 10:46:16 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_pipes(t_cmds *cmd, int ***fd, int i, int **pid)
{
	(1) && (*fd = NULL, i = -1, *pid = NULL);
	handle_fds(cmd);
	if (ft_cmdsize(cmd) > 1)
	{
		*fd = malloc(sizeof(int *) * (ft_cmdsize(cmd)));
		if (!*fd)
			return (perror("malloc"), -1);
		while (cmd && ++i < ft_cmdsize(cmd) - 1)
		{
			(*fd)[i] = malloc(sizeof(int) * 2);
			if (!(*fd)[i])
				return (perror("malloc"), -1);
			if (pipe((*fd)[i]) == -1)
				return (perror("pipe"), -1);
		}
		(*fd)[i] = NULL;
	}
	*pid = malloc(sizeof(int) * ft_cmdsize(cmd));
	if (!*pid)
		return (perror("malloc"), -1);
	return (0);
}

void	btn(t_execute *exec)
{
	if (dup2(exec->fake_in, 0) < 0)
		return (perror("dup2"), exit(1));
	if (dup2(exec->fake_out, 1) < 0)
		return (perror("dup2"), exit(1));
	close(exec->fake_in);
	close(exec->fake_out);
	return ;
}

void	free_pipes(t_cmds **cmd, int ***fd, int **pid)
{
	int		i;

	i = -1;
	if (cmd && *cmd && ft_cmdsize(*cmd) > 1)
	{
		while ((*fd)[++i])
			free((*fd)[i]);
		free(*fd);
	}
	free(*pid);
	ft_lstclear_cmd(cmd);
}

int	wait_pids(t_cmds *cmd, int **fd, int *pid, t_execute *exec)
{
	int	i;

	(1) && (i = -1);
	if (ft_cmdsize(cmd) > 1)
	{
		while (fd[++i])
		{
			(fd[i][0] != -1) && (close(fd[i][0]), fd[i][0] = -1);
		}
	}
	i = -1;
	while (++i < ft_cmdsize(cmd))
		waitpid(pid[i], &exec->status, 0);
	if (WIFSIGNALED(exec->status))
	{
		if (WTERMSIG(exec->status) == 3)
			ft_putstr_fd("Quit: 3\n", 2);
		else if (WTERMSIG(exec->status) == 2)
			ft_putstr_fd("\n", 2);
		exec->status = WTERMSIG(exec->status) + 128;
	}
	else
		exec->status = WEXITSTATUS(exec->status);
	(free_pipes(&cmd, &fd, &pid), signal(SIGINT, sig_handler), btn(exec));
	return (g_i = 0, exec->status);
}

int	execute(t_cmds *cmd, t_env **env, int i, t_execute *exec)
{
	int		**fd;
	t_cmds	*tmp;
	int		*pid;

	(1) && (i = 0, tmp = cmd, under_score(cmd, env), signal(SIGINT, ctrl_c));
	(prepare(exec) || fill_pipes(cmd, &fd, i, &pid))
		&& (free_pipes(&cmd, &fd, &pid), exit(1), 0);
	if (ft_cmdsize(tmp) == 1 && check_if_builtin(tmp))
		return (exec->status = handle_one_cmd(tmp, env), signal(SIGINT,
				sig_handler), free_pipes(&cmd, &fd, &pid),
			btn(exec), exec->status);
	while (tmp)
	{
		(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN), pid[i] = fork());
		if (pid[i] < 0)
			return (kil(pid, i, fd), btn(exec), free_pipes(&cmd, &fd, &pid), 1);
		if (pid[i] == 0)
			(1) && (signal(SIGQUIT, SIG_DFL),
				signal(SIGINT, SIG_DFL), middle_commands(tmp, *env, fd, i), 0);
		else
			if (i < ft_cmdsize(cmd) - 1)
				(fd[i][1] != -1) && (close(fd[i][1]), fd[i][1] = -1);
		(1) && (i++, tmp = tmp->next);
	}
	return (exec->status = wait_pids(cmd, fd, pid, exec), exec->status);
}
