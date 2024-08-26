/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:16:40 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/26 03:10:10 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	another_condition(t_cmds *cmds)
{
	if (cmds->args[0][0] == '~' && cmds->args[0][1] == '/')
		cmds->args[0] = ft_strjoin("/Users/aboulakr", (cmds->args[0] + 1));
	else if (cmds->args[0][0] == '~' && cmds->args[0][1] == '\0')
		cmds->args[0] = ft_strdup("/Users/aboulakr");
}

void	error_management(t_cmds *cmds, t_env *env, int **fd, int i)
{
	another_condition(cmds);
	if (!ft_strchr(cmds->args[0], '/'))
	{
		(!ft_strncmp(cmds->args[0], ".", ft_strlen(cmds->args[0]) + 1)
			&& ft_strlen(cmds->args[0]) == 1) && (ft_handle_dot(cmds, env), 0);
		if (!cmds->args[0] || !ft_strlen(cmds->args[0]))
			(1) && (ft_putstr_fd("minishell: : command not found\n", 2),
				exit(127), 0);
		else if (!find_path(cmds->args[0], env) && !check_if_builtin(cmds)
			&& access(cmds->args[0], X_OK) == -1)
			(1) && (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmds->args[0],
				2), ft_putstr_fd(": command not found\n", 2), exit(127), 0);
		else
		{
			(check_if_builtin(cmds)) && (exit(ft_is_builtin(cmds, &env)), 0);
			if (!access(cmds->args[0], F_OK) || !access(cmds->args[0], X_OK))
				(execve(cmds->args[0], cmds->args, environement(env)) < 0)
				&& (perror("minishell"), 0);
			else if (execve(find_path(cmds->args[0], env),
					cmds->args, environement(env)) == -1)
				perror("minishell");
		}
	}
	(ft_strchr(cmds->args[0], '/')) && (slash_condition(cmds, env, fd, i), 0);
}

int	ft_lstsize(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	*find_path(char *cmd, t_env *env)
{
	char	*path;
	char	**paths;
	char	*tmp;
	int		i;

	(!ft_strncmp(cmd, "..", ft_strlen(cmd) + 1)) && (ft_putstr_fd
		("minishell: ..: command not found\n", 2), exit(127), 0);
	path = ft_getenv("PATH", env);
	if (!path)
		return (NULL);
	paths = ft_split_execution(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (!access(tmp, X_OK))
		{
			free(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (free(paths), NULL);
}

char	**environement(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	int		i;

	i = 0;
	tmp = env;
	envp = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin(envp[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
