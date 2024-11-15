/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:16:44 by aboulakr          #+#    #+#             */
/*   Updated: 2024/09/03 11:31:53 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_builtin(t_cmds *cmds)
{
	if (!cmds)
		return (0);
	if (cmds->args && cmds->args[0])
	{
		if (ft_strncmp(cmds->args[0], "echo", 5) == 0)
			return (1);
		else if (ft_strncmp(cmds->args[0], "cd", 3) == 0)
			return (1);
		else if (ft_strncmp(cmds->args[0], "pwd", 4) == 0)
			return (1);
		else if (ft_strncmp(cmds->args[0], "export", 7) == 0)
			return (1);
		else if (ft_strncmp(cmds->args[0], "unset", 6) == 0)
			return (1);
		else if (ft_strncmp(cmds->args[0], "env", 4) == 0)
			return (1);
		else if (ft_strncmp(cmds->args[0], "exit", 5) == 0)
			return (1);
	}
	return (0);
}

int	ft_is_builtin(t_cmds *cmds, t_env **env, int factor)
{
	t_export	tmp;
	int			k;

	(!cmds) && (exit(0), k = 0);
	k = 0;
	if (cmds->args[0])
	{
		if (ft_strncmp(cmds->args[0], "echo", 5) == 0)
			k = echo(cmds->args);
		else if (ft_strncmp(cmds->args[0], "cd", 3) == 0)
			k = cd(cmds->args, *env);
		else if (ft_strncmp(cmds->args[0], "pwd", 4) == 0)
			k = pwd(*env);
		else if (ft_strncmp(cmds->args[0], "export", 7) == 0)
			k = export(cmds->args, env, 0, &tmp);
		else if (ft_strncmp(cmds->args[0], "unset", 6) == 0)
			k = unset(cmds->args, env, 0, 0);
		else if (ft_strncmp(cmds->args[0], "env", 4) == 0)
			k = ft_print_env(*env);
		else if (ft_strncmp(cmds->args[0], "exit", 5) == 0)
			k = ft_exit(cmds->args, factor);
		else
			return (-1);
	}
	return (k);
}

static void	dup2_protection(t_cmds *cmds, int i)
{
	if (cmds->fdin > 0 && i == 0)
	{
		(dup2(cmds->fdin, 0) < 0) && (perror("dup2"), exit(1), 0);
		close(cmds->fdin);
	}
}

void	ft_check_redirections(t_cmds *cmd, int **fd, int i)
{
	dup2_protection(cmd, i);
	if (i > 0)
	{
		(cmd->fdin == -1337) && (cmd->fdin = fd[i - 1][0]);
		if (cmd->fdin > 0)
		{
			(dup2(cmd->fdin, 0) < 0) && (perror("dup2"), exit(1), 0);
			close(cmd->fdin);
		}
	}
	if (cmd->next != NULL)
	{
		(cmd->fdout == -1337) && (cmd->fdout = fd[i][1]);
		if (cmd->fdout > 1)
		{
			(dup2(cmd->fdout, 1) < 0) && (perror("dup2"), exit(1), 0);
			close(cmd->fdout);
		}
	}
	else if (cmd->next == NULL && cmd->fdout > 1)
	{
		(dup2(cmd->fdout, 1) < 0) && (perror("dup2"), exit(1), 0);
		close(cmd->fdout);
	}
}

size_t	ft_split_size(char **split)
{
	size_t	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}
