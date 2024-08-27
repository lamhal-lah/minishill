/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:58:19 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/27 23:22:29 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_var_dqout(char *varaible, t_env *env, t_pars *pars)
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
	if (!varaible)
		ft_free_exit(pars, "failled malloc\n");
	free(tmp);
	return (varaible);
}

int	str_len(char *str, int *indx)
{
	int	i;
	int	len;

	len = 0;
	i = *indx;
	if (str[i] == '$')
	{
		i++;
		if (str[i] == '?' || (str[i] >= '0' && str[i] <= '9' ))
			i++;
		else
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
					|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'
					|| (str[i] >= '0' && str[i] <= '9')))
				i++;
	}
	else
		while (str[i] && str[i] != '$')
			i++;
	len = i - *indx;
	*indx = i;
	return (len);
}

char	*get_str(char *str, int *indx, t_env *env, t_pars *parsg)
{
	int		i;
	char	*str1;
	int		k;

	i = *indx;
	k = str_len(str, &i);
	str1 = ft_substr(str, *indx, k);
	if (str1 && ft_strncmp(str1, "$?", 3) == 0)
	{
		free(str1);
		str1 = ft_itoa(parsg->status);
	}
	if (!str)
		ft_free_exit(parsg, "failled malloc\n");
	if (str1 && str1[0] == '$')
		str1 = expand_var_dqout(str1, env, parsg);
	*indx = i;
	return (str1);
}

char	*expand_dquot(char *str, t_env *env, t_pars *parsg)
{
	char	*str1;
	char	*str2;
	int		i;

	i = 0;
	str1 = get_str(str, &i, env, parsg);
	while (str[i])
	{
		str2 = get_str(str, &i, env, parsg);
		if (str1 || str2)
		{
			str1 = ft_strjoin_free(str1, str2);
			if (!str1)
				ft_free_exit(parsg, "failed malloc\n");
		}
	}
	return (str1);
}

void	expand(t_list *lst, t_env *env, t_pars *parsg)
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
			tmp->content = expand_dquot(tmp->content, env, parsg);
			free(str_tmp);
			str_tmp = NULL;
		}
		tmp && (tmp = tmp->next);
	}
	remove_empty_node(&lst);
}
