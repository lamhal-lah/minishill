/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:06:53 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/11 11:18:32 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_check_redirections(t_cmds *cmd, int *fd)
{
	if (cmd->fdin == PIPE)
	{
		if (dup2(fd[0], 0) == -1)
			perror("dup2");
		close(fd[0]);
	}
	else if (cmd->fdin >= 0)
	{
		if (dup2(cmd->fdin, 0) == -1)
			perror("dup2");
		close(cmd->fdin);
	}
	if (cmd->fdout == PIPE)
	{
		if (dup2(fd[1], 1) == -1)
			perror("dup2");
		close(fd[1]);
	}
	else if (cmd->fdout >= 0)
	{
		if (dup2(cmd->fdout, 1) == -1)
			perror("dup2");
		close(cmd->fdout);
	}
	
}

int	execute(t_cmds *cmd, t_env *env, int i)
{
	char **envp;
	int fake_in;
	int fake_out;
	int fd[2];
	int status;
	t_cmds *tmp;

	
	envp = environement(env);
	tmp = cmd;
	fake_in = dup(0);
	fake_out = dup(1);
	if (!tmp)
		return (0);
	if (tmp && ft_cmdsize(tmp) > 1)
	{
		// if (pipe(fd) == -1)
		// 	perror("pipe");
		// ft_first_command(tmp, envp,find_path(*tmp->args, env), fd);
		// tmp = tmp->next;
		while(tmp && i < ft_cmdsize(cmd) - 1)
		{
			if (pipe(fd) == -1)
				perror("pipe");
			middle_commands(tmp, envp, find_path(*tmp->args, env), fd);
			tmp = tmp->next;
			i++;
		}
		if (tmp->next == NULL)
			status = last_command(tmp, envp, find_path(*tmp->args, env), fd);
	}
	// else if (tmp && ft_cmdsize(tmp) == 2)
	// {
	// 	ft_first_command(tmp, envp, find_path(*tmp->args, env), fd);
	// 	tmp = tmp->next;
	// 	if (tmp)
	// 		status = last_command(tmp, envp, find_path(*tmp->args, env), fd);
	// }
	else
		status = last_command(tmp, envp, find_path(*tmp->args, env), fd);
	while(wait(NULL) > 0)
		;
	dup2(fake_in, 0);
	dup2(fake_out, 1);
	close(fake_in);
	close(fake_out);
	return (status);
}
