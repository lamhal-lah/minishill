/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:45:24 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/15 16:00:15 by lamhal           ###   ########.fr       */
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
	t_list	*tmp1;
	int		type;

	type = limtr;
	tmp = lst;
	while (tmp && tmp->next)
	{
		if (tmp->type == herdoc)
		{
			tmp && (tmp = tmp->next);
			if (tmp->type == space && tmp->next)
				tmp = tmp->next;
			tmp1 = tmp;		
			while(tmp1 && tmp1->type != space && tmp1->type > 4)
			{
				if (tmp1->type == dquot || tmp1->type == squot)
					type = limtr_qt;
				tmp1 = tmp1->next;
			}
			while(tmp && tmp->type != space && tmp->type > 4)
			{
				tmp->type = type;
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != herdoc) && (tmp = tmp->next);
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
	while (line[i] == ' ' || line[i] == '\t')
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
	t_list	*tmp2;
	tmp1 = cmds;
	while (tmp1)
	{
		i = 0;
      	while(tmp1 && tmp1->args && tmp1->args[i])
		{
			printf("args[%d] = %s\n", i, tmp1->args[i]);
			i++;
		}
		tmp2 = tmp1->red;
		while (tmp2)
		{
			printf("%s-- %d\n", tmp2->content, tmp2->type);
			tmp2 = tmp2->next;
		}
		printf("------------------\n");
		tmp1 = tmp1->next;
	}
	
	return (cmds);
}
