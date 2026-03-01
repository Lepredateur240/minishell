/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:16:41 by masenche          #+#    #+#             */
/*   Updated: 2026/03/01 18:25:18 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exe_child(t_cmd *cmd, t_minishell *minishell, char**envp)
{
	// 1. Appliquer les redirections
	if (cmd->fd_in > 2) // Si c'est un fichier ouvert
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out > 2) // Si c'est un fichier ouvert
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	// 2. Exécuter le programme
	if (execve(cmd->cmd_path, cmd->args, envp) == -1)
	{
		perror("minishell");
		exit(127); 
	}
}

void exec_command(t_cmd *cmd, t_minishell *minishell)
{
	pid_t pid;
	int   status;
	char  **env_tab; // Pour stocker l'environnement converti

	// env_tab = convert_env_to_tab(minishell->env); // Convertir la liste d'environnement en tableau de chaînes
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0) // Processus ENFANT
		exe_child(cmd, minishell, env_tab);
	else // Processus PARENT
	{
		waitpid(pid, &status, 0);
		// On récupère le statut
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		if (cmd->fd_in > 2) close(cmd->fd_in);
		if (cmd->fd_out > 2) close(cmd->fd_out);
		// free_tab(env_tab);
	}
}
