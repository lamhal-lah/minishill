/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:16:44 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/12 15:43:26 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_builtin(t_cmds *cmds, t_env *env)
{
	t_export	tmp;

	if (!cmds)
		return (0);
	if (cmds->args[0])
	{
		if (ft_strncmp(cmds->args[0], "echo", 5) == 0)
			echo(cmds->args);
		else if (ft_strncmp(cmds->args[0], "cd", 3) == 0)
			cd(cmds->args, env);
		else if (ft_strncmp(cmds->args[0], "pwd", 4) == 0)
			pwd();
		else if (ft_strncmp(cmds->args[0], "export", 7) == 0)
			export(cmds->args, &env, 0, &tmp);
		else if (ft_strncmp(cmds->args[0], "unset", 6) == 0)
			unset(cmds->args, &env);
		else if (ft_strncmp(cmds->args[0], "env", 4) == 0)
			ft_print_env(env);
		// else if (ft_strncmp(cmds->args[0], "exit", 5) == 0)
		//     ft_exit(cmds, env);
		else
			return (0);
	}
	return (1);
}
