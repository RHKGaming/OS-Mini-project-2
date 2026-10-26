#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "pstat.h"

int counter = 0;
int partBcount = 0;
int partCcount = 0;

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
  counter ++;
  return proc->pid;
}

int
sys_getpinfo(void)
{
 struct pstat *pInfo;
 
 if(argptr(0, (void *)&pInfo, sizeof(*pInfo)) < 0){
  return -1;
 }
 if(pInfo == NULL){
  return -1;
 }
 getpinfo(pInfo);
 return 0;
}

int
sys_firstpart(void)
{
  return counter;
}

int
sys_secondpart(void)
{
  return partBcount;
}

int
sys_thirdpart(void)
{
    return partCcount;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_myps(void)
{
 return myps();
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
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}
extern int partCcount;

int
sys_ThirdPart(void)
{
  return partCcount;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_settickets(void)
{
    int n;

    if(argint(0, &n) < 0)
        return -1;

    if(n < 10 || n > 200 || n % 10 != 0)
        return -1;

    return settickets(n);
}