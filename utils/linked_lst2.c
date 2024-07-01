/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:50:25 by lamhal            #+#    #+#             */
/*   Updated: 2024/07/01 17:02:40 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew_env(char *env)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node -> env = env;
	node -> next = NULL;
	return (node);
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
		free(tmp->env);
        free(tmp);
	}
    lst = NULL;
}