/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:53:05 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/01 03:33:27 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_remove_node(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !(*lst))
		return ;
	tmp = *lst;
	*lst = (*lst)->next;
	free(tmp->content);
	free(tmp);
}

void	remove_quotes(t_list *list, t_pars *parsg)
{
	t_list	*tmp;
	char	*tmp_var;

	if (!list)
		return ;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == squot || tmp->type == dquot)
		{
			tmp_var = tmp->content;
			tmp->content = ft_substr(tmp->content, 1,
					ft_strlen(tmp->content) - 2);
			if (!tmp->content)
				ft_free_exit(parsg, "failled malloc\n");
			free(tmp_var);
		}
		tmp = tmp->next;
	}
}

void	remove_empty_node(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp && tmp->next)
	{
		if (tmp->next->type == var && tmp->next->content == NULL)
			ft_remove_node(&tmp->next);
		else
			tmp = tmp->next;
	}
	tmp = *lst;
	while (tmp && tmp->next)
	{
		if (tmp->type == space && tmp->next->type == space)
			ft_remove_node(&tmp->next);
		else
			tmp = tmp->next;
	}
}

void	remove_spaces(t_list **lst)
{
	t_list	*tmp;

	while ((*lst) && (*lst)->type == space)
		ft_remove_node(lst);
	tmp = *lst;
	while (tmp && tmp->next)
	{
		if (tmp->next->type == space)
			ft_remove_node(&tmp->next);
		else
			tmp = tmp->next;
	}
}
