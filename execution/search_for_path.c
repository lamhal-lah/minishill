/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:16:40 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/12 19:03:48 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	path = ft_getenv("PATH", env);
	if (!path)
		return (NULL);
	paths = ft_split_execution(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (!access(tmp, F_OK) || !access(tmp, X_OK))
		{
			free(path);
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

int	ft_cmdsize(t_cmds *cmd)
{
	int		i;
	t_cmds	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
