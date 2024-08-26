/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambgus_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:46:38 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/26 11:49:10 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_lenght(t_list *node, t_env *env, t_pars *parsg)
{
	char	*varaib;
	int		i;

	i = 0;
	if (node->type == var)
	{
		varaib = ft_getenv(node->content + 1, env);
		i = count_words(varaib);
	}
	else if (node->type == dquot)
	{
		varaib = expand_dquot(node->content, env, parsg);
		i = count_words(varaib);
		free(varaib);
	}
	else if (node->type == word || node->type == squot)
		i = count_words(node->content);
	return (i);
}

int	space_at_bgn(char *str, t_env *env, t_pars *parsg)
{
	char	*varaib;

	varaib = expand_dquot(str, env, parsg);
	if (varaib && (varaib[0] == ' ' || varaib[0] == '\t'))
		return (1);
	return (0);
}

int	space_at_end(char *str, t_env *env, t_pars *parsg)
{
	char	*varaib;
	int		id_p_nl;

	varaib = expand_dquot(str, env, parsg);
	id_p_nl = ft_strlen(varaib) - 1;
	if (varaib && (varaib[id_p_nl] == ' ' || varaib[id_p_nl] == '\t'))
		return (1);
	return (0);
}
