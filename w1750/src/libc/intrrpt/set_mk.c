/*
 *
 * $Log: set_mk.c,v $
 * Revision 1.1  1997/07/17 18:43:28  nettleto
 * Initial revision
 *
 */

struct linkage_area
  {
    unsigned short mk;  /* Interrupt mask */
    unsigned short sw;  /* Status word */
    void *ic;           /* Instruction counter */
  };
struct service_area
  {
    unsigned short mk;        /* Interrupt mask */
    const unsigned short sw;  /* Status word */
    const void *ic;           /* Instruction counter */
  };
extern const struct
  {
    struct linkage_area *linkage_area_ptr;
    struct service_area *service_area_ptr;
  }
ivt [16];



/*
 * Function to set the interrupt mask register, and the mk component of
 * each interrupt service area. To support nested interrupts each
 * interrupt service area mk must be set to allow interrupts of a higher
 * priority and no others.
 */
unsigned short
set_mk (unsigned short mk)
{
  int i;
  unsigned old_mk;

  /* Disable all interupts while we're in an inconsistent state.  */
  asm ("xio    r0,dsbl");

  /* Set the level 0 mask to all zeros.  */
  ivt [0].service_area_ptr->mk = 0x0000;

  /* Set the masks for levels 1 to 15 so that each level may only be
     interrupted by a lower numbered level.  */
  for (i = 1; i <= 15; i++)
    {
      unsigned short mask = 0xffff << (16 - i);

      ivt [i].service_area_ptr->mk = mask & mk;
    }

  /* Get the old mask then set the new one.  */
  asm ("xio    %0,rmk": "=r" (old_mk));
  asm ("xio    %0,smk" :: "r" (mk));

  /* And finally enable interrupts again.  */
  asm ("xio    r0,enbl");

  return old_mk;
}

