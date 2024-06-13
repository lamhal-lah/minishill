/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:45:24 by lamhal            #+#    #+#             */
/*   Updated: 2024/06/13 00:43:03 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_type(char *str)
{
	if (ft_strncmp(str, "|", 2))
		return (0);
	else if (ft_strncmp(str, ">", 2))
		return (1);
	else if (ft_strncmp(str, "<", 2))
		return (2);
	else if (ft_strncmp(str, "<<", 3))
		return (3);
	else if (ft_strncmp(str, "\"", 1))
		return (4);
	else if (ft_strncmp(str, "\'", 1))
		return (5);
	else if (ft_strncmp(str, "$", 1))
		return (6);
	else
		return (7);
}


void	add_to_list(t_list **lst, char *token)
{
	t_list	*node = NULL;
	//printf("%s\n", token);
	node = ft_lstnew(token);
	//printf("%s\n", node->content);
	if (!node)
		exit (EXIT_FAILURE);
	//printf("%s\n", node->content);
	node->type = find_type(token);
	ft_lstadd_back(lst, node);
}

int	check_couts(char *line)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == 34)
			j++;
		else if (line[i] == 39)
			k++;
		i++;
	}
	if (j % 2 == 1 || k % 2 == 1)
		return (0);
	return (1);
}

int	get_token(char *line ,char **token , int i)
{
	int		len;
	char	c;
	
	len = i;
	if (line[len] == 39 || line[len] == 34)
	{
		c = line[len++];
		while (line[len] && line[len] != c)
			len++;
		len = len - i + 1;
		*token = ft_substr(line, i, len);
		i = i + len;
	}
	else if (line[i] != ' ' && line[i] != '\t')
	{
		len = i;
		while (line[len] && line [len] != ' ' && line[len] != '\t')
			len++;
		len = len - i + 1;
		*token = ft_substr(line, i, len);
		i = i + len;
	}
	return (i);
}

void	proccess_line(char *line, t_list **lst)
{
	int		i;

	char	*token = NULL;

	i = 0;
	while (line && line[i] && line[i] != '\n')
	{
		while (line[i] == ' ' || line [i] == '\t')
			i++;
		i = get_token(line, &token, i);
		add_to_list(lst, token);
	}
}

