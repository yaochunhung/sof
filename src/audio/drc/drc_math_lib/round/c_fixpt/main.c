/*
 * File: main.c
 *
 * Author :Shriram Shastry
 * Copyright (c) 2016, Intel Corporation All rights reserved.
 */


/* Include Files */
#include "main.h"
#include "drc_round.h"

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  //main_drc_round_fixpt();
  //main_init_struc_fixpt();
  unsigned int x;
  unsigned char y;
  x = init_struc_fixpt();
  y = drc_round_fixpt(x);

  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
