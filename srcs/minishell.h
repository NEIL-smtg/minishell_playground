/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:22:17 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 18:37:56 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/include/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <errno.h>
# include <signal.h>
# include <string.h>

# define R1 1
# define R2 2
# define L1 3
# define L2 4
# define FREE_PIPE 1
# define PRINT 1

# define DOUBLE_PIPE 1
# define DOUBLE_N    2
# define PIPE        3
# define NORMAL      4


//store the original setting of default terminal
//reset terminal back to default setting before exiting the program
//not sure if it matters
typedef	struct s_term_setting
{
	struct termios	original_setting;
}	t_term;

//to store fd of redirections
typedef struct s_redirlst
{
	int					fd;
	char				*filename;
	struct	s_redirlst	*next;
}	t_redirlst;

//to store the files in wildcard
typedef struct s_files
{
	char			*file;
	struct s_files	*next;
}	t_files;

//to check if number of files before and after wildcard is the same
//if its the same, meaning no file is found is that directory, hence perror
typedef struct s_file_num
{
	int	before;
	int	after;
}	t_files_num;

//retation = relation of prev cmd and nxt cmd
//open_brac = indicates bracket starts
//close_brac = indicates bracket closed
//no brac = cmd isnt within bracket
typedef struct s_cmdlst
{
	char				*cmd;
	int					open_brac;
	int					closed_brac;
	int					within_brac;
	int					relation;
	struct s_cmdlst		*prev;
	struct s_cmdlst		*next;
}	t_cmdlst;

//main data struct
typedef struct s_shell
{
	char		*ms_prompt;
	char		**ms_env;
	char		*input_line;
	int			ms_status;
	int			fd[2];
	int			prevfd;
	t_term		term;
	t_cmdlst	*cmdlst;
	t_redirlst	*infile;
	t_redirlst	*outfile;
}	t_shell;

//check dangling
int		ft_dangling(char *str, int print);
int		dangling_dquote(char *str);
int		dangling_squote(char *str);
int		dangling_bracket(char *str);
int		dangling_pipe(char *str);

//signal
void	init_signal(void);

//parse input
void	ft_parse_input(t_shell *info);
void	ft_parse_wildcard(t_shell *info);

//redir
int		set_redir(t_shell *info, t_cmdlst **node);
void	ft_redir_exec(t_shell *info, t_cmdlst *node);

//redirlst
void	redirlst_addback(t_redirlst **rlst, char *filename, int fd);

//heredoc
char	*get_limiter(char *cmd);
void	heredoc(char *limiter, t_shell *info, t_cmdlst *next);

//wildcard
int		is_curr_dir(char *cmd, int i);
char	*get_target(char *cmd, int i);
int		target_found(char *file, char *target);
void	files_addback(t_files **files, char *file);

//utils
void	msg_cmd_not_found(char **cmd);
void	free_everything(t_shell *info);
void	swap_str(char **s1, char **s2);
void	ft_free_files_lst(t_files **lst);
int		get_files_num(t_files *files);
t_files	*get_last_files(t_files *files);
void	ft_free_infile_outfile(t_shell *info);

//cmdlst
void	interpret_cmd(char *cmd, t_cmdlst **lst);
void	ft_cmdexec(t_shell *info);

//cmdlst utils
void	ft_free_cmdlst(t_cmdlst **lst);
void	print_lst(t_cmdlst *lst);
void	ft_cmdlst_addback(t_cmdlst	**lst, char *s);
int		to_split(char *s);
char	**interesting_split(char *cmd, int depth, int sq, int dq);
int		cmdlst_is_double(char *s, char *bonus);

//execve
char	*get_cmd_path(char *cmd);

#endif