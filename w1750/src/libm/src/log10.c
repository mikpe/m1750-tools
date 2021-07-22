/*
 * ANSI Standard C: 7.5.4.5
 * 
 * #include <math.h>
 * double log10 (double x);
 * 
 * Copyright (c) 1997, Chris Nettleton Software
 *
 * The contents of this file are based on the algorithms and 
 * coefficients given in "Software Manual for the Elementry Functions" 
 * by William J. Cody, Jr. and William Waite, Prentice_Hall, 1980. 
 *
 * $Log: log10.c,v $
 * Revision 1.1  1997/03/17 17:15:43  nettleto
 * Initial revision
 *
 */

#include <math.h>

double
log10 (double x)
{
  const double log_base_10_of_e = 0.43429448190325182765;

  return log_base_10_of_e * log (x);
}
/*log10*/


