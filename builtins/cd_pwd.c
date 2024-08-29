/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:07 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/28 08:31:45 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_value(char *key, char *value, t_env **env)
{
	t_env	*tmp;
	char	*path;

	(1) && (tmp = *env, path = NULL);
	path = getcwd(NULL, 0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	if (path && !ft_strncmp(key, "PWD", 4))
	{
		key = ft_strjoin(key, "=");
		key = ft_strjoin(key, path);
		ft_lstadd_back_env(env, ft_lstnew_env(key));
		free(path);
	}
}

int	cd(char **av, t_env *env)
{
	int		i;
	char	*path;
	char	*old_path;
	char	*tmp;

	(1) && (i = 0, tmp = NULL, old_path = NULL,
		path = NULL, old_path = getcwd(NULL, 0));
	while (av[i])
		i++;
	(i == 1) && (path = ft_strdup(ft_getenv("HOME", env)), 0);
	if (i >= 2 && !ft_strncmp(av[1], "~", ft_strlen(av[1])))
		path = ft_strdup(ft_getenv("HOME", env));
	else if (i >= 2 && ft_strncmp(av[1], "~", ft_strlen(av[1])))
		path = ft_strdup(av[1]);
	if (chdir(path) != 0)
		return (free(path), free(tmp), free(old_path), ft_putstr_fd
			("minishell: cd:", 2), ft_putstr_fd(av[1], 2), ft_putstr_fd (": ",
				2), ft_putstr_fd(strerror(errno), 2), ft_putstr_fd("\n", 2), 1);
	else
	{
		tmp = getcwd(NULL, 0);
		change_env_value("OLDPWD", old_path, &env);
		(tmp) && (change_env_value("PWD", tmp, &env), 0);
	}
	return (free(path), free(tmp), free(old_path), path = NULL, tmp = NULL, 0);
}

int	pwd(t_env *env)
{
	char	*path;

	path = NULL;
	path = getcwd(NULL, 0);
	if (path == NULL)
		path = ft_strdup(ft_getenv("PWD", env));
	if (path != NULL)
		printf("%s\n", path);
	if (path)
		free(path);
	if (path == NULL)
		return (perror("pwd"), 1);
	return (0);
}
