/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:58:19 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/08 12:04:26 by lamhal           ###   ########.fr       */
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
	
	i = 1;
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
	var = ft_strdup(var);
	if (!var)
		return ;
	strs = ft_split(var);
	if (!strs)
		return ;
	free(var);
	if (!strs[0])
		return ;
	(*lst)->content = strs[0];
	while(strs[i])
	{
		node = ft_lstnew(ft_strdup(" "));
		node->type = space;
		ft_lstadd_midl(lst, node);
		(*lst) = (*lst)->next;
		node = ft_lstnew(strs[i++]);
		node->type = word;
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
    free(str);
    return (str1);
}

void	remove_empty_node(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while(tmp && tmp->next)
	{
		if (tmp->next->type == space && tmp->next->next->content == NULL)
		{
			ft_remove_node(&tmp->next);
			ft_remove_node(&tmp->next);
		}
		else if(tmp->next->content == NULL)
			ft_remove_node(&tmp->next);
		else
			tmp = tmp->next;
	}
}

void	expand(t_list *lst, t_env *env)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type == var)
			expand_var(tmp->content, env, &tmp);
		if (tmp->type == dquot)
			tmp->content = expand_dquot(tmp->content, env);
		tmp && (tmp = tmp->next);
	}
	remove_empty_node(&lst);
}
// void	expand(t_list *lst, t_env *env)
// {
// 	t_list *tmp;
// 	char	*tmp1;
// 	int		i;
// 	char	*var;
// 	char	*prev;

// 	i = 0;
// 	tmp = lst;
// 	while (tmp->next)
// 	{
// 		if (tmp->type == var)
// 			tmp->content = expand_var(tmp->content, env);
// 		else if (tmp->type == dquot)
// 		{
// 			var = ft_strchr(tmp->content, '$');
// 			prev = ft_substr(tmp->content, 0, tmp->content - var);
// 			while(var)	
			
// 		}
// 	}
	
	
// }

// char	*get_env(char *var, t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(var, tmp->key, ft_strlen(var)) == 0)
// 			return (ft_strdup(tmp->env + ft_strlen(var) + 1));
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// char	expand_var(char *str, t_env env)
// {
// 	int		i;
// 	int		j;
// 	char	*var;
// 	char	*tmp;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] != 0)
// 		{
// 			j = i + 1;
// 			while (str[j] && str[j] != ' ' && str[j] != '$')
// 				j++;
// 			var = ft_substr(str, i, j - i);
// 			tmp = get_env(var, env);
// 			free(var);
// 			if (tmp)
// 			{
// 				str = ft_strjoin(str, tmp);
// 				free(tmp);
// 			}
// 		}
// 		i++;
// 	}
// 	return (str);
// }


// char	*expan_varaible(char *var, t_env *env)
// {
// 	int	i;
// 	int	j;
// 	int	nbr_var;
// 	char	**vars;

// 	i = 0;
// 	nbr_var;
// 	while (var[i])
// 	{
// 		if(var[i] == '$' && var[i + 1] != 0)
// 			nbr_var++;
// 		i++;
// 	}
// 	i = 0;
// 	while (j < nbr_var)
// 	{
// 		while()
// 		{}
// 	}
// }
