/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:50:25 by lamhal            #+#    #+#             */
/*   Updated: 2024/07/04 15:10:11 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_env	*ft_lstnew_env(char *env)
// {
// 	t_env	*node;

// 	node = (t_env *)malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);
// 	node -> key = ;
// 	node -> next = NULL;
// 	return (node);
// }

t_env    *ft_lstnew_env(char *env)
{
    t_env *new;
    char *equal_sign;

    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    equal_sign = ft_strchr(env, '=');
    if (equal_sign)
    {
		new->key = ft_substr(env, 0, equal_sign - env);
        new->value = ft_strdup(equal_sign + 1);
        //new->type = 1;
    }
    else
    {
        new->key = ft_strdup(env);
        new->value = NULL;
        //new->type = 0;
    }
    new->next = NULL;
    return (new);
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

void	ft_lstadd_front_env(t_env **l, t_env *new)
{
	if (!new || !l)
		return ;
	new -> next = *l;
	*l = new;
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