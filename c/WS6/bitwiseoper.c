
#include <stdio.h> 
int main() 
{ 
   
    unsigned char a = 5, b = 9; 
   printf(" a = 5(00000101), b = 9(00001001)\n");
    printf(" The result is 00000001\n ");
    printf("a = %d, b = %d\n", a, b); 
    printf("  a&b = %d\n", a & b); 
  
  printf(" The result is 00001101 \n");
    
    printf("  a|b = %d\n", a | b); 
  
  printf(" The result is 00001100\n ");
    
    printf("a^b = %d\n", a ^ b); 
  
  printf(" The result is 11111010 \n ");
    
    printf("~a = %d\n", a = ~a); 
  
  printf(" /* The result is 00010010 */\n ");
    
    printf("b<<1 = %d\n", b << 1); 
  
  printf("  /* The result is 00000100 */ \n");
   
    printf("  b>>1 = %d\n", b >> 1); 
  
    return 0; 
} 
