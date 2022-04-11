#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
    
 //passing command line arguments
    
int main(int argc, char *argv[])
{
  
  //integer that is equal to page size
  int* align = (int*)4096;
  //integer that is not aligned with page size
  int* notAlign = (int*)4097;

  //When page is not aligned 
  //mprotect fails and returns -1
  int temp = mprotect((void *)notAlign,sizeof(notAlign));
  if(temp<0){
    printf(1,"mProtect() failed.\n");
  }
  
  //mprotect successes
  int i = mprotect((void *)align,1);
  if(i==0){
     printf(1,"mprotect() success.\n");
  }

  //munprotect successes
  int munprotectTest = munprotect((void *)align,1);
  if(munprotectTest==0){
    printf(1,"munprotect() success.\n");
  }

  //when length is less than or equal to 0
  //mprotect fails and returns -1
  temp = mprotect((void *)align,0);
  if(temp<0){
    printf(1,"mprotect() failed.\n");
  }
  //align should be able to be changed since mprotect() failed
  //change value of align to check if it can be changed
  
  exit();
}
