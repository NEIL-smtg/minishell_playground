/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:34:38 by suchua            #+#    #+#             */
/*   Updated: 2023/05/11 14:29:56 by mmuhamad         ###   ########.fr       */
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
