/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:55:26 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/24 10:17:45 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_env_data(t_env *new_node, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new_node->key = ft_substr(str, 0, i);
	new_node->exported = 1;
	if (!new_node->key)
		return (0);
	if (str[i])
	{
		new_node->value = ft_strdup(str + i + 1);
		if (!new_node->value)
		{
			free(new_node->key);
			return (0);
		}
	}
	else
		new_node->value = NULL;
	return (1);
}

static t_env	*new_env_node(char *str)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (!fill_env_data(new_node, str))
	{
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

t_list	*init_env(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	t_env	*content;
	int		i;

	env_list = NULL;
	if (!envp || !envp[0])
		return (NULL);
	i = 0;
	while (envp[i])
	{
		content = new_env_node(envp[i]);
		new_node = ft_lstnew(content);
		if (!content || !new_node)
		{
			free_env(content);
			ft_lstclear(&env_list, free_env);
			return (NULL);
		}
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}
