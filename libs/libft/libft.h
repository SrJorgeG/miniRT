/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:40:17 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/12 13:01:53 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include "get_next_line.h"

/* *************************************************************************- */
/*                               ESTRUCTURAS                                  */
/* *************************************************************************- */

/*
* Estructura de lista enlazada simple
*- content: puntero al contenido del nodo
*- next: puntero al siguiente nodo
*/
typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}	t_list;

typedef struct s_stack
{
	struct s_list		*first;
	struct s_list		*last;
	size_t				size;
}	t_stack;

/* *************************************************************************- */
/*                          FUNCIONES DE CONVERSIÓN                           */
/* *************************************************************************- */

/*
*- Convierte un string a int
*- Devuelve el número entero resultante
*/
int		ft_atoi(const char *str);

/*
*- Convierte un string a long
*- Devuelve el número largo resultante
*/
long	ft_atol(const char *str);

/*
*- Convierte un string a double
*- Devuelve el valor en formato double
*/
double	ft_atodbl(const char *str);

/*
*- Convierte un entero en string
*- Devuelve un puntero al string resultante (malloc)
*/
char	*ft_itoa(int n);

/* *************************************************************************- */
/*                          FUNCIONES DE MEMORIA                              */
/* *************************************************************************- */

/*
*- Rellena n bytes con cero en la memoria apuntada por s
*- No devuelve nada
*/
void	ft_bzero(void *s, size_t n);

/*
*- Reserva memoria para un array de nmemb elementos de size bytes
*	 y la inicializa a 0
*- Devuelve un puntero a la memoria asignada o NULL si falla
*/
void	*ft_calloc(size_t nmemb, size_t size);

/*
*- Busca el byte c en los primeros n bytes del bloque apuntado por s
*- Devuelve un puntero a la primera ocurrencia o NULL si no se encuentra
*/
void	*ft_memchr(const void *s, int c, size_t n);

/*
*- Compara los primeros n bytes de dos bloques de memoria
*- Devuelve 0 si son iguales, >0 o <0 según la diferencia
*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/*
*- Copia n bytes de src a dest (no seguro si se solapan)
*- Devuelve un puntero a dest
*/
void	*ft_memcpy(void *dest, const void *src, size_t n);

/*
*- Copia n bytes de src a dest de forma segura ante solapamiento
*- Devuelve un puntero a dest
*/
void	*ft_memmove(void *dest, const void *src, size_t n);

/*
*- Rellena los n primeros bytes de s con el byte c
*- Devuelve un puntero a s
*/
void	*ft_memset(void *s, int c, size_t n);

/* *************************************************************************- */
/*                   FUNCIONES DE COMPROBACIÓN DE CARACTERES                  */
/* *************************************************************************- */

/*
*- Comprueba si c es alfanumérico (letra o número)
*- Devuelve 1 si lo es, 0 si no
*/
int		ft_isalnum(int c);

/*
*- Comprueba si c es una letra
*- Devuelve 1 si lo es, 0 si no
*/
int		ft_isalpha(int c);

/*
*- Comprueba si c es un carácter ASCII
*- Devuelve 1 si lo es, 0 si no
*/
int		ft_isascii(int c);

/*
*- Comprueba si c es un dígito (0–9)
*- Devuelve 1 si lo es, 0 si no
*/
int		ft_isdigit(int c);

/*
*- Comprueba si c es imprimible
*- Devuelve 1 si lo es, 0 si no
*/
int		ft_isprint(int c);

/*
*- Convierte c a minúscula si es mayúscula
*- Devuelve el carácter convertido o el original
*/
int		ft_tolower(int c);

/*
*- Convierte c a mayúscula si es minúscula
*- Devuelve el carácter convertido o el original
*/
int		ft_toupper(int c);

/* *************************************************************************- */
/*                           FUNCIONES DE STRINGS                             */
/* *************************************************************************- */

/*
*- Calcula la longitud de un string
*- Devuelve el número de caracteres antes del null
*/
size_t	ft_strlen(const char *ptr);

/*
*- Copia un string en otro con límite de tamaño
*- Devuelve la longitud total de src
*/
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

/*
*- Concatena src en dest con límite de tamaño
*- Devuelve la longitud total que hubiera resultado sin truncar
*/
size_t	ft_strlcat(char *dest, const char *src, size_t size);

/*
*- Compara hasta n caracteres entre dos strings
*- Devuelve 0 si son iguales, >0 o <0 según la diferencia
*/
int		ft_strcmp(const char *s1, const char *s2);

/*
*- Compara hasta n caracteres entre dos strings
*- Devuelve 0 si son iguales, >0 o <0 según la diferencia
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*
*- Busca el carácter c en el string s (primera aparición)
*- Devuelve puntero a la posición o NULL si no se encuentra
*/
char	*ft_strchr(const char *s, int c);

/*
*- Busca el carácter c en el string s (última aparición)
*- Devuelve puntero a la posición o NULL si no se encuentra
*/
char	*ft_strrchr(const char *s, int c);

/*
*- Busca la subcadena little en big con un límite de len caracteres
*- Devuelve un puntero al primer match o NULL si no hay coincidencia
*/
char	*ft_strnstr(const char *big, const char *little, size_t len);

char	*ft_strstr(const char *big, const char *little);

/*
*- Duplica un string
*- Devuelve un puntero a la copia (malloc)
*/
char	*ft_strdup(const char *s);

