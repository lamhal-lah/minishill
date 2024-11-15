/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:50:25 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/23 16:40:46 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	unsigned char	*s;
	size_t			i;

	i = 0;
	s = malloc(n * sizeof(char) + 1);
	if (!s)
		(write(2, "allocation failed\n", 19), exit (EXIT_FAILURE));
	while (s1[i] && i < n)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return ((char *)s);
}

t_env	*ft_lstnew_env(char *env)
{
	t_env	*new;
	char	*equal;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	equal = ft_strchr(env, '=');
	if (equal)
	{
		(ft_strchr(env, '+')) && (new->key = ft_strndup(env, equal - env - 1));
		(!ft_strchr(env, '+')) && (new->key = ft_strndup(env, equal - env));
		new->value = ft_strdup(equal + 1);
		if (ft_strncmp(new->key, "OLDPWD", 7) == 0)
			return (free(new->value), new->value = NULL,
				new->printed = 0, new->next = NULL, new);
		if (!new->value || ft_strlen(new->value) == 0)
		{
			(new->value) && (free(new->value), 0);
			new->value = NULL;
		}
		new->printed = 1;
	}
	else
		(1) && (new->key = ft_strdup(env), new->value = NULL, new->printed = 0);
	return (new->next = NULL, new);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp -> next)
		tmp = tmp -> next;
	return (tmp);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	tmp = ft_lstlast_env(*lst);
	if (!tmp)
		*lst = new;
	else
		tmp->next = new;
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)-> next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	lst = NULL;
}
