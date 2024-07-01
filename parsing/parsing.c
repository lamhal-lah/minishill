/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:45:24 by lamhal            #+#    #+#             */
/*   Updated: 2024/07/01 16:14:32 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_type(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (0);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (3);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (4);
	else if (ft_strncmp(str, "\"", 1) == 0)
		return (5);
	else if (ft_strncmp(str, "\'", 1) == 0)
		return (6);
	else if (ft_strncmp(str, "$", 1) == 0)
		return (7);
	return (8);
}	


// void	add_to_list(t_list **lst, char *token)
// {
// 	t_list	*node = NULL;
// 	node = ft_lstnew(token);
// 	if (!node)
// 		exit (EXIT_FAILURE);
// 	node->type = find_type(token);
// 	ft_lstadd_back(lst, node);
// }

static void	get_token(char *line ,char **token , int *i)
{
	int		len;
	char	c;
	
	len = *i;
	if (line[len] == 39 || line[len] == 34)
	{
		c = line[len++];
		while (line[len] && line[len] != c)
			len++;
		len += 1 - *i;
	}
	else if ((line[len] == '>' && line[len + 1] == '>') ||
			(line[len] == '<' && line[len + 1] == '<') || (line[len] == '$' && line[len + 1] >= '0' && line[len + 1] <= '9'))
		len = 2;
	else if (line[len] == '|' || line[len] == '>' || line[len] == '<')
		len = 1;
	else if (line[len] != ' ' && line[len] != '\t')
	{
		while (line[len] && line [len] != ' ' && line[len] != '\t' && 
			line[len] != '|' && line[len] != '>' && line[len] != '<')
			len++;
		len -= *i;
	}
	*token = ft_substr(line, *i, len);
	*i += len;
}

void	proccess_line(char *line, t_list **lst)
{
	int		i;
	char	*token;
	t_list	*node;

	node = NULL;
	token = NULL;
	i = 0;
	if (check_couts(line))
		return ;
	while (line && line[i] && line[i] != '\n')
	{
		while (line[i] == ' ' || line [i] == '\t')
			i++;
		get_token(line, &token, &i);
		//add_to_list(lst, token);
		if (token && *token)
		{
			node = ft_lstnew(token);
			if (!node)
				exit (EXIT_FAILURE);
			node->type = find_type(token);
			ft_lstadd_back(lst, node);
		}
	}
}
