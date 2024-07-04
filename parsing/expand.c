/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:58:19 by lamhal            #+#    #+#             */
/*   Updated: 2024/07/04 15:10:43 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	 remove_quotes(t_list *list)
{
	t_list	*tmp;

	if (!list)
		return ;
	tmp = list;
	while (tmp)
	{
		if(tmp->content[0] == '\'' || tmp->content[0] == '\"')
		{
			free(tmp->content);
			tmp->content = ft_substr(tmp->content, 1, ft_strlen(tmp->content) - 2);
		}
		tmp = tmp->next;
	}
}

char	*expand_var(char *varaible, t_env *env)
{
	char	*tmp;

	tmp = varaible;
	varaible = get_env(varaible + 1, env);
	free(tmp);
	return varaible;
}

// void	expand_dqout(char *str, t_env *env)
// {
// 	char	*variab;
// 	char	*prev;

// 	while (str)
// 	{
// 		variab = ft_strchr(str, '$');
// 		prev = ft_substr(str, 0, str - variab);
		
// 	}
	
// }

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
