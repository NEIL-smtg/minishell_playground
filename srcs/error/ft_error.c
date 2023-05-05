/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 01:21:52 by suchua            #+#    #+#             */
/*   Updated: 2023/05/06 02:19:02 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if the cmd exists, theres no need to print out any msg,
// since the cmd itself will
// print out for us
void	cmd_not_found(t_cmdlst *node, t_shell *info)
{
	char	*path;
	char	**splitted;

	while (node)
	{
		if (to_split(node->cmd) || info->open_error == -1)
		{
			node = node->next;
			continue ;
		}
		splitted = ft_split(node->cmd, 32);
		path = get_cmd_path(splitted[0]);
		if (!path)
		{
			ft_putstr_fd("minishell : command not found: ", 2);
			ft_putendl_fd(splitted[0], 2);
			ft_free2d(splitted);
			return ;
		}
		ft_free2d(splitted);
		free(path);
		node = node->next;
	}
}
