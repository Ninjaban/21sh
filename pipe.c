/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 08:49:07 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/20 09:13:04 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <dirent.h>
#include <string.h>

int	ft_pipe(void)
{
	int const	READ_END = 0;
	int const	WRITE_END = 1;
	char	*str = NULL;
	char	*t[4];
	char	*str2 = NULL;
	char	*t2[3];
	pid_t	child;
	int		pdes[2];

	str = "/bin/ls";
	t[0] = "ls";
	t[1] = "-lR";
	t[2] = "/";
	t[3] = NULL;

	str2 = "/bin/cat";
	t2[0] = "cat";
	t2[1] = "-e";
	t2[2] = NULL;

	pipe(pdes);
	if ((child = fork()) == -1)
		return (1);
	if (child == 0)
	{
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		close(pdes[READ_END]);
		execve(str, t, NULL);
		return (1);
	}
	dup2(pdes[READ_END], STDIN_FILENO);
	close(pdes[WRITE_END]);
//	wait(NULL);
	execve(str2, t2, NULL);
	return (0);
}

int main()
{
	pid_t	child;

	printf("Start\n");
	if ((child = fork()) == -1)
		return (1);
	if (child == 0)
		ft_pipe();
	wait(NULL);
	printf("End\n");
	return (0);
}
