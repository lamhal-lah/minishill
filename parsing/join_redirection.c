/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:26:24 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/02 01:17:30 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_join_infile(t_list **lst, t_pars *pars)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp && tmp->next && tmp->next->type != space && tmp->next->type > 4)
	{
		lst_jion(tmp, pars);
		ft_remove_node(&tmp->next);
	}
	if (tmp->type != ambigus)
		tmp->type = word;
}

void	expand_join_infile(t_env *env, t_list **lst, t_pars *pars)
{
	t_list	*tmp;
	t_list	*tmp1;
	char	*tmp_char;

	tmp = *lst;
	tmp = tmp->next;
	(tmp->type == space) && (tmp = tmp->next);
	tmp1 = tmp;
	while (tmp && tmp->type != space && tmp->type > 4)
	{
		if (tmp->type == var)
			expand_var(tmp->content, env, &tmp, pars);
		else if (tmp->type == dquot)
		{
			tmp_char = tmp->content;
			tmp->content = expand_dquot(tmp->content, env, pars);
			free(tmp_char);
		}
		tmp = tmp->next;
	}
	*lst = tmp;
	ft_lst_join_infile(&tmp1, pars);
}
