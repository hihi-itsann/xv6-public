#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->vlimit;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//change protection bit to read-only
int
sys_mprotect(void)
{
  void *addr;
  int len;

  //if addr points to a region that is not currently a part of the address space
  if(argptr(0,(char**)&addr,sizeof(void*))<0 || argint(1,&len)<0){
    return -1;
  }

  //if page is not aligned
  if((uint)addr % PGSIZE != 0){
    return -1;
  }

  //if length is less or equal to zero
  if(len<=0){
    return -1;
  }

  return mprotect(addr, len);
}

//change protection bit to read-and-write
int
sys_munprotect(void)
{
  void* addr;
  int len;

  //if addr points to a region that is not currently a part of the address space
  if(argptr(0,(char**)&addr,sizeof(void*))<0  || argint(1,&len)<0){
    return -1;
  }

  //if page is not aligned
  if((uint)addr % PGSIZE != 0){
    return -1;
  }

  //if length is less or equal to zero
  if(len<=0){
    return -1;
  }
  
  return munprotect(addr, len);
}
