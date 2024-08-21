/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:45:24 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/21 17:45:07 by lamhal           ###   ########.fr       */
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

int	find_type_limter(t_list *lst)
{
	t_list	*tmp;
	int		type;

	tmp = lst;
	type = limtr;
	while (tmp && tmp->type != space && tmp->type > 4)
	{
		if (tmp->type == dquot || tmp->type == squot)
			type = limtr_qt;
		tmp = tmp->next;
	}
	return (type);
}

void	flag_limitter(t_list *lst)
{
	t_list	*tmp;
	int		type;

	tmp = lst;
	while (tmp && tmp->next)
	{
		if (tmp->type == herdoc)
		{
			tmp && (tmp = tmp->next);
			if (tmp->type == space && tmp->next)
				tmp = tmp->next;
			type = find_type_limter(tmp);
			while (tmp && tmp->type != space && tmp->type > 4)
			{
				tmp->type = type;
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != herdoc) && (tmp = tmp->next);
	}
}

void	add_to_list(t_list **lst, char *token, t_env *env)
{
	t_list	*node;

	if(!token)
	{
		ft_lstclear(lst);
		ft_lstclear_env(&env);
		ft_putstr_fd("mallac failed\n", 2);
		exit(1);
	}
	node = ft_lstnew(token);
	if (!node)
	{
		ft_lstclear(lst);
		ft_lstclear_env(&env);
		ft_putstr_fd("mallac failed\n", 2);
		exit(1);
	}
	node->type = find_type(token);
	ft_lstadd_back(lst, node);
}

void	tokonisation(t_list **lst, char *line, t_env *env)
{
	char	*token;
	int		i;

	i = 0;
	token = NULL;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line && line[i])
	{
		token = get_token(line, &i);
		add_to_list(lst, token, env);
		if (line[i] && (line[i] == ' ' || line [i] == '\t'))
		{
			while (line[i] == ' ' || line [i] == '\t')
				i++;
			if (line[i] != '\0')
			{
				token = ft_strdup(" ");
				add_to_list(lst, token, env);
			}
		}
	}
}

t_cmds	*proccess_line(char *line, t_env *env)
{
	t_list	*lst;
	t_list	*node;
	t_cmds	*cmds;

	lst = NULL;
	node = NULL;
	tokonisation(&lst, line, env);
	printf("**********************************************\n");
	t_list *tmp;
	tmp = lst;
	while (tmp)
	{
		printf("%s %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	printf("**********************************************\n");
	if (check_syntaxe_error(lst))
	{
		ft_lstclear(&lst);
		return (NULL);
	}
	remove_quotes(lst, env);
	flag_limitter(lst);
	flag_ambigus(lst, env);
	expand(lst, env);
	tmp = lst;
	while (tmp)
	{
		printf("%s %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	printf("**********************************************\n");
	ft_lst_join(&lst);//
	tmp = lst;
	while (tmp)
	{
		printf("%s %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	cmds = list_cmds(lst, env);//
	int	i;
	t_cmds	*tmp1;
	t_list	*tmp2;
	tmp1 = cmds;
	while (tmp1)
	{
		i = 0;
		if (!tmp1->args)
			printf("args =\n");
      	while(tmp1 && tmp1->args && tmp1->args[i])
		{
			printf("args[%d] = %s\n", i, tmp1->args[i]);
			i++;
		}
		tmp2 = tmp1->red;
		if (!tmp2)
			printf("red =\n");
		while (tmp2)
		{
			printf("%s-- %d\n", tmp2->content, tmp2->type);
			tmp2 = tmp2->next;
		}
		printf("------------------\n");
		tmp1 = tmp1->next;
	}
	ft_lstclear(&lst);//
	return (cmds);
}
