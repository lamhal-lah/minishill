/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:45:24 by lamhal            #+#    #+#             */
/*   Updated: 2024/07/04 13:10:49 by lamhal           ###   ########.fr       */
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
	else if (str[0] == '\"')
		return (5);
	else if (str[0] == '\'')
		return (6);
	else if (str[0] == '$')
		return (7);
	else if (str[0] == ' ')
		return (8);
	return (9);
}	

void	handl_quotes(char *line, int *i)
{
	char	c;
	
	c = line[*i];
	*i += 1;
	while (line[*i] && line[*i] != c)
		*i += 1;
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

static char	*get_token(char *line , int *i)
{
	int		len;
	char	c;
	char	*token;
	
	token = NULL;
	len = *i;
	if (line[len] == ' ' || line[len] == '\t')
	{
		while (line[*i] == ' ' || line[*i] == '\t')
			*i += 1;
		if (line[*i] == '\0')
			return (NULL);
		return (ft_strdup(" "));
	}
	if (line[len] == 39 || line[len] == 34)
	{
		c = line[len++];
		while ( line[len] &&line[len] && line[len] != c)
			len++;
		len += 1 - *i;
	}
	else if ((line[len] == '>' && line[len + 1] == '>') ||
			(line[len] == '<' && line[len + 1] == '<'))
		len = 2;
	else if (line[len] == '|' || line[len] == '>' || line[len] == '<')
		len = 1;
	else if(line[len++] == '$')
	{
		while ((line[len] >= 'a' && line[len] <= 'z') ||
			(line[len] >= 'A' && line[len] <= 'Z') || line[len] == '_' ||
			(line[len] >= '0' && line[len] <= '9'))
			len++;
		len -= *i;
	}
	else if (line[len] != ' ' && line[len] != '\t' && line[len] != '$')
	{
		while (line[len] && line [len] != ' ' && line[len] != '\t' && 
			line[len] != '|' && line[len] != '>' && line[len] != '<' && line[len] != '$')
			len++;
		len -= *i;
	}
	token = ft_substr(line, *i, len);
	*i += len;
	return (token);
}

void	proccess_line(char *line, t_list **lst)
{
	int		i;
	char	*token;
	t_list	*node;

	node = NULL;
	token = NULL;
	i = 0;
	while (line[i] == ' ' || line [i] == '\t')
			i++;
	while (line && line[i] && line[i] != '\n')
	{
		token = get_token(line, &i);
		//add_to_list(lst, token);
		if (token && *token)
		{
			node = ft_lstnew(token);
			if (!node)
				exit (EXIT_FAILURE);
			node->type = find_type(token);
			ft_lstadd_back(lst, node);
		}
		remove_quotes(*lst);
	}
}
