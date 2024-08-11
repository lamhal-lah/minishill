/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:07 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/11 10:29:48 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_value(char *key, char *value, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

void	cd(char **args, t_env *env)
{
	int		i;
	char	*path;
	char	*old_path;
	char	*tmp;

	(1) && (i = 0, tmp = NULL, path = NULL, old_path = getcwd(NULL, 0));
	while (args[i])
		i++;
	if (i >= 2 && !ft_strncmp(args[1], "~", 2))
		path = ft_getenv("HOME", env);
	else if (i == 1)
		path = ft_getenv("HOME", env);
	else
		path = ft_strdup(args[1]);
	if (chdir(path) != 0)
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
	else
	{
		tmp = getcwd(NULL, 0);
		change_env_value("OLDPWD", old_path, &env);
		change_env_value("PWD", tmp, &env);
	}
	(1) && (free(path), free(tmp), free(old_path), path = NULL);
}

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		perror("pwd");
	else
		printf("%s\n", path);
	free(path);
}
