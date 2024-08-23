/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:49:15 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/22 23:02:01 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*lstnew_red(t_list *lst_node, t_env *env, t_list *lst, t_cmds *cmds)
{
	t_list	*node;
	char	*str;

	node = NULL;
	if (lst_node->type == herdoc)
	{
		node = ft_lstnew(NULL);
		if (!node)
			ft_free_exit(&lst, &env, &cmds, "failed malloc\n");
		node->fd = process_herdoc(lst_node->next->content,
				lst_node->next->type, env, lst);
		node->type = herdoc;
	}
	else
	{
		str = ft_strdup(lst_node->next->content);
		if (!str)
			ft_free_exit(&lst, &env, &cmds, "failed malloc\n");
		node = ft_lstnew(str);
		if (!node)
			ft_free_exit(&lst, &env, &cmds, "failed malloc\n");
		node->type = lst_node->type;
	}
	return (node);
}

t_list	*handll_red(t_list *lst, t_list *list, t_env *env, t_cmds *cmds)
{
	t_list	*red;
	t_list	*tmp;
	t_list	*node;

	red = NULL;
	tmp = lst;
	while (tmp && tmp->next && tmp->type != Pipe)
	{
		if (tmp->type > 0 && tmp->type < 5)
		{
			node = lstnew_red(tmp, env, list, cmds);
			if (tmp->next && tmp->next->type == ambigus)
				node->type = ambigus;
			if (tmp->next && tmp->next->content[0] == '\0')
				node->type = nofile;
			ft_lstadd_back(&red, node);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (red);
}

t_cmds	*ft_lstnew_cmd(t_list **lst, t_list *lst1, t_env *env, t_cmds *cmds)
{
	t_cmds	*node;
	int		i;

	i = 0;
	node = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node)
		ft_free_exit(&lst1, &env, &cmds, "failed malloc");
	if (!lst)
	{
		node->red = NULL;
		node->args = NULL;
	}
	else
	{
		node->red = handll_red(*lst, lst1, env, cmds);
		node->args = get_args(lst, lst1, env, cmds);
	}
	node->fdin = -1337;
	node->fdout = -1337;
	node -> next = NULL;
	return (node);
}

void	lst_addback_cmd(t_list **node, t_list *lst, t_env *env, t_cmds **cmds)
{
	t_cmds	*new;

	new = ft_lstnew_cmd(node, lst, env, *cmds);
	if (!new)
		ft_free_exit(&lst, &env, cmds, "failed malloc");
	ft_lstadd_back_cmd(cmds, new);
}

t_cmds	*list_cmds(t_list *lst, t_env *env)
{
	t_cmds	*cmds;
	t_list	*tmp;

	cmds = NULL;
	tmp = lst;
	if (!lst)
		return (NULL);
	if (tmp->type == Pipe)
		lst_addback_cmd(NULL, lst, env, &cmds);
	while (tmp)
	{
		if (tmp && tmp->type != Pipe)
			lst_addback_cmd(&tmp, lst, env, &cmds);
		if (tmp && ((tmp->type == Pipe && tmp->next && tmp->next->type == Pipe)
				|| (tmp->type == Pipe && !tmp->next)))
			lst_addback_cmd(NULL, lst, env, &cmds);
		tmp && (tmp = tmp->next);
	}
	return (cmds);
}
