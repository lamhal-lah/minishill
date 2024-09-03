/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:54:55 by aboulakr          #+#    #+#             */
/*   Updated: 2024/09/01 23:53:38 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	middle_commands(t_cmds *cmd, t_env *env, int **fd, int i)
{
	int	x;

	x = -1;
	if (open_rediractions(cmd) < 0)
		exit(1);
	if (!cmd || !cmd->args || cmd->args[0] == NULL)
	{
		if (cmd->args && cmd->args[0] == NULL)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("command not found\n", 2);
			exit(127);
		}
		exit(0);
	}
	ft_check_redirections(cmd, fd, i);
	while (fd && fd[++x])
	{
		(fd[x][0] != -1) && (close(fd[x][0]), fd[x][0] = -1);
		(fd[x][1] != -1) && (close(fd[x][1]), fd[x][1] = -1);
	}
	error_management(cmd, env);
}

void	ft_handle_dot(t_cmds *cmds, t_env *env)
{
	struct stat	buf;

	(cmds->args[1] == NULL) && (ft_putstr_fd("minishell: .: filename argument",
		2), ft_putstr_fd("required \n .: usage: .",
			2), ft_putstr_fd("filename [arguments]\n", 2), exit(2), 0);
	if (cmds->args[1] != NULL)
	{
		if (stat(cmds->args[1], &buf) == 0)
		{
			if (S_ISDIR(buf.st_mode))
				(1) && (ft_putstr_fd("minishell: ", 2),
				ft_putstr_fd(cmds->args[1],
				2), ft_putstr_fd(": is a directory\n", 2), exit(1), 0);
		}
		else if (!find_path(cmds->args[1], env)
			&& access(cmds->args[1], F_OK) == -1)
			(1) && (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmds->args[1],
				2), ft_putstr_fd(": No such file or directory\n",
					2), exit(1), 0);
		else if (find_path(cmds->args[1], env) || !access(cmds->args[1], X_OK))
			(1) && (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmds->args[1],
				2), ft_putstr_fd(": command not found\n", 2), exit(1), 0);
	}
}

void	slash_condition(t_cmds *cmds, t_env *env)
{
	struct stat	buf;

	if (stat(cmds->args[0], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			(1) && (ft_putstr_fd("minishell: ", 2),
				ft_putstr_fd(cmds->args[0], 2),
				ft_putstr_fd(": is a directory\n", 2), exit(126), 0);
	}
	if (execve(cmds->args[0], cmds->args, environement(env)) < 0)
	{
		accessebility(cmds);
		if (errno == 2)
			(1) && (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmds->args[0],
				2), ft_putstr_fd(": No such file or directory\n",
					2), exit(127), 0);
		else if (errno == 13)
			(1) && (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmds->args[0],
				2), ft_putstr_fd(": Permission denied\n", 2), exit(126), 0);
		else
			(1) && (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmds->args[0],
				2), ft_putstr_fd(": command not found\n", 2), exit(127), 0);
	}
}

int	handle_one_cmd(t_cmds *cmd, t_env **env)
{
	if (open_rediractions_parent(cmd) < 0)
		return (1);
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (dup2(cmd->fdin, 0) < 0)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd
			(strerror(errno), 2), ft_putstr_fd("\n", 2), 1);
	if (dup2(cmd->fdout, 1) < 0)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd
			(strerror(errno), 2), ft_putstr_fd("\n", 2), 1);
	if (cmd->fdin != 0)
		close(cmd->fdin);
	if (cmd->fdout != 1)
		close(cmd->fdout);
	return (ft_is_builtin(cmd, env));
}

int	open_rediractions_parent(t_cmds *cmds)
{
	t_list	*red;

	red = cmds->red;
	while (red)
	{
		if (red_in_out(cmds, red) < 0 || red_app_ambg(cmds, red) < 0)
			return (-1);
		if (red->type == nofile)
		{
			(cmds->fdin > 0 && cmds->fdout > 1) && (close(cmds->fdout),
			close(cmds->fdin));
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(red->content, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (-1);
		}
		red = red->next;
	}
	return (0);
}
