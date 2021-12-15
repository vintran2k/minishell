/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:10:20 by vintran           #+#    #+#             */
/*   Updated: 2021/12/15 13:27:55 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}

int	var_len(char *s)
{
	int	i;
	
	i = 1;
	while (s[i] && ft_isalnum(s[i]))
		i++;
	return (i);
}


char	*is_in_env(char *s)
{
	int		len;
	t_list *env;
	int		i;

	len = var_len(s);
	if (len == 1)
		return (NULL);
	s++;
	env = g_vars.env;
	while (env)
	{
		if (ft_strncmp(s, (char *)env->data, len - 1) == 0)
		{
			i = 1;
			while (((char *)env->data)[i - 1] != '=')
				i++;
			return (&((char *)env->data)[i]);
		}
		env = env->next;
	}
	return (NULL);
}

int	itoa_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nb;

	len = itoa_len(n);
	nb = n;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		str[len] = nb % 10 + '0';
		len--;
		nb /= 10;
	}
	return (str);
}

int	replace_var(t_list **lst, char *env, int dq)
{
	int		i;
	int		j;
	int		len;
	char	*new;
	t_list	*tmp;
	int		err;


	tmp = *lst;
	i = 1;
	//printf("env = |%s| et data = |%s|\n", env, tmp->data);
	//while (env && env[i - 1] != '=')	//strchr
	//	i++;
	j = 0;
	while (((char *)tmp->data)[j] != '$')
		j++;
	int	varlen = var_len(&((char *)tmp->data)[j]);
	len = 0;
	if (dq == -1)
		len = 1;
	err = ft_strncmp(&((char *)tmp->data)[j], "$?", 2);
	if (err == 0)
		len += itoa_len(g_vars.error) + j + ft_strlen(&((char *)tmp->data)[j + varlen]);
	else
		len += ft_strlen(env) + j + ft_strlen(&((char *)tmp->data)[j + varlen]);
	new = malloc(len + 1);
	if (!new)
		return (malloc_error());
	new[0] = '\0';
	//((char *)tmp->data)[j] = '\0';
	ft_strcat(new, ((char *)tmp->data));
	new[j] = '\0';
	if (err == 0)
	{
		char	*itoa = ft_itoa(g_vars.error);
		ft_strcat(new, itoa);
		free(itoa);
	}
	else
		ft_strcat(new, env);
	ft_strcat(new, &((char *)tmp->data)[j + varlen]);
	free(tmp->data);
	if (dq == -1)
		new[len - 1] = '"';
	new[len] = '\0';
	tmp->data = new;
	return (0);
}

void	remove_var(t_list *var, int dq)
{
	int	i;

	i = 0;
	while (((char *)var->data)[i] != '$')
		i++;
	if (ft_isalnum(((char *)var->data)[i + 1]))
		((char *)var->data)[i] = '\0';
}

void	parse_vars(t_lexer *a)
{
	t_list	*tmp;
	int		i;
	char	*env;

	tmp = a->lst;
	while (tmp)
	{
		i = 0;
		while (((char *)tmp->data)[i])
		{
			quote_maj(a, ((char *)tmp->data)[i]);
			if (((char *)tmp->data)[i] == '$' && a->q == 1)
			{
				env = is_in_env(&((char *)tmp->data)[i]);
				if (env || ft_strncmp(&((char *)tmp->data)[i], "$?", 2) == 0)
				{
					replace_var(&tmp, env, a->dq);
					//break;
				}
				else
					remove_var(tmp, a->dq);
			}
			i++;
		}
		tmp = tmp->next;
	}
}
