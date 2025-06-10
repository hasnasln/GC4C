#ifndef S_MALLOC_H
# define S_MALLOC_H

# include <stdlib.h>


/*
	@s_malloc_node: Linked list node yapısı, tahsis edilen belleklerin tutulduğu.
	!! Bu yapı, tahsis edilen belleklerin adresini ve
	!! linked list içinde bir sonraki ve önceki node'ları tutar.
*/

typedef struct s_malloc_node
{
	void					*data;
	struct s_malloc_node	*next;
	struct s_malloc_node	*prev;

}							t_node;

/*
	@s_safe_malloc: Linked list yapısı, tahsis edilen belleklerin tutulduğu.
	!! Bu yapı, tahsis edilen belleklerin baş ve son node'larını tutar.
*/
typedef struct s_safe_malloc
{
	t_node					*head;
	t_node					*tail;
}							t_safe_malloc;



/*
	HEAD_TO_TAIL: Linked list arama yönü, baştan sona.
	TAIL_TO_HEAD: Linked list arama yönü, sondan başa.
*/
typedef enum e_direction
{
	HEAD_TO_TAIL,
	TAIL_TO_HEAD
}							t_direction;

/*--------------------Get-Data-------------------------------*/

/*
	!! Bu fonksiyon, tahsis edilen belleklerin tutulduğu
	!! linked list yapısını döndürür.
*/
t_safe_malloc				*get_safe_malloc_data(void);

/*--------------------S-MALLOC-------------------------------*/

/*
	Bellek tahsisi için kullanılır.
	@param __size: Tahsis edilecek bellek boyutu.
	@return: Tahsis edilen bellek adresi.
	
	*! tahsisi sırasnda hata çıkar ise program başlangıcından itibaren
	*! tahsis edilen tüm bellekleri serbest bırakır ve hata mesajı verir.
*/
void						*s_malloc(size_t __size);

/*--------------------S-FREE---------------------------------*/
/*
	Tahsis edilen tüm bellekleri serbest bırakır.
*/
void						safe_free_data(void);

/*
	@ptr: Serbest bırakılacak bellek adresi.
	@direction: Arama yönü (HEAD_TO_TAIL veya TAIL_TO_HEAD).
	!! Bu fonksiyon, verilen bellek adresini linked list içinde arar
	!! ve bulursa serbest bırakır.
*/
void						which_directions_search(void *ptr,
								t_direction direction);

/*
	@node: Serbest bırakılacak node.
	!! Bu fonksiyon, verilen node'u serbest bırakır.
*/
void						free_node(t_node *node);

/*-----------------Clear-Residual-Data-----------------------*/

/*
	@ptr: Temizlenecek bellek adresi.
	@__size: Temizlenecek bellek boyutu.
	!! Bu fonksiyon, verilen bellek adresindeki tüm verileri sıfırlar.
*/
void						clear_residual_data(void *ptr, size_t __size);

#endif