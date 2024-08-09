/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:54:55 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/07 11:56:30 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_first_command(t_cmds *cmd, char **env, char *path, int *fd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		printf("%s\n", path);
		ft_check_redirections(cmd, fd);
		if (!path)
		{
			if (execve(cmd->args[0], cmd->args, env) == -1)
				perror("execve");
		}
		else
		{
			if (execve(path, cmd->args, env) == -1)
				perror("execve");
		}
	}
}

void	middle_commands(t_cmds *cmd, char **env, char *path, int *fd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		ft_check_redirections(cmd, fd);
		if (!path)
		{
			if (execve(cmd->args[0], cmd->args, env) == -1)
				perror("execve");
		}
		else
		{
			if (execve(path, cmd->args, env) == -1)
				perror("execve");
		}
	}
}
int last_command(t_cmds *cmd, char **env, char *path, int *fd)
{
	int	pid;
	int status;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		ft_check_redirections(cmd, fd);
		if (!path)
		{
			if (execve(cmd->args[0], cmd->args, env) == -1)
				perror("execve");
		}
		else
		{
			if (execve(path, cmd->args, env) == -1)
				perror("execve");
		}
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));	
}

