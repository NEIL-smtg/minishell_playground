/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:34:38 by suchua            #+#    #+#             */
/*   Updated: 2023/09/23 06:05:53 by suchua           ###   ########.fr       */
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
	char	*exec_path;

	i = -1;
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	exec_path = get_exec_path(env);
	path = ft_split(exec_path, ':');
	free(exec_path);
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
