/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_ssl_des.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:46:29 by sboulet           #+#    #+#             */
/*   Updated: 2018/03/02 00:22:08 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_SSL_DES_H
# define H_SSL_DES_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pwd.h>
# include "libft/libft.h"

# define B64		1
# define DES		2
# define CBC		4
# define DES3		8
# define CBC3		16

# define FLAG_E		1
# define FLAG_D		2
# define FLAG_I		4
# define FLAG_O		8
# define FLAG_A		16
# define FLAG_K1	32
# define FLAG_K2	64
# define FLAG_K3	128
# define FLAG_V		256

# define BIT_1		1
# define BIT_2		2
# define BIT_3		4
# define BIT_4		8
# define BIT_5		16
# define BIT_6		32
# define BIT_7		64
# define BIT_8		128

typedef struct		s_env
{
	char			cmd;
	int				flag;
	const char		*pass1;
	const char		*pass2;
	const char		*pass3;
	const char		*infile;
	const char		*outfile;
	const char		*iv;
	char			*data;
	char			*out;
	int				nb_blocks;
	int				length;
}					t_env;

typedef struct		s_des
{
	char			key[8];
	char			leftkey[4];
	char			rightkey[4];
	char			subkeys[16][8];
	char			**blocks;
	char			**ciphers;
	char			left[4];
	char			right[4];
	char			exp[8];
	char			box[4];
	char			perm[4];
	char			iv[8];
	char			iv2[8];
}					t_des;

// ssl functions
int					ssl_parse(int ac, char **av, t_env *e);
int					ssl_read(t_env *e);
int					ssl_ed(void);
void				ssl_dispatch(t_env *e);
void				ssl_output(t_env *e);

// errors
int					ssl_help(char *s);
void				ssl_print_usage(t_env *e);
void				ssl_memory_error(t_env *e, t_des *des, const char *fct);
void				ssl_error_flags(const char *arg, char flag, t_env *e);
void				ssl_error_length(t_env *e, t_des *des, int length);
void				des_error_depadding(t_env *e, t_des *des);

// free
void				ssl_free_env(t_env *e);
void				des_free_stc(t_des *des);
void				des_free_keys(t_des *des);

// inits
void				ssl_init_env(t_env *e);
void				des_init_struct(t_env *e, t_des *des);
void				des_init_blocks(t_env *e, t_des *des);
void				des_init_ciphers(t_env *e, t_des *des);

// base64 functions
void				base64_encode(t_env *e, char *s, char *msg);
void				base64_decode(t_env *e, char *s, char *msg);
void				base64_clean(t_env *e);

// DES functions
void				des_encode(t_env *e, const char *pass, char flag);
void				des_decode(t_env *e, const char *pass, char flag);
void				des_create_key(t_env *e, t_des *des);
void				des_create_iv(t_des *des);
void				des_permuted_choice_1(t_des *des);
void				des_shift_keys(t_des *des, int round, int encode);
void				des_permuted_choice_2(t_des *des, int i);
void				des_initial_permutation(t_des *des, int id);
void				des_feistel_network(t_des *des);
void				des_function_f(t_des *des, int id, char *block);
void				des_final_permutation(t_des *des, int id);
void				des_switch_data(t_env *e);
void				des_str_to_hex(t_des *des, char *str);

// constantes
void				constantes_des_permuted_choice_2(t_des *des, int id);
void				constantes_des_s_boxes(t_des *des);
void				constantes_des_permutation_p(t_des *des);

#endif
