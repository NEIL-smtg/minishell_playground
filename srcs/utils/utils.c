/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:34:38 by suchua            #+#    #+#             */
/*   Updated: 2023/05/15 17:27:56 by suchua           ###   ########.fr       */
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

static char	*get_exec_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp("PATH", env[i], 4))
			return (ft_strdup(env[i] + 5));
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **env)
{
	int		i;
	char	*tmp;
	char	**path;

	i = -1;
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	path = ft_split(get_exec_path(env), ':');
	if (!path)
		return (ft_strdup(cmd));
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
