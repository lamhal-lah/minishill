/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:16:40 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/28 22:37:29 by aboulakr         ###   ########.fr       */
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

void	error_management(t_cmds *cmds, t_env *env)
{
	another_condition(cmds);
	if (!ft_strchr(cmds->args[0], '/') && !check_if_builtin(cmds))
	{
		if (!cmds->args[0] || !ft_strlen(cmds->args[0]))
			(1) && (ft_putstr_fd("minishell: : command not found\n", 2),
						exit(127), 0);
		(!ft_strncmp(cmds->args[0], ".", ft_strlen(cmds->args[0]) + 1)
			&& ft_strlen(cmds->args[0]) == 1) && (ft_handle_dot(cmds, env), 0);
		if (!check_if_builtin(cmds))
			handle(cmds, env);
	}
	else
		(check_if_builtin(cmds)) && (exit(ft_is_builtin(cmds, &env)), 0);
	(ft_strchr(cmds->args[0], '/')) && (slash_condition(cmds, env), 0);
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
