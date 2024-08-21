/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:05:34 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/21 15:33:02 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*txt;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	txt = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!txt)
		(write(2, "allocation failed\n", 19), exit (EXIT_FAILURE));
	while (s1[j])
		txt[i++] = s1[j++];
	j = 0;
	while (s2[j])
		txt[i++] = s2[j++];
	txt[i] = '\0';
	return (txt);
}

char	*ft_strjoin_free(char *str1, char *str2)
{
	char	*str;

	str = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	cc;
	int				i;

	i = 0;
	cc = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == cc)
		return ((char *)(s + i));
	return (NULL);
}
