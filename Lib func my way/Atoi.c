#include <stdio.h>
#include <unistd.h>

int atoi(char *str);

int main(int argc,char ** argv)
{
		char *str="+123";
		char *str1="-123";
		
		printf("str=%d\n",atoi(str));
		printf("str1=%d\n",atoi(str1));
		
		return 0;
}

int atoi(char *str)  
{  
   if(NULL==str)  return -1;  
   
   int zhengfu; //0为负，1为正
   
   int result=0;  
  
   if((*str=='+')||(*str=='-'))  
   {  
          if(*str=='-')  
            zhengfu=0;
          else
          	zhengfu=1;
          *str++;  
   }
   
   while( *str != '\0')  
   {
           if('0'> *str || *str>'9')  
                  {
                   	printf("is not a num,error\n");
                   	return -1;
                  }  
           else  result = result*10+(*str++ - '0');
   }  
   return zhengfu?result:-result;  
}  