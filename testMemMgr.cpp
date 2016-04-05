#include <iostream>
#include <cassert>
#include "MemoryManager.h"

int main()
{
   MemoryManager heaper(2048);
   cout << "heap initialized\n";
   cout << "Here is the block list\n";
   cout << "\n-------------BlockList start------------------\n";
   cout << heaper << endl;
   cout << "-------------BlockList end------------------\n\n";
   cout << "Executing p1 = malloc(10):\n";
   unsigned char * p1 = heaper.malloc(10);
   // Debug
   blocknode *first = heaper.getFirstPtr();
   assert(first->bsize == 10);
   assert(first->next->bsize == 2038);
   // End Debug

   cout << "malloc done\n";
   cout << "Here is the block list\n";
   cout << "\n-------------BlockList start------------------\n";
   cout << heaper << endl;
   cout << "-------------BlockList end------------------\n\n";

   cout << "Executing p2 = malloc(20):\n";
   unsigned char *p2 = heaper.malloc(20);
   cout << "malloc done\n";
   cout << "Here is the block list\n";
   cout << "\n-------------BlockList start------------------\n";
   cout << heaper << endl;
   cout << "-------------BlockList end------------------\n\n";

   cout << "Executing free(p1):\n";
   heaper.free(p1);
   cout << "Here is the block list\n";
   cout << "\n-------------BlockList start------------------\n";
   cout << heaper << endl;
   cout << "-------------BlockList end------------------\n\n";

   cout << "Now do a malloc for a block too big for the initial open block" << endl;
   cout << "Executing p1 = malloc(15)" << endl;
   p1 = heaper.malloc(15);
   cout << "malloc done\n";
   cout << "Here is the block list\n";
   cout << "\n-------------BlockList start------------------\n";
   cout << heaper << endl;
   cout << "-------------BlockList end------------------\n\n";

   cout << "Next free the most recently allocated pointer (p1)\n";
   heaper.free(p1);
   cout << "Here is the block list\n";
   cout << "\n-------------BlockList start------------------\n";
   cout << heaper << endl;
   cout << "-------------BlockList end------------------\n\n";

   cout << "Next free p2\n";
   heaper.free(p2);
   cout << "Here is the block list\n";
   cout << "-------------BlockList start------------------\n";
   cout << heaper << endl;
   cout << "\n-------------BlockList end------------------\n\n";

   return 0;
}
