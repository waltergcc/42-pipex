/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:58:28 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/05/13 12:25:09 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	custom_error(char *header, char *msg)
{
	ft_putstr_fd(header, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**envp_paths;
	char	*cmd_path;
	int		i;
	char	*only_path;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	envp_paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (envp_paths[++i])
	{
		only_path = ft_strjoin(envp_paths[i], "/");
		cmd_path = ft_strjoin(only_path, cmd);
		free (only_path);
		if (access(cmd_path, F_OK) == 0)
		{
			free_split(envp_paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_split(envp_paths);
	custom_error(cmd, "command not found");
	return (NULL);
}

void	run_cmd(char *cmd, char **envp)
{
	char	**cmd_and_flags;
	char	*path;

	cmd_and_flags = ft_split(cmd, ' ');
	path = get_cmd_path(cmd_and_flags[0], envp);
	if (!path)
	{
		free_split(cmd_and_flags);
		free (path);
		exit(127);
	}
	if (execve(path, cmd_and_flags, envp) == -1)
	{
		free_split(cmd_and_flags);
		free (path);
		exit_error();
	}
}
