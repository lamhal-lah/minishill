/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:21:07 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/07 21:10:07 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	count_words(char *str)
{
	int	count;

	count = 0;
	while(str && *str)
	{
		while (is_space(*str))
			str++;
		if (*str)
			count++;
		while (!is_space(*str) && *str)
			str++;
	}
	return (count);
}

void	ft_free(char **str, int n)
{
	while (n--)
		free(str[n]);
	free(str);
}

static char	*ft_word(char *str, int *l)
{
	int		i;
	char	*word;

	i = 0;
	while (!is_space(str[i]) && str[i])
		i++;
	*l = i;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (!is_space(str[i]) && str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	char	**strs;
	int		i;
	int		l;
	int		cnt;

	i = 0;
	if (!str)
		return (NULL);
	cnt = count_words(str);
	strs = (char **)malloc((cnt + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (i < cnt)
	{
		while (is_space(*str))
			str++;
		strs[i] = ft_word(str, &l);
		if (strs[i] == NULL)
			return (ft_free(strs, i), NULL);
		i++;
		str += l;
	} 
	strs[i] = NULL;
	return (strs);
}