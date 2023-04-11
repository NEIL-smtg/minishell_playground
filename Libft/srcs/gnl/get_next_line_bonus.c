/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:38:12 by suchua            #+#    #+#             */
/*   Updated: 2023/04/01 05:31:58 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*gnl_strjoin(char *line, char *partial)
{
	int		size;
	char	*new;
	int		i;
	int		j;

	if (!line)
		size = (int)(ft_strlen(partial) + 1);
	else
		size = (int)(ft_strlen(line) + ft_strlen(partial) + 1);
	new = (char *) malloc (size * sizeof(char));
	i = 0;
	if (line)
	{
		i = -1;
		while (line[++i])
			new[i] = line[i];
		free(line);
	}
	j = 0;
	while (partial[j])
		new[i++] = partial[j++];
	new[i] = 0;
	return (new);
}

char	*get_line(char *line)
{
	char	*new;
	int		i;

	if (!line)
		return (NULL);
	new = (char *) malloc ((ft_strlen_n(line) + 2) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < ft_strlen_n(line) + 1)
	{
		new[i] = line[i];
		i++;
	}
	new[i] = 0;
	if (*new == 0)
	{
		free(new);
		new = NULL;
	}
	return (new);
}

char	*ft_jump(char *line)
{
	int		size;
	int		i;
	int		j;
	char	*new;

	if (!line)
		return (NULL);
	size = (int)(ft_strlen(line)) - ft_strlen_n(line) + 1;
	new = (char *) malloc (size * sizeof(char));
	if (!new)
		return (NULL);
	i = ft_strlen_n(line) + 1;
	j = 0;
	while (i < (int) ft_strlen(line))
		new[j++] = line[i++];
	new[j] = 0;
	free(line);
	if (*new == 0)
	{
		free(new);
		new = NULL;
	}
	return (new);
}

char	*get_next_line(int fd)
{
	char		*partial;
	static char	*line[FILE_D_SIZE];
	int			read_res;
	char		*single;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	partial = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!partial)
		return (NULL);
	while (1)
	{
		ft_clean(partial);
		read_res = read(fd, partial, BUFFER_SIZE);
		if (read_res == -1)
			return (NULL);
		line[fd] = gnl_strjoin(line[fd], partial);
		if (ft_contain_n(line[fd]) || read_res == 0)
			break ;
	}
	free(partial);
	single = get_line(line[fd]);
	line[fd] = ft_jump(line[fd]);
	return (single);
}
