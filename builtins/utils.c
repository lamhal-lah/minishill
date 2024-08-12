/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:41:42 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/11 12:37:16 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*ft_strchr(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return (str + i);
// 		i++;
// 	}
// 	return (NULL);
// }

size_t	count_words_execution(const char *s, char c)
{
	size_t	word;

	word = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			word++;
		while (*s && *s != c)
			s++;
	}
	return (word);
}

char	**free_split_execution(char **split, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(split[i++]);
	free(split);
	return (NULL);
}

static char	**alloc_split(const char *s, char c)
{
	size_t		i;
	size_t		total;
	char		**split;
	size_t		size;

	i = 0;
	if (!s)
		return (NULL);
	size = count_words_execution(s, c);
	split = (char **)malloc(sizeof(char *) * (size + 1));
	if (!split)
		return (NULL);
	while (*s && i < size)
	{
		total = 0;
		while (*s == c)
			s++;
		while (*s && *s != c && s++)
			total++;
		split[i] = (char *)malloc(sizeof(char) * (total + 1));
		if (!split[i])
			return (free_split_execution(split, i));
		i++;
	}
	return (split);
}

char	**ft_split_execution(char *s, char c)
{
	char		**split;
	size_t		i;
	size_t		j;
	size_t		size;

	i = 0;
	size = count_words_execution(s, c);
	split = alloc_split(s, c);
	if (!split)
		return (NULL);
	while (i < size && *s)
	{
		j = 0;
		while (*s == c)
			s++;
		while (*s && *s != c)
			split[i][j++] = *s++;
		split[i][j] = '\0';
		i++;
	}
	split[i] = NULL;
	return (split);
}
