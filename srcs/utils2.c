/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 01:55:59 by suchua            #+#    #+#             */
/*   Updated: 2023/04/17 00:22:59 by suchua           ###   ########.fr       */
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

void	ft_free_files_lst(t_files **lst)
{
	t_files	*tmp;

	while ((*lst))
	{
		tmp = (*lst)->next;
		free((*lst)->file);
		free((*lst));
		(*lst) = tmp;
	}
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

void	ft_free_infile_outfile(t_shell *info)
{
	t_redirlst	*tmp;

	tmp = info->infile;
	printf("infile :: \n");
	while (tmp)
	{
		printf("%d\n", tmp->fd);
		tmp = tmp->next;
	}
	
	tmp = info->outfile;
	printf("outfile :: \n");
	while (tmp)
	{
		printf("%d\n", tmp->fd);
		tmp = tmp->next;
	}
	
	while (info->infile)
	{
		tmp = info->infile->next;
		close(info->infile->fd);
		free(info->infile);
		info->infile = tmp;
	}
	while (info->outfile)
	{
		tmp = info->outfile->next;
		close(info->outfile->fd);
		free(info->outfile);
		info->outfile = tmp;
	}
}
