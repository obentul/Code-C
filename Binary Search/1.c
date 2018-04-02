#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
long binary_search(long *collection,long size,long test);

int main(int argc,char **argv)
{
	long a[]={1,2,3,4,5,6,7,8,9,20,30,40,50,60,70,100};
	
	int result;
	long size;
	long test;
	long *ap=a;
	size=sizeof(a)/sizeof(long);

	//is
	result = binary_search(a,size,70);
	
	sleep(1);
	
	result = binary_search(a,size,89);
	
	if(result!=-1)
	{printf("in\n");}
	else
	{printf("not in\n");}

	return 0;
}



/*desc:binary search to check if is in the collection
 *return: num -- location
 *	  -1 -- not in
 *params: void *collection  --  collecion
	  long size	    --  item num of collection
	  long test	    --  item to be checked
 *
 * */
long binary_search(long *collection,long size,long test)
{
	long *p;
	long location;
	long ret;

	location = size/2;

	p=collection+location;
	
	if(test==*p)
	{
		return location;
	}
	else
	{
		if(p==collection+1||p==collection+size-1)
		{
			return -1;
		}
		else if(test>*p)
		{
			ret=binary_search(p,size/2+1,test);
			if(ret==-1)
				{
					return -1;	
				}
		}
		else if(test<*p)
		{
			ret=binary_search(collection,size/2+1,test);
			if(ret=-1)
				{
					return -1;
				}
		}
	}

}
