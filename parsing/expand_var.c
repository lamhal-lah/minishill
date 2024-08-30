/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:53:57 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/29 12:27:58 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_var(char *var, t_list **node, t_env *env, t_list **lst)
{
	char	**strs;

	strs = ft_split(var);
	if (!strs)
		(ft_lstclear(lst), ft_lstclear_env(&env),
			ft_putstr_fd("failed allocation", 2), exit (1));
	if (var[0] == ' ' || var[0] == '\t')
	{
		(*node)->content = ft_strdup(" ");
		(*node)->type = word;
	}
	else
	{
		if (!strs[0])
			return (NULL);
		(*node)->content = ft_strdup(strs[0]);
	}
	return (strs);
}

void	ft_add_in_lst(char *str, t_list **node, t_env *env, t_list **lst)
{
	char	*str1;
	t_list	*new;

	str1 = ft_strdup(str);
	if (!str1)
		(ft_lstclear(lst), ft_lstclear_env(&env),
			ft_putstr_fd("failed allocation", 2), exit (1));
	new = ft_lstnew(str1);
	if (!new)
		(ft_lstclear(lst), ft_lstclear_env(&env),
			ft_putstr_fd("failed allocation", 2), exit (1));
	new->type = word;
	ft_lstadd_midl(node, new);
	(*node) = (*node)->next;
}

void	expand_in_token(char *var, t_env *env, t_list **node, t_list **lst)
{
	char	**strs;
	int		i;

	strs = split_var(var, node, env, lst);
	i = (ft_strncmp((*node)->content, " ", 2));
	while (strs[i])
	{
		if (i != 0)
			ft_add_in_lst(" ", node, env, lst);
		ft_add_in_lst(strs[i++], node, env, lst);
	}
	if (var[ft_strlen(var) - 1] == ' ' || var[ft_strlen(var) - 1] == '\t')
		ft_add_in_lst(" ", node, env, lst);
	ft_free(strs, i);
}

void	expand_var(char *var, t_env *env, t_list **node, t_list **lst)
{
	char	*tmp;

	tmp = var;
	var = ft_getenv(var + 1, env);
	if (!var)
	{
		(*node)->content = NULL;
		free(tmp);
		return ;
	}
	free(tmp);
	expand_in_token(var, env, node, lst);
}
