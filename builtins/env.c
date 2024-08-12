/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:53:54 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/12 18:35:35 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*ft_getenv(char *key, t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(key, tmp->key, ft_strlen(key)) == 0)
// 			return (ft_strdup(tmp->value));
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// t_env	*ft_env(char **env)
// {
// 	int		i;
// 	t_env	*head;
// 	t_env	*tmp;

// 	i = 0;
// 	head = NULL;
// 	while (env[i])
// 	{
// 		tmp = ft_lstnew_env(env[i]);
// 		if (tmp == NULL)
// 		{
// 			ft_lstclear_env(&head);
// 			return (NULL);
// 		}
// 		ft_lstadd_back_env(&head, tmp);
// 		i++;
// 	}
// 	return (head);
// }

void	ft_print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && tmp->value != NULL)
			printf("=%s\n", tmp->value);
		else if (tmp->printed == 1 && tmp->key && tmp->value == NULL)
			printf("dfdfdf");
		tmp = tmp->next;
	}
}
