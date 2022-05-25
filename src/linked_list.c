#include "linked_list.h"


// STATIC FUNCTIONS

static struct LnListElemInfo *_LnList_GetInfo(const void *elem)
{
	/*     <- elem_info -> <- object ->
	 *    |---------------|------------|
	 *    \__ the address of the begining of elem_info is returned 
	 */
	return (struct LnListElemInfo *) (elem - sizeof(struct LnListElemInfo));
}

/*------------------------------------------------------------------*/

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

/*------------------------------------------------------------------*/

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

/*------------------------------------------------------------------*/
// LIST METHODS

LnList _LnList_new(size_t typeSize)
{
	return (LnList) {
		typeSize,  // type size
		NULL,      // first elem ptr
		NULL       // last elem ptr
	};
}

/*------------------------------------------------------------------*/

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

/*------------------------------------------------------------------*/

void *_SafeLnList_get(size_t typeSize, LnList *list, const int index)
{
	if (typeSize != list->typeSize) {
		printf("[LnList_get] LnList_get was called with a different type then the one in the list\n");
		exit(-1);
	}

	return _LnList_get(list, index);
}

/*------------------------------------------------------------------*/

char LnList_pop(LnList *list, const int index)
{
	void *elem = _LnList_get(list, index);

	if (elem == NULL)
		return -1;
	
	return LnList_rem(list, elem);
}

/*------------------------------------------------------------------*/

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
		list->first = info->next;
	if (list->last == ptr)
		list->last = info->prev;

	free(info);
	
	return 0;
}

/*------------------------------------------------------------------*/

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

	if (list->last == NULL) {
		info->next = NULL;
	}

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

/*------------------------------------------------------------------*/

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

	if (list->first == NULL) {
		info->prev = NULL;
	}

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

/*------------------------------------------------------------------*/

void LnList_clear(LnList *list)
{
	void *next = list->first;
	while (next != NULL) {
		void *tmp = _LnList_GetInfo(next)->next;
		free(_LnList_GetInfo(next));
		next = tmp;
	}
}

/*------------------------------------------------------------------*/
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