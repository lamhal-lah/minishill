/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:39:48 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/26 12:01:55 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_jion(t_list *tmp, t_pars *pars)
{
	char	*tmp_content;

	tmp_content = tmp->content;
	if (tmp->content || tmp->next->content)
	{
		tmp->content = ft_strjoin(tmp->content, tmp->next->content);
		if (tmp->content == NULL)
			ft_free_exit(pars, "failled malloc\n");
	}
	free(tmp_content);
	if (tmp->type == limtr && tmp->next->type == limtr_qt)
		tmp->type = limtr_qt;
}

void	ft_lst_join(t_list **lst, t_pars *pars)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp && tmp->next)
	{
		if (tmp->type != space && tmp->type > 4)
		{
			while (tmp && tmp->next && tmp->next->type != space
				&& tmp->next->type > 4)
			{
				lst_jion(tmp, pars);
				ft_remove_node(&tmp->next);
			}
		}
		tmp && (tmp = tmp->next);
	}
	if ((*lst) && (*lst)->type == var && (*lst)->content == NULL)
		ft_remove_node(lst);
	remove_spaces(lst);
}
