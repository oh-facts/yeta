#include "gen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   int c = add_int_(5, 6);

   printf("%d \n", c);

   array_int_ myarray;
   init_array_int_(&myarray,10);

   for(int i = 0; i < myarray.max_size; i ++)
   {
     printf("%d\n",myarray.data[i]);
   }
   
   return 0;
}
