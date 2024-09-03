/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:45:24 by aboulakr          #+#    #+#             */
/*   Updated: 2024/09/02 00:37:21 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	accessebility(t_cmds *cmds)
{
	if (access(cmds->args[0], X_OK) == -1)
	{
		if (errno == 13)
			print_error_and_exit(cmds, "Permission denied\n", 126);
		else
			print_error_and_exit(cmds, "command not found\n", 127);
	}
}

void	handle(t_cmds *cmds, t_env *env)
{
	if (!access(cmds->args[0], X_OK) || find_path(cmds->args[0], env))
	{
		if (execve(find_path(cmds->args[0], env),
				cmds->args, environement(env)) == -1)
			handle_execve_error(cmds, env);
	}
	accessebility(cmds);
	if (!find_path(cmds->args[0], env)
		&& access(cmds->args[0], X_OK) == -1)
		print_error_and_exit(cmds, "command not found\n", 127);
}

void	print_error_and_exit(t_cmds *cmds, char *error_msg, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmds->args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	exit(exit_code);
}

void	handle_other_error(t_cmds *cmds, t_env *env)
{
	if (!ft_getenv("PATH", env))
	{
		cmds->args[0] = ft_strjoin("./", cmds->args[0]);
		slash_condition(cmds, env);
	}
	print_error_and_exit(cmds, "command not found\n", 127);
}

void	handle_execve_error(t_cmds *cmds, t_env *env)
{
	if (errno == 2)
		print_error_and_exit(cmds, "No such file or directory\n", 127);
	else if (errno == 13)
		print_error_and_exit(cmds, "Permission denied\n", 126);
	else
		handle_other_error(cmds, env);
}
