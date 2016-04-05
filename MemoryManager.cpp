// Jason Mellinger		Data Structures		MemoryManagement Project

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include "MemoryManager.h"

using namespace std;


ostream & operator<<(ostream & out,const MemoryManager &M)
{
   blocknode *tmp = M.firstBlock;
   assert(tmp);
   while(tmp)
   {
      out << "[" << tmp->bsize << ",";
      if (tmp->free)
	 out << "free] ";
      else
	 out << "allocated] ";
      if (tmp->next)
	 out << " -> "; 
      tmp = tmp->next;
   }
   return out;
}

MemoryManager::MemoryManager(unsigned int memtotal): memsize(memtotal)
{
   baseptr = new unsigned char[memsize];
   firstBlock = new blocknode(memsize,baseptr);
}

blocknode *MemoryManager::getFirstPtr()
{
   return firstBlock;
}

unsigned char * MemoryManager::malloc(unsigned int request)
// Finds the first block in the list whose size is >= request
// If the block's size is strictly greater than request
// the block is split, with the newly create block being free. 
// It then changes the original block's free status to false
{
	blocknode *tmp = firstBlock;						//create new tmp node and set equal to pointer of first blocknode in linked list
	while (tmp->bsize < request || tmp->free == false){			//while tmp node is smaller than request or already taken
		tmp = tmp->next;						//iterate to next node, until it is at least as big as the request
	}
	if (tmp->bsize == request){						//if node's size is equal to the request
		tmp->free = false;						//change the status of the node to not be free
	}
	else if (tmp->bsize > request) {					//if node's size is bigger than the request
		splitBlock(tmp, request);					//call the splitBlock function
		tmp->free = false;						//change the status of the node to not be free
	}
	return tmp->bptr;							//return the base pointer of the node

}

void MemoryManager::splitBlock(blocknode *p, unsigned int chunksize)
// Utility function. Inserts a block after that represented by p
// changing p's blocksize to chunksize; the new successor node 
// will have blocksize the original blocksize of p minus chunksize and 
// will represent a free block.  
// Preconditions: p represents a free block with block size > chunksize
// and the modified target of p will still be free.

{
	int newSize = p->bsize - chunksize;						//create a new node size that is the old node size minus the chunksize
	p->bsize = chunksize;								//set the node size equal to chunk size
	p->next = new blocknode(newSize, p->bptr + chunksize, true, p, p->next);	//create a new block(node) with the new size, updated basepointer, status free
}

void MemoryManager::free(unsigned char *blockptr)
// makes the block represented by the blocknode free
// and merges with successor, if it is free; also 
// merges with the predecessor, it it is free
{				
	blocknode *tmp = firstBlock;
	while (tmp->bptr != blockptr && tmp != NULL){				//iterate through nodes until the block pointer is equal to the one in the function
		tmp = tmp->next;
	}
	
	tmp->free = true;							//set that block's status to free
	
	if (tmp->prev && tmp->prev->free){					//if the block before it is also free call merge forward
		mergeForward(tmp->prev);
	}
	if (tmp->next && tmp->next->free){					//if the block after it is also free call merge forward
		mergeForward(tmp);
	}

}

void MemoryManager::mergeForward(blocknode *p)
// merges two consecutive free blocks
// using a pointer to the first blocknode;
// following blocknode is deleted
{
