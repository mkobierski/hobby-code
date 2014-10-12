void * Memory::allocate(Natural bytes)
{
	return malloc(bytes);
}
void * Memory::zeroRange(void * handle, Natural bytes)
{
	if (handle)
	{
		memset(handle, 0, bytes);
	}
	return handle;
}
void Memory::freeRange(void * handle)
{
	free(handle);
}