/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:58:19 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/15 13:19:49 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	 remove_quotes(t_list *list)
{
	t_list	*tmp;
    char    *tmp_var;

	if (!list)
		return ;
	tmp = list;
	while (tmp)
	{
		if(tmp->type == squot || tmp->type == dquot)
		{
			tmp_var = tmp->content;
			tmp->content = ft_substr(tmp->content, 1, ft_strlen(tmp->content) - 2);
            free(tmp_var);
		}
		tmp = tmp->next;
	}
}

char	*expand_var_dqout(char *varaible, t_env *env)
{
	char	*tmp;

	if ( varaible && !varaible[1])
		return(varaible);
	tmp = varaible;
	varaible = ft_getenv(varaible + 1, env);
    if(!varaible)
        return (NULL);
    varaible = ft_strdup(varaible);
    free(tmp);
	return varaible;
}

void	expand_var(char *var, t_env *env, t_list **lst)
{
    char    *tmp;    
	char	**strs;
	int		i;
	t_list	*node;
	
	i = 0;
	tmp = var;
	var = ft_getenv(var + 1, env);
    if(!var)
	{
		(*lst)->content = NULL;
		//ft_remove_node(lst);
		free(tmp); 
    	return ;
	}
	free(tmp);
	strs = ft_split(var);
	if (!strs)
		return ;
	if (var[0] == ' ' || var[0] == '\t')
	{
		(*lst)->content = ft_strdup(" ");
		(*lst)->type = space;
	}
	else
	{
		if (!strs[0])
			return ;
		(*lst)->content = strs[i++];
	}
	while(strs[i])
	{
		if (i == 1)
		{
			node = ft_lstnew(ft_strdup(" "));
			node->type = space;
			ft_lstadd_midl(lst, node);
			(*lst) = (*lst)->next;
		}
		node = ft_lstnew(strs[i++]);
		node->type = word;
		ft_lstadd_midl(lst, node);
		(*lst) = (*lst)->next;
	}
	if (var[ft_strlen(var) - 1] == ' ' || var[ft_strlen(var) - 1] == '\t')
	{
		node = ft_lstnew(ft_strdup(" "));
		node->type = space;
		ft_lstadd_midl(lst, node);
		(*lst) = (*lst)->next;
	}
}

char    *get_str(char *str, int *indx, t_env *env)
{
    int i;
    char    *str1;
    int    k;

    i = *indx;
    k = *indx;
    if (str[i] == '$')
    {
        i++;
        while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') ||
                (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_' ||
            (str[i] >= '0' && str[i] <= '9')))
            i++;
    }
    else
        while(str[i] && str[i] != '$')
            i++;
    str1 = ft_substr(str, k, i - k);
    if (str1 && str1[0] == '$')
        str1 = expand_var_dqout(str1, env);
    *indx = i;
    return (str1);
}

char    *expand_dquot(char *str, t_env *env)
{
    char    *str1;
    char    *str2;
    int        i;

    i = 0;
    str1 = get_str(str, &i, env);
    while(str[i])
    {
        str2 = get_str(str, &i, env);
        str1 = ft_strjoin_free(str1, str2);
    }
    return (str1);
}

// int	check_nofile(t_list	*lst)
// {
// 	t_list	*tmp;

// 	tmp = lst;
// 	while (tmp && tmp->type != space && tmp->type > 4)
// 	{
// 		// if (tmp->type == dquot && tmp->content == '\0')
// 		// 	return (1);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// void	flag_nofile(t_list **lst)
// {
// 	t_list	*tmp;
// 	int		nofile;
	
// 	tmp = *lst;
// 	while(tmp)
// 	{
// 		nofile = 0;
// 		if (tmp->type > 0 && tmp->type < 5)
// 		{
// 			tmp = tmp->next;
// 			if (tmp->type == space)
// 				tmp = tmp->next;
// 			nofile = check_nofile(tmp);
// 			while(tmp && tmp->type != space  && tmp->type > 4)
// 			{
// 				if (nofile)
// 					tmp->type = nofile;
// 				tmp = tmp->next;
// 			}
// 		}
// 		tmp && (tmp->type != space && tmp->type > 4) && (tmp = tmp->next);
// 	}
// }

void	expand(t_list *lst, t_env *env)
{
	t_list	*tmp;
	char	*str_tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type == var)
			expand_var(tmp->content, env, &tmp);
		if (tmp->type == dquot)
		{
			str_tmp = tmp->content;
			tmp->content = expand_dquot(tmp->content, env);
			free(str_tmp);
			str_tmp = NULL;
		}
		tmp && (tmp = tmp->next);
	}
	//flag_nofile(&lst);
	remove_empty_node(&lst);
}
