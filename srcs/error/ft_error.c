/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 01:21:52 by suchua            #+#    #+#             */
/*   Updated: 2023/09/23 06:00:27 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	wildcard error when there not matches
void	wildcard_error(char *target, t_shell *info)
{
	info->wildcard_error = -1;
	info->ms_status = 256;
	ft_putstr_fd("minishell : no matches found: ", 2);
	if (target)
	{
		ft_putendl_fd(target, 2);
		free(target);
	}
	else
		ft_putendl_fd("*", 2);
}

//	ignore cmd that already prompt error by itself
static int	ignore(t_shell *info, char *cmd)
{
	if (info->open_error == -1 || info->wildcard_error == -1)
		return (1);
	return (to_split(cmd));
}

// if the cmd exists, theres no need to print out any msg,
// since the cmd itself will
// print out for us
void	cmd_not_found(t_cmdlst *node, t_shell *info)
{
	char	*path;
	char	**splitted;

	while (node)
	{
		if (ignore(info, node->cmd))
		{
			node = node->next;
			continue ;
		}
		splitted = ft_split(node->cmd, 32);
		path = get_cmd_path(splitted[0], info->ms_env);
		if ((path && !ft_strncmp(path, splitted[0], ft_strlen(path))) || !path)
		{
			ft_putstr_fd("minishell : command not found: ", 2);
			ft_putendl_fd(splitted[0], 2);
			free(path);
			ft_free2d(splitted);
			return ;
		}
		ft_free2d(splitted);
		free(path);
		node = node->next;
	}
}
