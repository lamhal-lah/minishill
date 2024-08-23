/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:58:19 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/23 15:35:56 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_var_dqout(char *varaible, t_env *env)
{
	char	*tmp;

	if (varaible && !varaible[1])
		return (varaible);
	tmp = varaible;
	varaible = ft_getenv(varaible + 1, env);
	if (!varaible)
	{
		free(tmp);
		return (NULL);
	}
	varaible = ft_strdup(varaible);
	free(tmp);
	return (varaible);
}

char	*get_str(char *str, int *indx, t_env *env, t_list *lst)
{
	int		i;
	char	*str1;
	int		k;

	i = *indx;
	k = *indx;
	if (str[i] == '$')
	{
		i++;
		while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'
				|| (str[i] >= '0' && str[i] <= '9')))
			i++;
	}
	else
		while (str[i] && str[i] != '$')
			i++;
	str1 = ft_substr(str, k, i - k);
	if (!str)
		(ft_lstclear(&lst), ft_lstclear_env(&env),
			ft_putstr_fd("failled malloc", 2), exit(1));
	if (str1 && str1[0] == '$')
		str1 = expand_var_dqout(str1, env);
	*indx = i;
	return (str1);
}

char	*expand_dquot(char *str, t_env *env, t_list *lst)
{
	char	*str1;
	char	*str2;
	int		i;

	i = 0;
	str1 = get_str(str, &i, env, lst);
	while (str[i])
	{
		str2 = get_str(str, &i, env, lst);
		if (str1 || str2)
		{
			str1 = ft_strjoin_free(str1, str2);
			if (!str1)
				(ft_lstclear(&lst), ft_lstclear_env(&env), exit(1),
					ft_putstr_fd("failed malloc", 2), exit(1));
		}
	}
	return (str1);
}

void	expand(t_list *lst, t_env *env)
{
	t_list	*tmp;
	char	*str_tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type == var)
			expand_var(tmp->content, env, &tmp, &lst);
		if (tmp->type == dquot)
		{
			str_tmp = tmp->content;
			tmp->content = expand_dquot(tmp->content, env, lst);
			free(str_tmp);
			str_tmp = NULL;
		}
		tmp && (tmp = tmp->next);
	}
	remove_empty_node(&lst);
}
