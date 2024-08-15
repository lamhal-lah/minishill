/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambgus.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:20:38 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/15 12:37:37 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_lenght(t_list *node, t_env *env)
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
		varaib = expand_dquot(node->content, env);
		i = count_words(varaib);
		free(varaib);
	}
	else if (node->type == word || node->type == squot)
		i = count_words(node->content);
	return (i);
}

int	space_at_bgn(char *str, t_env *env)
{
	char	*varaib;

	varaib = expand_dquot(str, env);
	if (varaib &&  (varaib[0] == ' ' || varaib[0] == '\t'))
		return (1);
	return (0);
}

int	space_at_end(char *str, t_env *env)
{
	char	*varaib;
	int 	id_p_nl;

	varaib = expand_dquot(str, env);
	id_p_nl = ft_strlen(varaib) - 1; 
	if (varaib &&  (varaib[id_p_nl] == ' ' || varaib[id_p_nl] == '\t'))
		return (1);
	return (0);
}

int	check_ambigus_one(t_list *lst, t_env *env)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp->type == var)
	{
		while (tmp && tmp->type == var)
		{
			if (count_lenght(tmp, env) == 0)
				tmp = tmp->next;
			else 
				break ;
		}
		if (!tmp || (tmp && (tmp->type <= 4 || tmp->type == space)))
			return (1);
	}
	tmp = lst;
	while(tmp && tmp->type != space  && tmp->type > 4)
	{
		if (tmp->type == var && count_lenght(tmp, env) > 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_ambigus_var(t_list *lst, t_env *env)
{
	t_list	*tmp;
	
	tmp = lst;
	while(tmp && tmp->type != space  && tmp->type > 4)
	{
		if (tmp->type == var && count_lenght(tmp, env) == 1 &&
			space_at_end(tmp->content, env))
		{
			tmp = tmp->next;
			while (tmp && tmp->type != space  && tmp->type > 4)
			{
				if (tmp && count_lenght(tmp, env))
					return (1);
				tmp && (tmp = tmp->next);
			}
		}
		tmp && (tmp->type != space  && tmp->type > 4) && (tmp = tmp->next);
	}
	return (0);
}

int	check_ambigus_word(t_list *lst,t_env *env)
{
	t_list	*tmp;

	tmp = lst;
	while(tmp && tmp->type != space  && tmp->type > 4)
	{
		if (count_lenght(tmp, env) == 1)
		{
			tmp = tmp->next;
			while (tmp && tmp->type != space  && tmp->type > 4)
			{
				if (tmp->type == var)
				{
					if (count_lenght(tmp, env) == 1 && space_at_bgn(tmp->content, env))
						return (1);
				}
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != space  && tmp->type > 4) && (tmp = tmp->next);
	}
	return (0);
}

int	check_ambigus(t_list *lst, t_env *env)
{	
	if (check_ambigus_one(lst, env))
		return (1);
	if (check_ambigus_var(lst, env))
		return (1);
	if (check_ambigus_word(lst, env))
		return (1);
	return (0);
}

void	flag_ambigus(t_list *lst, t_env *env)
{
	t_list	*tmp;
	int		ambg;
	
	tmp = lst;
	while(tmp)
	{
		ambg = 0;
		if (tmp->type == red_out || tmp->type == red_in || tmp->type == append)
		{
			tmp = tmp->next;
			if (tmp->type == space)
				tmp = tmp->next;
			ambg = check_ambigus(tmp, env);
			while(tmp && tmp->type != space  && tmp->type > 4)
			{
				if (ambg)
					tmp->type = ambigus;
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != red_out) && tmp->type != red_in && tmp->type != append && (tmp = tmp->next);
	}
}


// int	check_ambigus(t_list *lst, t_env *env)
// {
// 	t_list	*tmp;
// 	char	*varaib;
	
// 	tmp = lst;
// 	while(tmp && tmp->type != space  && tmp->type > 4)
// 	{
// 		if (tmp->type == var)
// 		{
// 			varaib = ft_getenv(tmp->content + 1, env);
// 			if (count_words(varaib) != 1)
// 				return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// void	flag_ambigus(t_list *lst, t_env *env)
// {
// 	t_list	*tmp;
// 	int		ambg;
	
// 	tmp = lst;
// 	while(tmp && tmp->next)
// 	{
// 		ambg = 0; 
// 		if (tmp->type == red_out || tmp->type == red_in || tmp->type == append)
// 		{
// 			tmp = tmp->next;
// 			if (tmp->type == space)
// 				tmp = tmp->next;
// 			ambg = check_ambigus(tmp, env);
// 			while(tmp && tmp->type != space  && tmp->type > 4)
// 			{
// 				if (ambg && tmp->type == var)
// 					tmp->type = ambigus;
// 				tmp = tmp->next;
// 			}
// 		}
// 		tmp && (tmp->type != red_out) && tmp->type != red_in && tmp->type != append && (tmp = tmp->next);
// 	}
// }