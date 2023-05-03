/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:29:44 by suchua            #+#    #+#             */
/*   Updated: 2023/05/03 16:25:20 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_result(t_shell *info, char *needle)
{
	int		i;
	int		len;

	if (!ft_strncmp("?", needle, 2))
		return (ft_itoa(info->ms_status / 256));
	i = -1;
	while (info->ms_env[++i])
	{
		len = 0;
		while (info->ms_env[i][len] != '=')
			++len;
		if (len > (int) ft_strlen(needle))
			continue ;
		if (!ft_strncmp(info->ms_env[i], needle, ft_strlen(needle)))
			return (ft_strdup(info->ms_env[i] + ft_strlen(needle) + 1));
	}
	return (NULL);
}

//i = input index, j = new index
static void	overwrite_with_env_value(char **new, t_shell *info, int *i, int *j)
{
	char	*res;
	int		k;
	char	*needle;
	char	*tmp;

	k = *i + 1;
	while (info->input_line[k] && ft_isalpha(info->input_line[k]))
		++k;
	needle = ft_substr(info->input_line, *i + 1, k - *i - 1);
	res = search_result(info, needle);
	if (!res)
		res = ft_substr(info->input_line, *i, k);
	tmp = ft_strjoin(*new, res);
	tmp = gnl_strjoin(tmp, &info->input_line[k]);
	*j += ft_strlen(res);
	*i += ft_strlen(needle);
	ft_memset(&tmp[*j], 0, ft_strlen(&tmp[*j]));
	free(res);
	free(*new);
	free(needle);
	*new = tmp;
}

static void	generate_new_input(t_shell *info)
{
	int		i;
	int		j;
	char	*new;
	int		quote;

	new = ft_calloc(ft_strlen(info->input_line), sizeof(char));
	i = -1;
	j = 0;
	quote = -1;
	while (info->input_line[++i])
	{
		if (quote == -1 && (info->input_line[i] == 34
				|| info->input_line[i] == 39))
			quote = info->input_line[i];
		else if (quote == info->input_line[i])
			quote = -1;
		else if ((quote == -1 || quote == 34) && info->input_line[i] == '$')
			overwrite_with_env_value(&new, info, &i, &j);
		else
			new[j++] = info->input_line[i];
	}
	free(info->input_line);
	info->input_line = new;
}

void	no_quote_parsing(t_shell *info)
{
	int		i;
	int		j;
	char	*new;

	if (!ft_strchr(info->input_line, '$'))
		return ;
	i = -1;
	j = 0;
	new = ft_calloc(ft_strlen(info->input_line), sizeof(char));
	while (info->input_line[++i])
	{
		if (info->input_line[i] == '$')
			overwrite_with_env_value(&new, info, &i, &j);
		else
			new[j++] = info->input_line[i];
	}
	free(info->input_line);
	info->input_line = new;
}

void	ft_parse_input(t_shell *info)
{
	if (ft_strchr(info->input_line, 34) || ft_strchr(info->input_line, 39))
	{
		generate_new_input(info);
		return ;
	}
	else
		no_quote_parsing(info);
}
