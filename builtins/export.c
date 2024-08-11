/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:17:46 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/11 10:29:48 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp_ex(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	a1 = (unsigned char *)s1;
	a2 = (unsigned char *)s2;
	i = 0;
	while ((a1[i] || a2[i]) && i < n)
	{
		if (a1[i] != a2[i])
			return (a1[i] - a2[i]);
		i++;
	}
	if (a1[i] && a1[i] != '+')
		return (-1);
	return (0);
}

int	ft_fill(char **key, char **value, char *str)
{
	if (ft_strchr(str, '=') && ft_strlen(str) > 1)
	{
		*key = ft_substr(str, 0, ft_strchr(str, '=') - str);
		if (!*key)
			return (1);
		*value = ft_strdup(ft_strchr(str, '=') + 1);
		if (!*value || ft_strlen(*value) == 0)
		{
			if (*value)
				free(*value);
			*value = NULL;
		}
	}
	else
	{
		*key = ft_strdup(str);
		if (!*key)
			return (1);
		*value = NULL;
	}
	if (ft_check_key(*key, '+') > 1 || !check_first_char(*key))
	{
		(1) && (free(*key), free(*value),
		printf("minishell: export: `%s': not a valid identifier\n", str));
		return (1);
	}
	if (ft_strchr(*key, '_') && ft_strlen(*key) == 1)
		return (free(*key), free(*value), 1);
	return (0);
}

int	ft_if(char *str, char **new_key, char **new_value, t_env **env)
{
	if (ft_strchr(str, '=') && !ft_strchr(*new_key, '+')
		&& !ft_strncmp_ex(*new_key, (*env)->key, ft_strlen((*env)->key)))
	{
		(1) && (free((*env)->value), (*env)->value = *new_value);
		return ((*env)->printed = 1, 0);
	}
	else if (ft_strchr(str, '=') && ft_strchr(*new_key, '+')
		&& !ft_strncmp_ex(*new_key, (*env)->key, ft_strlen((*env)->key)))
	{
		(1) && ((*env)->value = ft_strjoin_free((*env)->value, *new_value));
		return ((*env)->printed = 1, 0);
	}
	else if (!ft_strchr(str, '=') && ft_strchr(*new_key, '+'))
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return (0);
	}
	else if (!ft_strchr(str, '=')
		&& !ft_strncmp_ex(*new_key, (*env)->key, ft_strlen((*env)->key)))
	{
		if ((*env)->value == NULL)
			return (0);
		return ((*env)->printed = 1, 0);
	}
	return (1);
}

void	export(char **args, t_env **env, int i)
{
	t_env	*tmp;
	t_env	*new;
	char	*new_key;
	char	*new_value;

	while (++i && args[i])
	{
		(1) && (tmp = *env, new_key = NULL, new_value = NULL);
		if (ft_fill(&new_key, &new_value, args[i]))
			new_key = NULL;
		else
		{
			while (tmp)
			{
				if (!ft_if(args[i], &new_key, &new_value, &tmp))
					break ;
				tmp = tmp->next;
				if (!tmp)
				{
					if (help_export(env, &new, args[i]))
						return ;
					free(new_value);
					break ;
				}
			}
		}
		free(new_key);
	}
	ft_print_export(args, *env);
}

void	ft_print_export(char **args, t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (args[i])
		i++;
	if (i == 1)
	{
		while (tmp)
		{
			if (tmp->key && tmp->value != NULL)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			else if (tmp->printed == 1 && tmp->key && tmp->value == NULL)
				printf("declare -x %s=\"\"\n", tmp->key);
			else
				printf("declare -x %s\n", tmp->key);
			tmp = tmp->next;
		}
	}
	return ;
}
