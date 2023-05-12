/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:57:17 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/05/12 11:30:36 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

void	sub_process(int *fd, char **argv, char **envp);
void	main_process(int *fd, char **argv, char **envp);
void	error(void);
void	free_split(char **str);
char	*get_cmd_path(char *cmd, char **envp);
void	run_cmd(char *cmd, char **envp);

#endif