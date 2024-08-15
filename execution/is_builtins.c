/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:16:44 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/15 15:52:00 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_builtin(t_cmds *cmds)
{
	if (!cmds)
		exit(0);
	if (cmds->args[0])
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
	}
	return (0);
}

int	ft_is_builtin(t_cmds *cmds, t_env **env)
{
	t_export	tmp;
	int			k;

	if (!cmds)
		exit(0);
	k = 0;
	if (cmds->args[0])
	{
		if (ft_strncmp(cmds->args[0], "echo", 5) == 0)
			echo(cmds->args);
		else if (ft_strncmp(cmds->args[0], "cd", 3) == 0)
			cd(cmds->args, *env);
		else if (ft_strncmp(cmds->args[0], "pwd", 4) == 0)
			pwd();
		else if (ft_strncmp(cmds->args[0], "export", 7) == 0)
			k = export(cmds->args, env, 0, &tmp);
		else if (ft_strncmp(cmds->args[0], "unset", 6) == 0)
			k = unset(cmds->args, env, 0, 0);
		else if (ft_strncmp(cmds->args[0], "env", 4) == 0)
			ft_print_env(*env);
		else
			return (-1);
	}
	return (k);
}

