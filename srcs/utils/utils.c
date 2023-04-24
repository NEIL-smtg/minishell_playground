/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:34:38 by suchua            #+#    #+#             */
/*   Updated: 2023/04/24 22:44:16 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

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

void	msg_cmd_not_found(char **cmd)
{
	char	*path;

	path = get_cmd_path(cmd[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: Command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
	}
	else
		free(path);
	ft_free2d(cmd);
}

int	get_files_num(t_files *files)
{
	int		i;
	t_files	*tmp;

	i = 0;
	tmp = files;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	return (i);
}

t_files	*get_last_files(t_files *files)
{
	t_files	*tmp;

	tmp = files;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
