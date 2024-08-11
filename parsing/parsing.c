/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:45:24 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/11 10:29:48 by lamhal           ###   ########.fr       */
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

void	flag_limitter(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
	{
		if (tmp->type == herdoc)
		{
			tmp && (tmp = tmp->next);
			if (tmp->type == space && tmp->next)
				tmp = tmp->next;		
			while(tmp && tmp->type != space && tmp->type > 4)
			{
				if (tmp->type == dquot)
					tmp->type = limtr_qt;
				else if (tmp->type == var)
					tmp->type = limtr;
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != herdoc) && (tmp = tmp->next);
	}
}

int	check_ambigus(t_list *lst, t_env *env)
{
	t_list	*tmp;
	char	*varaib;
	
	tmp = lst;
	while(tmp && tmp->type != space  && tmp->type > 4)
	{
		if (tmp->type == var)
		{
			varaib = ft_getenv(tmp->content + 1, env);
			if (count_words(varaib) != 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	flag_ambigus(t_list *lst, t_env *env)
{
	t_list	*tmp;
	int		ambg;
	
	tmp = lst;
	while(tmp && tmp->next)
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
				if (ambg && tmp->type == var)
					tmp->type = ambigus;
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != red_out) && tmp->type != red_in && tmp->type != append && (tmp = tmp->next);
	}
}

void	add_to_list(t_list **lst, char *token)
{
	t_list	*node = NULL;
	node = ft_lstnew(token);
	if (!node)
		exit (EXIT_FAILURE);
	node->type = find_type(token);
	ft_lstadd_back(lst, node);
}

static void	*get_token(char *line, int *i)
{
	int		len;
	char	c;
	char	*token;
	
	len = *i;
	if (line[len] == 39 || line[len] == 34)
	{
		c = line[len++];
		while (line[len] && line[len] != c)
			len++;
		len += 1 - *i;
	}
	else if (line[len] == '$' && line[len + 1] == '$')
	{
		while (line[len] == '$')
			len++;
		len -= *i;
		(len % 2 == 1) && len--;
	}
	else if ((line[len] == '>' && line[len + 1] == '>') ||
			(line[len] == '<' && line[len + 1] == '<') || (line[len] == '$' && line[len + 1] >= '0' && line[len + 1] <= '9'))
		len = 2;
	else if (line[len] == '|' || line[len] == '>' || line[len] == '<')
		len = 1;
	else if(line[len] == '$')
	{
		len++;
		while ((line[len] >= 'a' && line[len] <= 'z') ||
			(line[len] >= 'A' && line[len] <= 'Z') || line[len] == '_' ||
			(line[len] >= '0' && line[len] <= '9'))
			len++;
		len -= *i;
	}
	else if (line[len] != ' ' && line[len] != '\t')
	{
		while (line[len] && line [len] != ' ' && line[len] != '\t' && 
			line[len] != '|' && line[len] != '>' && line[len] != '<' &&
			line[len] != '$' && line[len] != '\"' && line[len] != '\'')
			len++;
		len -= *i;
	}
	token = ft_substr(line, *i, len);
	if (!token)
		return (NULL);
	*i += len;
	//printf("token : %s\n", token);
	return (token);
}

t_cmds	*proccess_line(char *line, t_list **lst, t_env *env)
{
	t_list	*tmp;
	int		i;
	char	*token;
	t_list	*node;
	t_cmds	*cmds;

	node = NULL;
	token = NULL;
	i = 0;
	while (line[i] == ' ' && line[i] == '\t')
		i++;
	while (line && line[i])
	{
		token = get_token(line, &i);
		if (!token)
			(ft_lstclear(lst), ft_putstr_fd("mallac failed\n", 2), exit(1));
		add_to_list(lst, token);
		if (line[i] == ' ' || line [i] == '\t'){
			while (line[i] == ' ' || line [i] == '\t')
				i++;
			if (line[i] != '\0')
			{
				token = ft_strdup(" ");
				if (!token)
					(ft_lstclear(lst), ft_putstr_fd("mallac failed\n", 2), exit(1));
				add_to_list(lst, token);
			}
		}
	}
	if (check_syntaxe_error(*lst))
		return NULL;
	remove_quotes(*lst);
	flag_limitter(*lst);
	flag_ambigus(*lst, env);
	expand(*lst, env);
	tmp = *lst;
	while (tmp)
	{
		printf("%s %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	printf("**********************************************\n");
	ft_lst_join(lst);
	tmp = *lst;
	while (tmp)
	{
		printf("%s %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	cmds = list_cmds(*lst);
	t_cmds	*tmp1;
	tmp1 = cmds;
	// while (tmp1)
	// {
	// 	printf("node %s\n",tmp1->args[0]);
	// 	tmp1 = tmp1->next;
	// }
	while (tmp1)
	{
		i = 0;
      	while(tmp1 && tmp1->args && tmp1->args[i])
		{
			printf("args[%d] = %s\n", i, tmp1->args[i]);
			i++;
		}
		while (tmp1->red)
		{
			printf("%s-- %d\n", tmp1->red->content, tmp1->red->type);
			tmp1->red = tmp1->red->next;
		}
		printf("------------------\n");
		tmp1 = tmp1->next;
	}
	
	return (cmds);
}
