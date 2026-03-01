/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_unquoted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:32:50 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/26 09:33:31 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_word(char const *s, char c)
{
	size_t	word_count;
	size_t	i;
	int		state;
	int		in_word;

	state = 0;
	word_count = 0;
	in_word = 0;
	i = 0;
	while (s[i])
	{
		update_quote_state(s[i], &state);
		if (s[i] == c && state == 0)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			word_count++;
		}
		i++;
	}
	return (word_count);
}

static size_t	ft_len_word(char const *s, char c)
{
	size_t	len;
	int		state;

	len = 0;
	state = 0;
	while (s[len])
	{
		update_quote_state(s[len], &state);
		if (s[len] == c && state == 0)
			break ;
		len++;
	}
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

char	**ft_split_unquoted(char const *s, char c)
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
