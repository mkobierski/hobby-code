#pragma once

#include <cassert>

#include "Types.hpp"

namespace Memory
{
	void * allocate( Natural bytes );
	void * zeroRange( void * handle, Natural bytes );
	void * copyRange( void const * source , void * dest , Natural bytes );
	void freeRange( void * handle );
}