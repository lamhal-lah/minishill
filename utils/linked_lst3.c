/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:47:18 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/09 17:01:09 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*ft_lstlast_cmd(t_cmds *lst)
{
	t_cmds	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	if (!lst || !new)
		return ;
	tmp = ft_lstlast_cmd(*lst);
	if (!tmp)
		*lst = new;
	else
		tmp->next = new;
}

void	ft_lstadd_front_cmd(t_cmds **l, t_cmds *new)
{
	if (!new || !l)
		return ;
	new -> next = *l;
	*l = new;
}


void	ft_lstclear_cmd(t_cmds **lst)
{
	t_cmds	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)-> next;
		//free(tmp->content);
        free(tmp);
	}
    lst = NULL;
}