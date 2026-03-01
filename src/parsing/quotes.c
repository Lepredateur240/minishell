/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:34:28 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/25 15:28:52 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quote_state(char c, int *state)
{
	if (c == '\'' && *state == 0)
		*state = 1;
	else if (c == '\'' && *state == 1)
		*state = 0;
	else if (c == '\"' && *state == 0)
		*state = 2;
	else if (c == '\"' && *state == 2)
		*state = 0;
}

int	get_quote_state(char *str, int index)
{
	int	i;
	int	state;

	if (!str || index < 0)
		return (0);
	i = 0;
	state = 0;
	while (str[i] && i <= index)
	{
		update_quote_state(str[i], &state);
		i++;
	}
	return (state);
}

int	verify_unclosed_quotes(char *prompt)
{
	if (get_quote_state(prompt, ft_strlen(prompt) - 1))
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (1);
	}
	return (0);
}
