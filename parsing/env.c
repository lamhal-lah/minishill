/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:53:54 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/05 10:44:52 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, ft_strlen(key) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*ft_env(char **env)
{
	int		i;
	t_env	*head;
	t_env	*tmp;

	i = 0;
	head = NULL;
	while (env[i])
	{
		tmp = ft_lstnew_env(env[i]);
		if (tmp == NULL)
		{
			ft_lstclear_env(&head);
			return (NULL);
		}
		if (head == NULL)
			head = tmp;
		else
			ft_lstadd_back_env(&head, tmp);
		i++;
	}
	shlvl(&head);
	return (head);
}
