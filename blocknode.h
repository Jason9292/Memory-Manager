#include <iostream>

using namespace std;

struct blocknode
{
      unsigned int bsize;
      bool free;
      unsigned char *bptr;
      blocknode *next;
      blocknode *prev;

      blocknode(unsigned int sz,unsigned char *b,bool f=true,blocknode *p=0,blocknode *n=0):
	 bsize(sz),free(f),bptr(b),prev(p),next(n) {}
};

      
