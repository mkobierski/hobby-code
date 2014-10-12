
namespace Memory
{
	void * allocate(Natural bytes);
	void * zeroRange(void * handle, Natural bytes);
	void freeRange(void * handle);
}