#include "BlockList.h"
#include <iostream>
#include <sstream>
#include "blocknode.h"

using namespace std;

class MemoryManager
{
  public:
   MemoryManager(unsigned int memsize);
   unsigned char * malloc(unsigned int request);
   void free(unsigned char * blockptr);
   blocknode *getFirstPtr();
   friend ostream & operator<<(ostream & out,const MemoryManager &M);

  private:
   unsigned int memsize;
   unsigned char *baseptr;
   blocknode * firstBlock;

   void mergeForward(blocknode *p);
   void splitBlock(blocknode *p,unsigned int chunksize);
};
  
	