/*
*- Duplica el string recibido hasta len carácteres;
*- Devuelve un puntero a la copia (malloc)
*/
char	*ft_strndup(const char *s, size_t len);

/*
*- Extrae una subcadena desde start con longitud len
*- Devuelve un nuevo string (malloc)
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*
*- Une dos strings en uno nuevo
*- Devuelve el nuevo string (malloc)
*/
char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strreplace(const char *str, size_t start,
			size_t end, const char *rep);
/*
*- Elimina los caracteres del set del principio y final del string
*- Devuelve el string resultante (malloc)
*/
char	*ft_strtrim(char const *s1, char const *set);

/*
*- Divide un string en substrings usando un delimitador
*- Devuelve un array de strings (malloc)
*/
char	**ft_split(char const *s, char c);

/*
*- Aplica una función a cada carácter y construye un nuevo string
*- Devuelve el string resultante (malloc)
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
*- Aplica una función a cada carácter del string original (modifica in-place)
*- No devuelve nada
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/*
*- Convierte todos los caracteres de un string a minúsculas
*- Devuelve el mismo puntero original modificado
*/
char	*ft_strlower(char *str);

/*
*- Copia hasta dsize caracteres de src a dst
*- Devuelve dst
*/
char	*ft_strncpy(char *dst, const char *src, size_t dsize);

/*
*- Comprueba si un string representa un double válido
*- Devuelve 1 si lo es, 0 si no
*/
int		ft_strisdbl(char *str);

/*
*- Comprueba si un string representa un numero válido
*- Devuelve 1 si lo es, 0 si no
*/
int	ft_strisnum(char *str);
/*
*- Cuenta el número de strings en un array char **
*- Devuelve la cantidad de punteros no NULL
*/
int		ft_lststrlen(char **lst);

/* *************************************************************************- */
/*                      FUNCIONES DE IMPRESIÓN EN FILE DESCRIPTORS            */
/* *************************************************************************- */

/* Escribe un carácter en un descriptor de archivo */
void	ft_putchar_fd(char c, int fd);

/* Escribe un string en un descriptor de archivo */
void	ft_putstr_fd(char *s, int fd);

/* Escribe un string con salto de línea en un fd */
void	ft_putendl_fd(char *s, int fd);

/* Escribe un número entero en un descriptor de archivo */
void	ft_putnbr_fd(int n, int fd);

/* *************************************************************************- */
/*                            FUNCIONES DE LISTAS                             */
/* *************************************************************************- */

/*
*- Crea un nuevo nodo de lista con el contenido dado
*- Devuelve un puntero al nuevo nodo
*/
t_list	*ft_lstnew(void *content);

/*
*- Añade un nodo al principio de la lista
*- No devuelve nada
*/
void	ft_lstadd_front(t_list **lst, t_list *new);

/*
*- Devuelve el número de nodos de la lista
*/
int		ft_lstsize(t_list *lst);

/*
*- Devuelve el último nodo de la lista
*/
t_list	*ft_lstlast(t_list *lst);

/*
*- Añade un nodo al final de la lista
*- No devuelve nada
*/
void	ft_lstadd_back(t_list **lst, t_list *new);

/*
*- Elimina un único nodo usando una función de liberación
*- No libera el siguiente nodo
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/*
*- Elimina y libera todos los nodos de la lista
*- Aplica la función del a cada contenido
*/
void	ft_lstclear(t_list **lst, void (*del)(void *));

/*
*- Elimina y libera todos los nodos de la lista
*- Deja sin liberar su contenido
*/
void	ft_lstclearnodes(t_list **lst, void (*del)(void*));

/*
*- Aplica una función a cada contenido de los nodos de la lista
*- No modifica la lista ni la libera
*/
void	ft_lstiter(t_list *lst, void (*f)(void *));

/*
*- Crea una nueva lista con el resultado de aplicar f a cada nodo
*- Si falla, libera los nodos creados hasta el momento con del
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*
*- Ordena un array de enteros (no una lista enlazada)
*- Modifica el array original directamente
*/
void	ft_lstsort_int(int *lst, int size);

/*
*- Busca en el array lst un match con target en base a la funcion cmp
*- Si cmp devuelve distinto a 0 en algun caso devolvera este nodo.
*/
void	*ft_lstfind_cmp(void *lst, void *target, int (*cmp)(void *, void *));


char	**ft_lst_to_strlist(t_list *first);


/* ************************************************************************* */
/*                           FUNCIONES STACK                                 */
/* ************************************************************************* */

t_stack	*ft_stack_new(void);
void	ft_stack_add_back(t_stack *lst, t_list *node);
void	ft_stack_add_front(t_stack *lst, t_list *node);
t_list	*ft_stack_first(t_stack *lst);
t_list	*ft_stack_last(t_stack *lst);
t_list	*ft_stack_pop_front(t_stack *lst);
t_list	*ft_stack_pop_back(t_stack *lst);
size_t	ft_stack_size(t_stack *lst);
int		ft_stack_is_empty(t_stack *lst);
void	ft_stack_clear(t_stack *lst, void (*del)(void *));

/* *************************************************************************- */
/*                           FUNCIONES AUXILIARES                             */
/* *************************************************************************- */

/*
*- Libera un array de strings (como los generados por split)
*- No devuelve nada
*/
void	ft_free_split(char **arr);

/*
*- Calcula el numero de elementos en un array de strings (como los generados por split)
*- Devuelve un size_t con el tamaño encontrado.
*/
size_t	ft_strlst_len(char **strlst);
#endif
