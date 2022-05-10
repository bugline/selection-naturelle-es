#include <stdio.h>
#include <stdlib.h>


typedef struct LnList {  // Linked list
	size_t typeSize;
	void *first;
	void *last;
} LnList;

struct LnListElemInfo {
	void *prev;
	void *next;
};

typedef struct Iter {
	int index;
} Iter;


// PUBLIC METHODS
#define LnList_get(type_in_list, list_ptr, index);
// TODO: char LnList_set(LnList *list, const int index, void *newElem);
// TODO: char LnList_insert(LnList *list, const int index, void *newElem);
char LnList_pop(LnList *list, const int index);
char LnList_rem(LnList *list, void *ptr);
#define LnList_pushFront(type_in_list, list_ptr, new_element_reference);
#define LnList_pushBack(type_in_list, list_ptr, new_element_reference);
void LnList_clear(LnList *list);

Iter Iterate(LnList *list);
void Iter_next(Iter *iterator);
#define Iter_getElem(element_type,iterator_ptr);


/* To go threw a list of type T
 *
 * ```
 * Iter iter = Iterate(&list);
 * T object = Iter_getElem(T, &iter);
 * 
 * while (object != NULL) {
 * 	
 * 	// Do stuff with "object" and "iter.index"
 * 
 * 	Iter_next(&iter);
 * 	object = Iter_getElem(T, &iter);
 * }
 * 
 * ```
 */



// PRIVATE FUNCTIONS use the coresponding macros to call them
void *_LnList_get(LnList *list, const int index);
void *_SafeLnList_get(size_t typeSize, LnList *list, const int index);
char _LnList_pushFront(LnList *list, const void *newElem);
char _LnList_pushBack(LnList *list, const void *newElem);

// MACROS

#undef LnList_get
#undef LnList_pushFront
#undef LnList_pushBack

#undef Iter_getElem


#ifdef RELEASE
	#define LnList_get(type_in_list,list_ptr,index) \
		(*( (type_in_list *) _LnList_get( (list_ptr), (index) ) ))

	#define LnList_pushFront(type_in_list,list_ptr,new_elem_ref)  \
		( _LnList_pushBack( list_ptr, new_elem_ref) )

	#define LnList_pushBack(type_in_list,list_ptr,new_elem_ref)  \
		( _LnList_pushBack( list_ptr, new_elem_ref) )

#else
	#define _CHECK_PTR(type,ptr) ( &(*( (type *) ptr )) )

	#define LnList_get(type_in_list,list_ptr,index)                      \
		(*( (type_in_list *) _SafeLnList_get( sizeof(type_in_list),  \
			(list_ptr), (index) ) ))

	#define LnList_pushFront(type_in_list,list_ptr,new_elem_ref)  \
		( _LnList_pushFront( _CHECK_PTR(LnList, list_ptr),    \
			_CHECK_PTR(type_in_list, new_elem_ref) ) )

	#define LnList_pushBack(type_in_list,list_ptr,new_elem_ref)  \
		( _LnList_pushBack( _CHECK_PTR(LnList, list_ptr),    \
			_CHECK_PTR(type_in_list, new_elem_ref) ) )
#endif

#define Iter_getElem(element_type,iterator_ptr) ((element_type *)  \
	(iterator_ptr))


// STATIC FUNCTIONS

static struct LnListElemInfo *_LnList_GetInfo(const void *elem)
{
	/*     <- elem_info -> <- object ->
	 *    |---------------|------------|
	 *    \__ the address of the begining of elem_info is returned 
	 */
	return (struct LnListElemInfo *) (elem - sizeof(struct LnListElemInfo));
}

static void *_LnList_malloc(const size_t size)
{
	/*     <-  Allocates this space  ->
	 *     <- elem_info -> <- object ->
	 *    |---------------|------------|
	 *                    \__ the address of the begining of object is
	 *                        returned
	 */
	return malloc(sizeof(struct LnListElemInfo) + size) +
		sizeof(struct LnListElemInfo);
}

static void _LnList_copy(void *dest, const void *src, const size_t bytes)
{
	/* Copies byte by byte each value
	 *    |----------| dest
	 *     ^^^^^^^^^^
	 *    |----------| src
	 */
	for (size_t i = 0; i < bytes; i++) {
		((char *) dest)[i] = ((const char *) src)[i];
	}
}


