/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 08:57:59 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/05/12 13:52:40 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	sub_process(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in == -1)
		error();
	dup2(fd[1], STDOUT_FILENO); // the write end of the pipe '4' is duplicated to stdout '1'
	dup2(fd_in, STDIN_FILENO); // fd_in '5' is duplicated to stdin '0'
	close(fd[0]); // close the read end of the pipe '3'
	run_cmd(argv[2], envp);
}

void	main_process(int *fd, char **argv, char **envp)
{
	int	output_file;

	output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_file == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(output_file, STDOUT_FILENO);
	close(fd[1]);
	run_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			sub_process(fd, argv, envp);
		waitpid(pid, NULL, 0);
		main_process(fd, argv, envp);
	}
	else
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		ft_putstr_fd("Correct Input: ", 1);
		ft_putstr_fd("./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		exit(1);
	}
}
