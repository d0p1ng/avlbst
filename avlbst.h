#pragma once

#include<stdint.h>

//=============================================================================
// The structure of the AVL binary search tree node.
// Do not modify any of the members except userdata by your own.
// Manage the tree by calling the API functions.
//-----------------------------------------------------------------------------
typedef struct avlbst_struct avlbst_t, *avlbst_p;
struct avlbst_struct
{
	size_t key;
	avlbst_p l_child; // The child who has a lesser key value
	avlbst_p r_child; // The child who has a greater key value
	avlbst_p prev; // Previous inserted
	avlbst_p next; // Next inserted
	int height;
	void* userdata;
};

//=============================================================================
// Func: avlbst_insert
// Desc: Insert an item into a avlbst tree. You can find the item by the key
//   faster if you use the avlbst functions.
// Params:
//   ppavlbst: A pointer to the tree. Must be a valid value.
//   key: A value represents the data.
//   userdata: The data you put in with the tree.
// Return value:
//   Nonzero if success. The function fails when the key already exists in the
//   tree.
//-----------------------------------------------------------------------------
int avlbst_insert(avlbst_p *ppavlbst, size_t key, void *userdata);

//=============================================================================
// Func: avlbst_search
// Desc: Search the tree to get the data specified by key.
// Params:
//   pavlbst: The tree.
//   key: A value represents the data you want to search.
//   ppmatch: A pointer you use it to retrieve the matched avlbst node.
// Return value:
//   Nonzero if success.
//-----------------------------------------------------------------------------
int avlbst_search(avlbst_p pavlbst, size_t key, avlbst_p *ppmatch);

//=============================================================================
// Func: avlbst_find_max_key
// Desc: Retrieve the maximum key value from a tree.
// Params:
//   pavlbst: The tree.
//   ppn: A pointer to retrieve which node has the specific key value, Can be
//     NULL.
// Return value:
//   The maximum key value. If pavlbst is NULL, the function returns 0.
//-----------------------------------------------------------------------------
size_t avlbst_find_max_key(avlbst_p pavlbst, avlbst_p *ppn);

//=============================================================================
// Func: avlbst_find_min_key
// Desc: Retrieve the minimum key value from a tree.
// Params:
//   pavlbst: The tree.
//   ppn: A pointer to retrieve which node has the specific key value, Can be
//     NULL.
// Return value:
//   The minimum key value. If pavlbst is NULL, the function returns 0.
//-----------------------------------------------------------------------------
size_t avlbst_find_min_key(avlbst_p pavlbst, avlbst_p *ppn);

//=============================================================================
// Func: avlbst_remove
// Desc: Remove a node from the tree.
// Params:
//   ppavlbst: A pointer to the tree. Must be a valid value.
//   key: A value represents the data.
//   on_free: A function pointer used to free the userdata, can be NULL.
// Return value:
//   If the matched node can be found, nonzero is returned. Otherwise returns
//   zero.
//-----------------------------------------------------------------------------
int avlbst_remove(avlbst_p *ppavlbst, size_t key, void(*on_free)(void *userdata));

//=============================================================================
// Func: avlbst_first
// Desc: Get the first inserted node of a whole tree
// Params:
//   pavlbst: The tree.
// Return value:
//   The first inserted node from the tree. Used to iterate the tree.
//-----------------------------------------------------------------------------
avlbst_p avlbst_first(avlbst_p pavlbst);

//=============================================================================
// Func: avlbst_last
// Desc: Get the last inserted node of a whole tree
// Params:
//   pavlbst: The tree.
// Return value:
//   The last inserted node from the tree. Used to iterate the tree reverse.
//-----------------------------------------------------------------------------
avlbst_p avlbst_last(avlbst_p pavlbst);

//=============================================================================
// Func: avlbst_free
// Desc: Free the whole tree.
// Params:
//   ppavlbst: A pointer to the tree which is being freed.
//   on_free: A function pointer used to free the userdata, can be NULL.
//-----------------------------------------------------------------------------
void avlbst_free(avlbst_p *ppavlbst, void(*on_free)(void *userdata));

//=============================================================================
// Func: avlbst_clone
// Desc: Clone the whole tree. Usually used in bucket sort algorithm.
// Params:
//   pavlbst: The root node of a tree to be cloned.
// Return value:
//   A pointer to the root node of the cloned AVL tree. If the function failed,
//     the returned value is NULL and you can check out errno for further
//     information.
// Remarks:
//   The `key' field and the `userdata' field were kept the same to the
//     original tree. To free the cloned tree, call avlbst_free(). Please NOTE
//     that if the `userdata' field were used as a pointer which referenced to
//     your own data, you probably don't want the pointer to be double freed.
//     So the second parameter of the function avlbst_free() which is `on_free'
//     should be NULL at this point.
//-----------------------------------------------------------------------------
avlbst_p avlbst_clone(avlbst_p pavlbst);

//=============================================================================
// Func: avlbst_defrag
// Desc: Perform the defragment to the avlbst to make the memory layout more
//   compact by move the nodes to lower addresses, and collect the previously
//   freed memory to a larger block which can contain larger data.
// Return value:
//    The count of the moved nodes.
// Remarks:
//   Using avlbst by frequently insert and remove nodes creates memory holes
//     which only has the capacity to contain smaller memory blocks than an
//     avlbst node. These small freed memory blocks cause memory management
//     performance problems, and could not be used effectively since they are
//     too small to contain larger data.
//
//   The defragment is performed by calling malloc() to try to get a lower
//     address, then copy its contents to the new location, then free the
//     previous memory block. if malloc() returns a higher address, the node
//     will not be moved and the new memory block will be freed.
//
//   Not all platforms allocate memory from low to high addresses. If the
//     current platform always allocates memory from the tail of the last
//     allocated address, this function will not work at all. Calling this
//     function at this point will only result in wasted performance.
//
//   Always do testing on your targeting platform to make sure you really need
//     to call this function.
//-----------------------------------------------------------------------------
size_t avlbst_defrag(avlbst_p *ppavlbst);
