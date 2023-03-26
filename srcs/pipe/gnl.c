//
// Created by dcarvalh on 3/26/23.
//
static size_t	ft_strlen(const char *str)
{
    size_t	i;

    i = 0;
    if (!str)
        return (0);
    while (str[i] && str[i] != '\n')
        i++;
    return ((i + (str[i] == '\n')));
}

static char	*ft_strjoin(char *str1, char *str2)
{
    char	*ret;
    size_t	i;

    ret = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
    if (!ret)
        return (NULL);
    i = -1;
    while (str1 && str1[++i])
        ret[i] = str1[i];
    i += (!str1);
    while (*str2)
    {
        ret[i++] = *str2;
        if (*str2++ == '\n')
            break ;
    }
    ret[i] = 0;
    if (str1)
        free (str1);
    return (ret);
}

static int	next_line(char *stash)
{
    int	i;
    int	j;

    i = -1;
    j = -1;
    while (stash[++i])
    {
        if (stash[i] == '\n')
        {
            stash[i++] = 0;
            j = 0;
            break ;
        }
        stash[i] = 0;
    }
    if (!j)
    {
        while (stash[i])
        {
            stash[j++] = stash[i];
            stash[i++] = 0;
        }
    }
    return (j);
}

char	*get_next_line(int fd)
{
    char		*line;
    static char	stash[101];
    size_t		i;

    i = -1;
    if (read(fd, 0, 0) < 0 || 100 < 1)
    {
        while (stash[++i])
            stash[i] = 0;
        return (NULL);
    }
    line = NULL;
    while (*stash || read(fd, stash, 100) > 0)
    {
        line = ft_strjoin(line, stash);
        if (next_line(stash) != -1)
            break ;
    }
    return (line);
}