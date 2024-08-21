/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:49:15 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/21 19:21:27 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arg(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp && tmp->type != Pipe)
	{
		if (tmp->type > 0 && tmp->type < 5)
		{
			tmp = tmp->next->next;
		}
		else
		{
			i++;
			tmp && (tmp = tmp->next);
		}
	}
	return (i);
}

char	**get_args(t_list **lst)
{
	char	**args;
	t_list	*tmp;
	int		i;

	tmp = *lst;
	i = 0;
	args = malloc((count_arg(*lst) + 1) * sizeof(char **));
	while (tmp && tmp->type != Pipe)
	{
		if (tmp->type > 0 && tmp->type < 5)
			tmp = tmp->next->next;
		else
		{
			args[i++] = ft_strdup(tmp->content);
			tmp = tmp->next;
		}
	}
	*lst = tmp;
	args[i] = NULL;
	return (args);
}

t_list	*handll_red(t_list *lst, t_env *env)
{
	t_list	*red;
	t_list	*tmp;
	t_list	*node;
	char	*str;

	red = NULL;
	tmp = lst;
	while (tmp && tmp->next && tmp->type != Pipe)
	{
		if (tmp->type > 0 && tmp->type < 5)
		{
			if (tmp->type == herdoc)
			{
				node = ft_lstnew(NULL);
				node->fd = process_herdoc(tmp->next->content,
						tmp->next->type, env, lst);
				node->type = herdoc;
			}
			else
			{
				str = ft_strdup(tmp->next->content);
				node = ft_lstnew(str);
				node->type = tmp->type;
			}
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

t_cmds	*ft_lstnew_cmd(t_list **lst, t_env *env)
{
	t_cmds	*node;
	int		i;

	i = 0;
	node = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	if (!lst)
	{
		node->red = NULL;
		node->args = NULL;
	}
	else
	{
		node->red = handll_red(*lst, env);
		node->args = get_args(lst);
	}
	node->fdin = -1337;
	node->fdout = -1337;
	node -> next = NULL;
	return (node);
}

t_cmds	*list_cmds(t_list *lst, t_env *env)
{
	t_cmds	*cmds;
	t_list	*tmp;
	t_cmds	*node;

	node = NULL;
	cmds = NULL;
	tmp = lst;
	if (!lst)
		return (NULL);
	if (tmp->type == Pipe)
	{
		node = ft_lstnew_cmd(NULL, env);
		ft_lstadd_back_cmd(&cmds, node);
	}
	while (tmp)
	{
		if (tmp && tmp->type != Pipe)
		{
			node = ft_lstnew_cmd(&tmp, env);
			ft_lstadd_back_cmd(&cmds, node);
		}
		else if ((tmp->type == Pipe && tmp->next && tmp->next->type == Pipe)
					|| (tmp->type == Pipe && !tmp->next ))
		{
			node = ft_lstnew_cmd(NULL, env);
			ft_lstadd_back_cmd(&cmds, node);
		}
		tmp && (tmp = tmp->next);
	}
	return (cmds);
}


void	ft_lst_join(t_list **lst)
{
	t_list	*tmp;
	char	*tmp_content;

	tmp = *lst;
	while (tmp && tmp->next)
	{
		if (tmp->type != space && tmp->type > 4)
		{
			while (tmp && tmp->next && tmp->next->type != space
				&& tmp->next->type > 4)
			{
				tmp_content = tmp->content;
				if (tmp->content || tmp->next->content)
				{
					tmp->content = ft_strjoin(tmp->content, tmp->next->content);
					if (tmp->content == NULL)
						(ft_lstclear(lst), exit(1));
				}
				free(tmp_content);
				if (tmp->type == limtr && tmp->next->type == limtr_qt)
					tmp->type = limtr_qt;
				ft_remove_node(&tmp->next);
			}
		}
		tmp && (tmp = tmp->next);
	}
	if ((*lst) && (*lst)->type == var && (*lst)->content == NULL)
		ft_remove_node(lst);
	remove_spaces(lst);
}
