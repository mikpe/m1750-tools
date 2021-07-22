#include <intrrpt.h>
#include "pthread_internals.h"


int
intwait_handler (int code)
{
  pthread_t p;
  int i;

  DISABLE_INTERRUPTS;

  /* find the thread which is waiting for this code */
  p = waitq.head;
  while (p && (! ((0x0001 << (15 - code)) & p->intwait_mask)) )
    p = p->next_in_primary_q;

  if (!p)
    return;

  /* disconnenct handlers we connected for this intwait */
  for (i = 0; i <= 15; i++)
    if ((0x0001 << (15 - i)) & p->intwait_mask)
      handler (i, INT_DFL);

  p->intwait_code = code;
  pthread_q_wakeup_thread (&waitq, p);

  ENABLE_INTERRUPTS;

  if (state_change) {
    state_change = FALSE;
    asm ("bex 1");
  }
}


int
intwait (unsigned set)
{
  /*
   * Block the current thread until any of the interrupts
   * in the given set occur.
   */
  pthread_t p = mac_pthread_self();
  int i;

  SET_KERNEL_FLAG;

  for (i = 0; i <= 15; i++)
    if ((0x0001 << (15 - i)) & set)
      handler (i, intwait_handler);

  p->intwait_mask = set;
  pthread_q_sleep (&waitq);

  CLEAR_KERNEL_FLAG;

  return p->intwait_code;
}
