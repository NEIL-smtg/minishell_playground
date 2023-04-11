/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:41:12 by suchua            #+#    #+#             */
/*   Updated: 2023/04/12 01:42:20 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char *cmd)
{
	int		i;
	char	*tmp;
	char	**path;

	i = -1;
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	path = ft_split(getenv("PATH"), ':');
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = gnl_strjoin(tmp, cmd);
		if (!access(tmp, F_OK))
		{
			ft_free2d(path);
			return (tmp);
		}
		free(tmp);
	}
	ft_free2d(path);
	return (NULL);
}

void	init_pipe_fd(t_shell *info)
{
	int	i;

	if (info->input_size < 2)
		return ;
	info->fd = ft_calloc((info->input_size - 1), sizeof(int *));
	i = -1;
	while (++i < info->input_size - 1)
	{
		info->fd[i] = ft_calloc(2, sizeof(int));
		if (pipe(info->fd[i]) == -1)
			ft_putendl_fd("Error piping !\n", 2);
	}
}

void	exit_now(char **s, char **cmd, int end, t_shell *info)
{
	if ((!ft_strncmp("exit", s[0], 5) && get_2d_arr_size(cmd) == 1)
		|| (!ft_strncmp("exit", cmd[end], 5)))
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &info->term.original_setting);
		exit(EXIT_SUCCESS);
	}
}

int	exec_now(t_shell *info, char **cmd)
{
	char	**s;
	int		end;
	int		flag;

	s = ft_split(cmd[0], 32);
	end = get_2d_arr_size(cmd) - 1;
	flag = 1;
	exit_now(s, cmd, end, info);
	if ((!ft_strncmp("export", s[0], 7) && get_2d_arr_size(cmd) == 1)
		|| (!ft_strncmp("export", cmd[end], 7)))
		ft_export(info, s);
	else if ((!ft_strncmp("unset", s[0], 6) && get_2d_arr_size(cmd) == 1)
		|| (!ft_strncmp("unset", cmd[end], 6)))
		ft_unset(info, s);
	else if ((!ft_strncmp("cd", s[0], 3) && get_2d_arr_size(cmd) == 1)
		|| (!ft_strncmp("cd", cmd[end], 3)))
		ft_cd(info, s);
	else
		flag = 0;
	ft_free2d(s);
	return (flag);
}
