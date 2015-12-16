/*! \file		callbacks.c
 *	\brief		ENet callback functions
 *  \version	1.0
 *  \author		Enric Macías López <tm18164@salle.url.edu> Manel Tso Torres <tm17801>
 *  \date		18 de Juny de 2009
*/
#define ENET_BUILDING_LIB 1
#include "enet/enet.h"

static ENetCallbacks callbacks = { malloc, free, rand };

int
enet_initialize_with_callbacks (ENetVersion version, const ENetCallbacks * inits)
{
   if (version != ENET_VERSION)
     return -1;

   if (inits -> malloc != NULL || inits -> free != NULL)
   {
      if (inits -> malloc == NULL || inits -> free == NULL)
        return -1;

      callbacks.malloc = inits -> malloc;
      callbacks.free = inits -> free;
   }
      
   if (inits -> rand != NULL)
     callbacks.rand = inits -> rand;

   return enet_initialize ();
}
           
void *
enet_malloc (size_t size)
{
   void * memory = callbacks.malloc (size);

   if (memory == NULL)
     abort ();

   return memory;
}

void
enet_free (void * memory)
{
   callbacks.free (memory);
}

int
enet_rand (void)
{
   return callbacks.rand ();
}

