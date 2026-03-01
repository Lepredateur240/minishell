/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:12:56 by algasnie          #+#    #+#             */
/*   Updated: 2025/10/23 12:50:54 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*t;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		t = ft_strdup("");
		return (t);
	}
	if ((ft_strlen(s) - start) < len)
		t = malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
	else
		t = malloc(sizeof(char) * (len + 1));
	if (!t)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		t[i] = s[start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
