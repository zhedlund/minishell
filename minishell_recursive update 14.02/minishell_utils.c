/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhedlund <zhedlund@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:27:07 by zhedlund          #+#    #+#             */
/*   Updated: 2024/02/14 01:08:36 by zhedlund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tree.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ps;
	char	uc;

	ps = (char *)s;
	uc = (char)c;
	while (n > 0)
	{
		ps[n - 1] = uc;
		n--;
	}
	return (ps);
}

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int i = 0;

	if (!s1 || !s2)
		return (0);
	while (*s1)
	{
		i = 0;
		while (s2[i])
		{
			if (*s1 == s2[i])
				return ((char *)s1);
			i++;
		}
		s1++;
	}
	return (0);
}

char *ft_strtok(char *str, const char *delim)
{
	static char	*token;
	char		*found;
	char		*result;
	
	if (str != NULL)
		token = str;
	if (token == NULL || *token == '\0')
		return (NULL);
	found = ft_strpbrk(token, delim);
	if (found != NULL)
	{
		*found = '\0';
		found++;
	}
	result = token;
	token = found;
	return (result);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n -1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = c;
	if (ch == '\0')
	{
		i = ft_strlen(s);
		return ((char *)s + i++);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dsize;
	size_t	ssize;

	dsize = ft_strlen(dst);
	ssize = ft_strlen(src);
	if (size <= dsize)
		return (size + ssize);
	i = dsize;
	j = 0;
	while ((i + j) < (size - 1) && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dsize + ssize);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*newstr;

	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	newstr = malloc(sizeof(char) * len);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, len);
	ft_strlcat(newstr, s2, len);
	return (newstr);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

static char	*num_to_array(char *arr, unsigned int number, long int len)
{
	while (number > 0)
	{
		arr[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (arr);
}

static long int	num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		len;
	unsigned int	num;

	len = num_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		num = n * -1;
		str[0] = '-';
	}
	else
		num = n;
	str = num_to_array(str, num, len);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	char			*src;
	size_t			sublen;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	src = (char *)s + start;
	if (ft_strlen(src) < len)
		sublen = ft_strlen(src) + 1;
	else
		sublen = len + 1;
	sub = malloc(sublen * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, src, sublen);
	return (sub);
}

static	int	wordcount(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		index;
	int		len;

	index = 0;
	words = malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!words)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			words[index++] = ft_substr(s, 0, len);
			s += len;
		}
		else
		{
			s++;
		}
	}
	words[index] = NULL;
	return (words);
}
