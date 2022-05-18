#ifndef __LNLIST_H
#define __LNLIST_H

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
	LnList *list;
	void *m_Elem;  // Use the Iter_getElem macro to access it
	int index;
} Iter;


// PUBLIC METHODS
#define LnList_new(type_in_list);
#define LnList_get(type_in_list, list_ptr, index);
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
 * T *object = Iter_getElem(T, &iter);
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

LnList _LnList_new(size_t typeSize);
void *_LnList_get(LnList *list, const int index);
void *_SafeLnList_get(size_t typeSize, LnList *list, const int index);
char _LnList_pushFront(LnList *list, const void *newElem);
char _LnList_pushBack(LnList *list, const void *newElem);

// MACROS

// undefine those use for decoration

#undef LnList_new
#undef LnList_get
#undef LnList_pushFront
#undef LnList_pushBack

#undef Iter_getElem

// define with the real body
#define LnList_new(type_in_list) (_LnList_new(sizeof(type_in_list)))


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
	(iterator_ptr)->m_Elem)


#endif  // __LNLIST_H