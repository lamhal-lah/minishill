/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:06:53 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/15 15:45:54 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_fds(t_cmds *cmd)
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
		if (red->type == red_in)
		{
			(1) && (close(cmds->fdin),
				cmds->fdin = open(red->content, O_RDONLY));
			(cmds->fdin == -1) && (printf("minihell: %s: %s", red->content,
				strerror(errno)), exit(1), 0);
		}
		else if (red->type == red_out)
		{
			(1) && (close(cmds->fdout), cmds->fdout = open(red->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0777));
			(cmds->fdout == -1) && (printf("minihell: %s: %s", red->content,
				strerror(errno)), exit(1), 0);
		}
		else if (red->type == append)
		{
			(1) && (close(cmds->fdout), cmds->fdout = open(red->content,
				O_WRONLY | O_CREAT | O_APPEND, 0777));
			(cmds->fdout == -1) && (printf("minihell: %s: %s", red->content,
				strerror(errno)), exit(1), 0);
		}
		else if (red->type == ambigus)
		{
			(1) && (close(cmds->fdout), close(cmds->fdin),
			printf("minishell: %s:ambiguous redirect\n", red->content));
			exit(1);
		}
		red = red->next;
	}
	return (0);
}

void	ft_check_redirections(t_cmds *cmd, int **fd, int i)
{
	if (i >= 0)
	{
		if (cmd->fdin == -1337)
			cmd->fdin = fd[i - 1][0];
		dup2(cmd->fdin, 0);
	}
	if (cmd->next != NULL)
	{
		if (cmd->fdout == -1337)
			cmd->fdout = fd[i][1];
		dup2(cmd->fdout, 1);
	}
}

int	execute(t_cmds *cmd, t_env **env, int i)
{
	int		fake_in;
	int		fake_out;
	int		**fd;
	int		status;
	t_cmds	*tmp;
	int		*pid;

	(1) && (i = -1, tmp = cmd, status = 0, pid = NULL, fd = NULL,
		fake_in = dup(0), fake_out = dup(1));
	if (!tmp)
		return (0);
	handle_fds(tmp);
	fd = malloc(sizeof(int *) * (ft_cmdsize(cmd)));
	if (!fd)
		return (perror("malloc"), -1);
	while (tmp && ++i < ft_cmdsize(cmd) - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			return (perror("malloc"), -1);
		if (pipe(fd[i]) == -1)
			return (perror("pipe"), -1);
	}
	fd[i] = NULL;
	pid = malloc(sizeof(int) * ft_cmdsize(cmd));
	if (!pid)
		return (perror("malloc"), -1);
	i = 0;
	while (tmp)
	{
		if (ft_cmdsize(tmp) == 1 && check_if_builtin(tmp))
			(1) && (status = handle_one_cmd(tmp, env), tmp = tmp->next, i++);
		else
		{
			pid[i] = fork();
			if (pid[i] < 0)
				return (perror("fork"), -1);
			if (pid[i] == 0)
				middle_commands(tmp, *env, fd, i);
			else
			{
				if (i < ft_cmdsize(cmd) - 1)
					close(fd[i][1]);
			}
			tmp = tmp->next;
			i++;
		}
	}
	i = -1;
	while (fd[++i])
		close(fd[i][0]);
	i = -1;
	while (++i < ft_cmdsize(cmd))
		waitpid(pid[i], &status, 0);
	(1) && (free(pid), free(fd),
		dup2(fake_in, 0), dup2(fake_out, 1), close(fake_in), close(fake_out));
	return (status);
}
