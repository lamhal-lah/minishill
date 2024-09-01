/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:07 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/28 23:06:38 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_pwd(t_env **env, char *value, char *key, char *path)
{
	char	*tmp_key;
	char	*tmp2_key;

	(1) && (tmp_key = NULL, tmp2_key = NULL);
	tmp_key = ft_strjoin(key, "=");
	if (!ft_strncmp(key, "PWD", 4))
		tmp2_key = ft_strjoin(tmp_key, path);
	else
		tmp2_key = ft_strjoin(tmp_key, value);
	ft_lstadd_back_env(env, ft_lstnew_env(tmp2_key));
	free(tmp_key);
	free(tmp2_key);
}

void	change_env_value(char *key, char *value, t_env **env)
{
	t_env	*tmp;
	char	*path;

	(1) && (tmp = *env, path = NULL);
	path = getcwd(NULL, 0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
			return (free(tmp->value), tmp->value = ft_strdup(value),
				free(path));
		tmp = tmp->next;
		if (tmp == NULL)
		{
			if ((!ft_strncmp(key, "PWD", 4)) || !ft_strncmp(key, "OLDPWD", 7))
				handle_pwd(env, value, key, path);
		}
	}
	free(path);
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
		(tmp != NULL) && (change_env_value("PWD", tmp, &env), 0);
		change_env_value("OLDPWD", old_path, &env);
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
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	if (path)
		free(path);
	if (path == NULL)
		return (perror("pwd"), 1);
	return (0);
}
