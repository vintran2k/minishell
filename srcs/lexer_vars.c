/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:10:20 by vintran           #+#    #+#             */
/*   Updated: 2021/12/16 16:30:52 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}

char	*ft_strncat(char *dest, char *src, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && j < n)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int	var_len(char *s)
{
	int	i;
	
	i = 1;
	if (!ft_strncmp(s, "$?", 2) || (s[1] >= '0' && s[1] <= '9'))
		return (2);
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
			while (((char *)env->data)[i] && ((char *)env->data)[i - 1] != '=')
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

int	get_newlen(char *s, char *env, int dq)
{
	int	len;
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	len = 0;
	if (dq == -1)
		len = 1;
	if (ft_strncmp(&s[i], "$?", 2) == 0)
		len += itoa_len(g_vars.error) + i + ft_strlen(&s[i + len]);
	else
		len += ft_strlen(env) + i + ft_strlen(&s[i + len]);
	return (len);
}

void	fill_new(char *dst, char *src, char *env, int beg)
{
	char	*itoa;
	int		varlen;

	varlen = var_len(&src[beg]);
	dst[0] = '\0';
	ft_strcat(dst, src);
	dst[beg] = '\0';
	if (ft_strncmp(&src[beg], "$?", 2) == 0)
	{
		itoa = ft_itoa(g_vars.error);
		ft_strcat(dst, itoa);
		free(itoa);
	}
	else
		ft_strcat(dst, env);
	ft_strcat(dst, &src[beg + varlen]);
}

int	replace_var(t_list **lst, char *env, int dq)
{
	int		i;
	int		newlen;
	char	*new;
	t_list	*tmp;

	tmp = *lst;
	i = 0;
	while (((char *)tmp->data)[i] != '$')
		i++;
	newlen = get_newlen((char *)tmp->data, env, dq);
	new = malloc(newlen + 1);
	if (!new)
		return (malloc_error());
	fill_new(new, tmp->data, env, i);
	free(tmp->data);
	if (dq == -1)
		new[newlen - 1] = '"';
	new[newlen] = '\0';
	tmp->data = new;
	return (0);
}

int	remove_var(t_list *var, int i)
{
	int		j;
	int		len;
	char	*new;

	if (!ft_isalnum(((char *)var->data)[i + 1]))
		return (i);
	j = var_len(&((char *)var->data)[i]);
	len = i + ft_strlen(&((char *)var->data)[i + j]);
	new = malloc(len + 1);
	new[0] = '\0';
	ft_strncat(new, var->data, len);
	new[i] = '\0';
	ft_strncat(&new[i], &((char *)var->data)[i + j], len - i);
	free(var->data);
	var->data = new;
	return (i - 1);
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
					i = 0;
				}
				else
					i = remove_var(tmp, i);
			}
			i++;
		}
		tmp = tmp->next;
	}
	tmp = a->lst;
	t_list	*tmp2;
	while (tmp)
	{
		if (!((char *)tmp->data)[0])
		{
			tmp2 = tmp;
			tmp = tmp->next;
			if (tmp2 == a->lst)
				a->lst = tmp;
			lst_delone(tmp2);
		}
		else if (tmp)
			tmp = tmp->next;
	}
}
