/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:54:55 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/14 20:27:08 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	middle_commands(t_cmds *cmd, t_env *env, int **fd, int i)
{
	int	x;

	x = -1;
	if (open_rediractions(cmd) < 0)
		exit(1);
	//ft_check_redirections(cmd, fd, i);
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
	error_management(cmd, env, fd, i);
	while (fd[++x])
	{
		close(fd[x][0]);
		close(fd[x][1]);
	}
}

void	ft_handle_dot(t_cmds *cmds, t_env *env, int **fd, int i)
{
	struct stat	buf;

	if (cmds->args[1] == NULL)
	{
		printf("minishell: .: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
		exit(2);
	}
	if (cmds->args[1] != NULL)
	{
		if (ft_strchr(cmds->args[1], '/'))
			slash_condition(cmds +1, env, fd, i);
		if (stat(cmds->args[1], &buf) == 0)
		{
			if (S_ISDIR(buf.st_mode))
			{
				printf("minishell: %s: is a directory\n", cmds->args[1]);
				exit(126);
			}
		}
		if (!find_path(cmds->args[1], env))
		{
			printf("minishell: %s: No such file or directory\n", cmds->args[1]);
			exit(1);
		}
		else
			if (execve(cmds->args[1], cmds->args, environement(env)) < 0)
				perror("minishell");
	}
}

void	slash_condition(t_cmds *cmds, t_env *env, int **fd, int i)
{
	struct stat	buf;

	if (stat(cmds->args[0], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			printf("minishell: %s: is a directory\n", cmds->args[0]);
			exit(126);
		}
	}
	if (!find_path(cmds->args[0], env) && access(cmds->args[0], F_OK) == -1)
	{
		printf("minishell: %s: No such file or directory\n", cmds->args[0]);
		exit(127);
	}
	else
	{
		ft_check_redirections(cmds, fd, i);
		if (execve(cmds->args[0], cmds->args, environement(env)) < 0)
			perror("minishell");
	}
}

