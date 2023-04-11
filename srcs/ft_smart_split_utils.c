/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smart_split_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:24:12 by suchua            #+#    #+#             */
/*   Updated: 2023/03/24 12:30:35 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_quote(char *str)
{
	int	i;
	int	within_s;
	int	within_d;

	i = -1;
	within_s = 0;
	within_d = 0;
	while (str[++i])
	{
		if (str[i] == 39)
			within_d = !within_d;
		if (str[i] == 34)
			within_s = !within_s;
	}
	if (within_d || within_s)
		return (0);
	return (1);
}

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = -1;
	j = 0;
	len = ft_strlen(str);
	new = ft_calloc((len + 1), sizeof(char));
	while (++i < len)
	{
		if (str[i] != 34 && str[i] != 39)
			new[j++] = str[i];
	}
	free(str);
	return (new);
}

char	*filter_quote(char *str)
{
	int	i;

	i = 0;
	if (!ft_strncmp("echo", &str[i], 4))
		return (str);
	if (close_quote(str))
		return (remove_quote(str));
	return (str);
}

// void	ft_fill_empty_string(char *str, char *ori, char *delimiters)
// {
// 	int i, j, k;
// 	int	row;
//     int	delimiter = 0;
//     int	quote = 0;
//     int	parens = 0;

// 	i = -1;
// 	k = -1;
// 	row = 0;
// 	free (str);
// 	while (ori[++i])
// 	{
// 		if (ori[i] == '\'' || ori[i] == '\"')
//             quote = !quote;
//         if (ori[i] == '(')
//             parens++;
//         if (ori[i] == ')')
//             parens--;
//         while (delimiters[++k])
// 		{
// 			// printf("-\\-%c-\\-\n", delimiters[k]);
//             if (ori[i] == delimiters[k] && !quote && !parens)
// 			{
//                 delimiter = 1;
//                 break;
//             }
//         }
// 		if (delimiter)
// 		{
// 			printf("\\%s\\\n", ft_strdup(ft_substr(ori, i, 2)));
// 			str = ft_strdup(ft_substr(ori, i, 2));
// 			delimiter = 0;
// 		}
// 	}
// }

char	**remove_space_quote(char **str, t_shell *info)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i][j] && str[i][j] == 32)
			++j;
		tmp = ft_strdup(&str[i][j]);
		free(str[i]);
		str[i] = filter_quote(tmp);
		str[i] = filter_dollar(str[i], info);
	}
	return (str);
}
