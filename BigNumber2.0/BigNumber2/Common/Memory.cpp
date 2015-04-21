void * Memory::allocate(Natural bytes)
{
	return malloc( bytes );
}

void * Memory::zeroRange(void * handle, Natural bytes)
{
	if ( handle )
	{
		memset( handle , 0 , bytes );
	}
	return handle;
}

void * Memory::copyRange( void const * source , void * dest , Natural bytes )
{
	Natural endSource = reinterpret_cast< Natural >( source ) + bytes;
	Natural endDest = reinterpret_cast< Natural >( dest ) + bytes;
	if( source < dest )
	{
		assert( endSource < reinterpret_cast< Natural >( dest ) );
	}
	else
	{
		assert( endDest < reinterpret_cast< Natural >( source ) );
	}
	return memcpy ( dest , source, bytes);
}

void Memory::freeRange( void * handle )
{
	free( handle );
}