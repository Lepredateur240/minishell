/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:32:50 by algasnie          #+#    #+#             */
/*   Updated: 2025/10/23 11:43:44 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(char const *s, char c)
{
	size_t	word_count;
	size_t	i;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word_count++;
		i++;
	}
	return (word_count);
}

static size_t	ft_len_word(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	ft_freeall(char **tab, size_t index)
{
	while (index > 0)
	{
		index--;
		free(tab[index]);
	}
	free(tab);
}

static int	ft_putwords(char **tab, char const *s, char c, size_t nbr_words)
{
	size_t	index;
	size_t	j;
	size_t	len;

	index = 0;
	j = 0;
	while (s[j] && index < nbr_words)
	{
		if (s[j] != c && (j == 0 || s[j - 1] == c))
		{
			len = ft_len_word(&s[j], c);
			tab[index] = malloc(sizeof(char) * (len + 1));
			if (!tab[index])
			{
				ft_freeall(tab, index);
				return (1);
			}
			ft_strlcpy(tab[index], &s[j], len + 1);
			index++;
			j += len;
		}
		else
			j++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	nbr_words;

	if (s == NULL)
		return (NULL);
	nbr_words = ft_count_word(s, c);
	tab = malloc(sizeof(char *) * (nbr_words + 1));
	if (!tab)
		return (NULL);
	tab[nbr_words] = NULL;
	if (ft_putwords(tab, s, c, nbr_words) == 1)
		return (NULL);
	return (tab);
}
