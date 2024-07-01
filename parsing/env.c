/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:53:54 by lamhal            #+#    #+#             */
/*   Updated: 2024/07/01 18:17:42 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env    *ft_env(char **env)
{
    int i;
    t_env *head;
    t_env *tmp;

    i = 0;
    head = NULL;
    while (env[i])
    {
        tmp = ft_lstnew_env(env[i]);
        if (tmp == NULL)
        {
            ft_lstclear_env(&head);
            return (NULL);
        }
        if (head == NULL)
            head = tmp;
        else
            ft_lstadd_back_env(&head, ft_lstnew_env(env[i]));
        i++;
    }
    return (head);
}
