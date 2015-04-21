#ifndef MEMORY__INCLUDED
#define MEMORY__INCLUDED

#include <cassert>
namespace Memory
{
	void * allocate( Natural bytes );
	void * zeroRange( void * handle, Natural bytes );
	void * copyRange( void const * source , void * dest , Natural bytes );
	void freeRange( void * handle );
}

#endif // MEMORY__INCLUDED