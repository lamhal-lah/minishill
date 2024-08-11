/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:49:15 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/11 10:29:48 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arg(t_list *lst)
{
	int i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp && tmp->type != Pipe)
	{
		if (tmp->type > 0 &&  tmp->type < 5)
		{
			tmp = tmp->next->next; // < h < f < h
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
	int	i;

	tmp = *lst;
	i = 0;
	//args = NULL;
	args = malloc((count_arg(*lst) + 1)* sizeof(char **));
	//printf("%p\n", args);
	while(tmp && tmp->type != Pipe)
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
// void	handl_redin(t_list **lst, t_cmds *node)
// {
// 	if(node->fdin != -1337)
// 		close(node->fdin);
// 	node->fdin = open((*lst)->next->content, O_RDONLY);
// 	if (node->fdin == -1)
// 	{
// 		perror("failed open");
// 		node->args = NULL;
// 	}
// 	*lst = (*lst)->next;
// }

// void	handl_redout(t_list **lst, t_cmds *node)
// {
// 	if(node->fdout != -1337)
// 		close(node->fdout);
// 	if ((*lst)->type == red_out)
// 	{
// 		node->fdout = open((*lst)->next->content, O_RDONLY | O_CREAT | O_TRUNC , 0777);
// 		if (node->fdout == -1)
// 		{
// 			perror("failed open");
// 			node->args = NULL;
// 		}
// 		*lst = (*lst)->next;
// 	}
// 	else if ((*lst)->type == append)
// 	{
// 		node->fdout = open((*lst)->content, O_RDONLY | O_CREAT | O_APPEND , 0777);
// 		if (node->fdout == -1)
// 		{
// 			perror("failed open");
// 			node->args = NULL;
// 		}
// 		*lst = (*lst)->next;
// 	}
// }

// void	fill_node_cmd(t_list **lst, t_cmds *node)
// {
// 	t_list	*tmp;

// 	tmp = *lst;
// 	while(*lst && (*lst)->type != Pipe)
// 	{
// 		if ((*lst)->type == red_in)
// 		{
// 			handl_redin(lst, node);
// 			if (node->fdin == -1)
// 				return ;
// 		}
// 		else if ((*lst)->type == red_out || (*lst)->type == append)
// 		{
// 			handl_redout(lst, node);
// 			if (node->fdin == -1)
// 				return ;
// 		}
// 		*lst && (*lst = (*lst)->next);
// 	}
//}

t_list	*handll_red(t_list *lst)
{
	t_list	*red;
	t_list	*tmp;
	t_list	*node;
	char	*str;

	red = NULL;
	tmp = lst;
	while (tmp && tmp->next && tmp->type != Pipe)
	{
		if(tmp->type > 0 && tmp->type < 5)
		{
			str = ft_strdup(tmp->next->content);
			node = ft_lstnew(str);
			node->type = tmp->type;
			ft_lstadd_back(&red, node);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (red);
}

t_cmds	*ft_lstnew_cmd(t_list **lst)
{
	t_cmds	*node;
	int		i;

	i = 0;
	node = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	// node->args = malloc((count_arg(*lst) + 1)* sizeof(char *));
	// if (!node->args)
	// 	return (NULL);
	node->red = handll_red(*lst);
	node->args = get_args(lst);
	node -> next = NULL;
	return (node);
}

t_cmds    *list_cmds(t_list *lst)
{
	t_cmds  *cmds;
	t_list	*tmp;
	t_cmds	*node;

	node = NULL;
	cmds = NULL;
	tmp = lst;
	while (tmp)
	{
		if (tmp && tmp->type != Pipe)
		{
			node = ft_lstnew_cmd(&tmp);
			ft_lstadd_back_cmd(&cmds, node);
		}
		tmp && (tmp = tmp->next);
	}
	return (cmds);
}

void	remove_spaces(t_list **lst)
{
	t_list	*tmp;
	
	tmp = *lst;
	while(tmp && tmp->next)
	{
		if (tmp->next->type == space)
			ft_remove_node(&tmp->next);
		else
			tmp = tmp->next;
	}
}

void	ft_lst_join(t_list **lst)
{
	t_list	*tmp;
	char	*tmp_content;

	tmp = *lst;
	while(tmp && tmp->next)
	{
		if (tmp->type != space && tmp->type > 4)
		{
			while(tmp && tmp->next && tmp->next->type != space && tmp->next->type > 4)
			{
				tmp_content = tmp->content;
				tmp->content = ft_strjoin(tmp->content, tmp->next->content);
				free(tmp_content);
				if (tmp->type == limtr && tmp->next->type == limtr_qt)
					tmp->type = limtr_qt;
				ft_remove_node(&tmp->next);
			}
		}
		tmp && (tmp = tmp->next);
	}
	remove_spaces(lst);
}

