#ifndef _LLIST_H
# define _LLIST_H

/*
 *	Linked list library
 * 	parsa mahmoudy
 */

#define L_LINK(type) struct { type *next; type *prev; }

#define L_LINK_NEXT(o) ((o)->link.next)
#define L_LINK_PREV(o) ((o)->link.prev)
#define L_LINK_SNEXT(s,d) ((s)->link.next = d)
#define L_LINK_SPREV(s,d) ((s)->link.prev = d)

#define L_LINK_APPEND(l,n) {\
		void *next = L_LINK_NEXT(l);\
		L_LINK_SNEXT(l,n);\
		L_LINK_SPREV(n,l);\
		if (next == NULL) {\
			L_LINK_SPREV(next,n);\
		    L_LINK_SNEXT(n,next);\
		}\
	}

#endif
