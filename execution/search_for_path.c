/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:16:40 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/13 20:27:46 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	directory_or_file(char *cmd, t_cmds *cmds)
{
	struct stat	buf;

	if (ft_strchr(cmd, '.') && !ft_strchr(cmd, '/'))
	{
		if (ft_strlen(cmd) == 1 && cmds->args[1] == NULL)
		{
			printf("minishell: .: filename argument required\n");
			printf(".: usage: . filename [arguments]\n");
			exit(2);
		}
		else if (ft_strlen(cmd) == 1 && cmds->args[1] != NULL)
		{
			if (stat(cmds->args[1], &buf) == 0)
			{
				if (S_ISDIR(buf.st_mode))
				{
					printf("minishell: %s: is a directory\n", cmds->args[1]);
					exit(1);
				}
			}
			if (execve(cmds->args[1], cmds->args + 1, NULL) == -1)
			{
				if (errno == 2)
				{
					printf("minishell: %s: No such file or directory\n", cmds->args[1]);
					exit(1);
				}
				else
				{
					printf("minishell: %s: command not found\n", cmds->args[1]);
					exit(1);
				}
			}
		}
	}
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &buf) == 0)
		{
			if (S_ISDIR(buf.st_mode))
			{
				printf("minishell: %s: is a directory\n", cmd);
				exit(126);
			}
		}
	}
	// else
	// {
	// 	printf("cmd : %s\n", cmd);
	// 	if (execve(cmd, NULL, NULL) == -1)
	// 	{
	// 		printf("minishell: %s: command not found\n", cmd);
	// 		exit(127);
	// 	}
	// }
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

	path = ft_getenv("PATH", env);
	if (!path)
		return (NULL);
	paths = ft_split_execution(path, ':');
	i = 0;
	while (paths[i] /*&& (!ft_strchr(cmd, '.')) && ft_strlen(cmd) > 1*/)
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (!access(tmp, X_OK))
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
