/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:54:55 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/13 20:31:22 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	middle_commands(t_cmds *cmd, char **env, char *path, int **fd, int i)
{
	int	x;

	x = -1;
	if (open_rediractions(cmd) < 0)
		exit(1);
	ft_check_redirections(cmd, fd, i);
	directory_or_file(cmd->args[0], cmd);
	while (fd[++x])
	{
		close(fd[x][0]);
		close(fd[x][1]);
	}
	if (!cmd->args || !cmd->args[0])
		exit(0);
	printf("path = %s\n", path);
	if (!path)
	{
		if (execve(path, cmd->args, env) == -1)
		{
			printf("here\n");
			if (errno == 2)
			{
				printf("minishell: %s: No such file or directory\n", cmd->args[0]);
				exit(127);
			}
			else
			{
				printf("minishell: %s: command not found\n", cmd->args[0]);
				exit(127);
			}
		}
	}
	else
	{
		if (execve(path, cmd->args, env) == -1)
			perror("execve");
	}
}
