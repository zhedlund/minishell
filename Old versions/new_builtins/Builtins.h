/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelliott <jelliott@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:27:11 by jelliott          #+#    #+#             */
/*   Updated: 2024/02/23 17:27:14 by jelliott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cd functions
char	*ft_home(char *locate, t_env **head, t_info **info);
char	*ft_gethome(t_env **head, char *locate);
bool	ft_homeset(t_env **head);
char	*ft_cdsub(char *arraystring);
char	*ft_path(char *former);
char	*ft_backone_sub(char *locate, int i);
char	*ft_backone(char *locate);
void	ft_move(char *locate, t_env **head, t_info **info);
void	ft_cd_finish(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_cd_execute(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_cd(t_exec *exec_cmd, t_env **head, t_info **info);

//echo functions
void	ft_printout(int a, char **cmdargs, bool newline);
void	ft_echo(t_exec *exec_cmd, t_env **head, t_info **info);

//pwd functions
void	ft_pwd(t_env **head, t_info **info, t_exec *exec_cmd);
void	ft_multifree(char *a, t_env **head, t_info **info, t_exec *exec_cmd);

//env functions
void	ft_env(char *arraystring, t_env **head, t_info **info, t_exec *exec_cmd);

//exit functions
void	ft_exit(t_exec *exec_cmd, t_env **head, t_info **info);

//unset functions
void	ft_unset(t_exec *exec_cmd, t_env **head, t_info **info)
void	ft_unset_end_free(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_unsetsub(char *inputi, t_env **head);
void	ft_list_middle(t_env *temp);
void	ft_list_start_end(t_env **head, t_env *temp, bool start);

//export functions
void	ft_exportfree(t_exec **exec_cmd, t_env **head, t_info **info);
void	ft_invalid_identifier(t_env **head, t_info **info, t_exec *exec_cmd);
int ft_valididentifier(char *check);
bool	ft_unexpectedtoken(char *check);
bool	ft_syntax_check(t_exec *exec_cmd, t_env **head, t_info **info);
bool	ft_equalpresent(char *check);
void	ft_exportsub(char *toexport, t_env **head);
void	ft_solo_export(t_env **head, t_info **info, t_exec *exec_cmd);
void	valid_identifier_export(t_exec *exec_cmd, t_env **head, t_info **info);
void	ft_export(t_exec *exec_cmd, t_env **head, t_info **info);

//functions that might be useful for all are in export - syntax ones
//also pwd freeing ones might be useful