// LIST METHODS
LnList LnList_new(size_t typeSize)
{
	return (LnList) {
		typeSize,  // type size
		NULL,      // first elem ptr
		NULL       // last elem ptr
	};
}

void *_LnList_get(LnList *list, const int index)
{
	void *nextPtr = list->first;
	
	// Go threw the list
	for (int i = 0; i < index; i++) {
		if (nextPtr == NULL) {
#ifndef RELEASE
			printf("[LnList_get] the list is %d elements long but you are trying to access the %d element\n", i, index);
#endif
			return NULL;  // The list is not long enough;
		}

		nextPtr = _LnList_GetInfo(nextPtr)->next;
	}

	return nextPtr;
}

void *_SafeLnList_get(size_t typeSize, LnList *list, const int index)
{
	if (typeSize != list->typeSize) {
		printf("[LnList_get] LnList_get was called with a different type then the one in the list\n");
		exit(-1);
	}

	return _LnList_get(list, index);
}

char LnList_pop(LnList *list, const int index)
{
	void *elem = _LnList_get(list, index);

	if (elem == NULL)
		return -1;
	
	return LnList_rem(list, elem);
}

char LnList_rem(LnList *list, void *ptr)
{
	/* .-----------.                 .-----------.
	 * |  previous |<----------------|   next    |
	 * |  element  |---------------->|  element  |
	 * `-----------'                 `-----------'
	 *                .-----------.
	 *             x--|  removed  |<-x
	 *             x->|  element  |--x
	 *                `-----------'
	 */

	struct LnListElemInfo *info = _LnList_GetInfo(ptr);

	if (info->prev != NULL)
		_LnList_GetInfo(info->prev)->next = info->next;
	if (info->next != NULL)
		_LnList_GetInfo(info->next)->prev = info->prev;
	
	if (list->first == ptr)
		list->first = NULL;
	if (list->last == ptr)
		list->last = NULL;

	free(info);
	
	return 0;
}

char _LnList_pushFront(LnList *list, const void *newElem)
{
	// Alloc space for the new element
	void *tmp = _LnList_malloc(list->typeSize);

	if (tmp == NULL) {
#ifndef RELEASE
		printf("[LnList_append] malloc failed (T^T)\n");
#endif	
		return -1;  // Failed to malloc
	}

	// Make a copy of the input element
	_LnList_copy(tmp, newElem, list->typeSize);
	
	struct LnListElemInfo *info = _LnList_GetInfo(tmp);

	// Set it's next ptr to null because it's at the end of the list
	info->prev = NULL;

	// If the list wasn't empty
	if (list->first != NULL) {
		// Set it's prev ptr to the previous last
		info->next = list->first;
		// Set the previous's next ptr to the new element
		_LnList_GetInfo(list->first)->prev = tmp;
	} else {
		list->last = tmp;
	}

	// Set the last ptr to be to the new element
	list->first = tmp;

	return 0;
}

char _LnList_pushBack(LnList *list, const void *newElem)
{
	// Alloc space for the new element
	void *tmp = _LnList_malloc(list->typeSize);

	if (tmp == NULL) {
#ifndef RELEASE
		printf("[LnList_append] malloc failed (T^T)\n");
#endif	
		return -1;  // Failed to malloc
	}

	// Make a copy of the input element
	_LnList_copy(tmp, newElem, list->typeSize);
	
	struct LnListElemInfo *info = _LnList_GetInfo(tmp);

	// Set it's next ptr to null because it's at the end of the list
	info->next = NULL;

	// If the list wasn't empty
	if (list->last != NULL) {
		// Set it's prev ptr to the previous last
		info->prev = list->last;
		// Set the previous's next ptr to the new element
		_LnList_GetInfo(list->last)->next = tmp;
	} else {
		list->first = tmp;
	}

	// Set the last ptr to be to the new element
	list->last = tmp;

	return 0;
}

void LnList_clear(LnList *list)
{
	void *next = list->first;
	while (next != NULL) {
		void *tmp = _LnList_GetInfo(next)->next;
		free(_LnList_GetInfo(next));
		next = tmp;
	}
}


// ITER METHODS

Iter Iterate(LnList *list)
{
	return (Iter) {
		list,
		list->first,
		0
	};
}

void Iter_next(Iter *iter)
{
	iter->m_Elem = _LnList_GetInfo(iter->m_Elem)->next;
	iter->index += 1;
}
