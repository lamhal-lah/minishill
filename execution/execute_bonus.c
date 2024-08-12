/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:54:55 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/12 16:58:51 by aboulakr         ###   ########.fr       */
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
	while (fd[++x])
	{
		close(fd[x][0]);
		close(fd[x][1]);
	}
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
