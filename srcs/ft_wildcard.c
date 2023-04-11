/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:31:51 by suchua            #+#    #+#             */
/*   Updated: 2023/03/20 20:24:26 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_file_type(char *cmd, int i)
{
	int		j;
	char	c;
	char	*type;

	j = i + 1;
	while (cmd[j] && cmd[j] != 32)
		++j;
	c = cmd[j];
	cmd[j] = 0;
	type = ft_strdup(&cmd[i + 1]);
	cmd[j] = c;
	return (type);
}

char	*redup_cmd(char *cmd)
{
	int			i;
	char		*type;
	t_files		*files;
	t_files_num	files_num;

	i = -1;
	files = NULL;
	while (cmd[++i])
	{
		if (cmd[i] == '*')
		{
			files_num.before = get_files_num(files);
			if (cmd[i + 1] == 32 || !cmd[i + 1])
				type = NULL;
			else
				type = get_file_type(cmd, i);
			get_the_files(&files, type);
			files_num.after = get_files_num(files);
			if (cmd[i] == '*' && files_num.after == files_num.before)
				return (wildcard_error(&cmd[i], &files));
		}
	}
	return (write_files_to_str(cmd, &files));
}

int	check_wild_card(char ***cmd)
{
	int		i;
	int		ret;
	char	**tmp;
	char	*tmp2;

	i = -1;
	tmp = *cmd;
	while (tmp[++i])
	{
		ret = wild_card_exists(tmp[i]);
		if (ret == -1)
			return (-1);
		if (ret == 0)
			continue ;
		tmp2 = redup_cmd(tmp[i]);
		if (!tmp2)
			return (-1);
		free(tmp[i]);
		tmp[i] = ft_strdup(tmp2);
		free(tmp2);
	}
	return (1);
}
