/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smart_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:06:54 by suchua            #+#    #+#             */
/*   Updated: 2023/04/11 01:33:41 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_row(char *str, char *delimiters)
{
	int	i, k;
	int	row;
	int	delimiter;
	int	quote ;
	int	parens;

	i = -1;
	row = 0;
	delimiter = 0;
	quote = 0;
	parens = 0;
	while (str[++i])
	{
		k = -1;
		if (str[i] == '\'' || str[i] == '\"')
			quote = !quote;
		if (str[i] == '(')
			parens++;
		if (str[i] == ')')
			parens--;
		while (delimiters[++k])
		{
			if (str[i] == delimiters[k] && !quote && !parens)
			{
				delimiter++;
				break ;
			}
		}
	}
	return (delimiter + 1);
}

void	tokenize(char *str, char **new, char *delimiters)
{
	int		i, j, k;
	int		quote;
	int		delimiter;
	int		parens;
	int		token_count;
	char	token[1024];

	i = -1;
	j = 0;
	quote = 0;
	delimiter = 0;
	parens = 0;
	token_count = 0;
	ft_memset(token, 0, 1024);
	while (str[++i])
	{
		k = -1;
		if (str[i] == '\'' || str[i] == '\"')
			quote = !quote;
		if (str[i] == '(')
			parens++;
		if (str[i] == ')')
			parens--;
		while (delimiters[++k])
		{
			if (str[i] == delimiters[k] && !quote && !parens)
			{
				delimiter = 1;
				break;
			}
		}
		if (delimiter)
		{
			if (j > 0)
			{
				new[token_count] = ft_strdup(token);
				ft_memset(token, 0, 1024);
				token_count++;
				j = 0;
			}
			new[token_count] = ft_substr(&str[i], 0, 2);
			token_count++;
			i++;
			delimiter = 0;
		}
		else
		{
			token[j] = str[i];
			j++;
		}
	}
	if (j > 0 && token_count < 100)
	{
		new[token_count] = ft_strdup(token);
		token_count++;
	}
	// printf("-%s-\n", "here");
    new[token_count] = NULL;
}

char	**ft_smart_split(char *str, t_shell *info)
{
	char	**new;
	int		i;

	i = ft_get_row(str, "||&&|");
	new = ft_calloc(i + 1, sizeof(char *));
	tokenize(str, new, "||&&|");
	return (remove_space_quote(new, info));
}

// int main(int ac, char **av, char **env)
// {
// 	t_shell info;
// 	info.ms_env = ft_2d_strdup(env);
// 	char str[100] = "echo \"cat lol.c || cat lol.c\" && (cd \"..\" && hi) | hopeful it works";
// 	char **s = ft_smart_split(str, &info);
// 	int i = -1;
// 	// printf("row %d\n", get_row(str));
// 	while (s[++i])
// 		printf("\\%d - %s\\\n", i, s[i]);
// 	// system("leaks a.out");
// 	exit(EXIT_SUCCESS);
// }