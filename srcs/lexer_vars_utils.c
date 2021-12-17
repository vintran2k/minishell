/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_vars_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 13:01:53 by vintran           #+#    #+#             */
/*   Updated: 2021/12/17 13:27:19 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_isalnum(int c)
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
	t_list	*env;
	int		len;
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
