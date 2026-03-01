/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:12:48 by algasnie          #+#    #+#             */
/*   Updated: 2025/10/23 13:10:27 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*t;

	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) == 0)
	{
		t = ft_strdup("");
		return (t);
	}
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end >= start && ft_strchr(set, s1[end]) != NULL)
		end--;
	t = malloc(sizeof(char) * (end - start + 2));
	if (!t)
		return (NULL);
	ft_strlcpy(t, &s1[start], end - start + 2);
	return (t);
}
