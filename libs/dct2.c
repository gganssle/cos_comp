/* Copyright (c) Colorado School of Mines, 2011.*/
/* All rights reserved.                       */


/*********************** self documentation **********************/

/*****************************************************************************
DCT2 - 2D Discrete Cosine Transform Routines

dctiv_2 - in-place IV-type 2D-DCT
dct_2   - in-place 2D-DCT

*****************************************************************************
Function Prototypes:

void dctiv_2(float **x, int n1, int n2, float **c1, float **c2);
void dct_2(float **x, int n1, int n2, float **c1, float **c2, int type);

*****************************************************************************
dctiv_2:
Input:
x        array[][] of the signal before and after transform
n1       length of the signal along the 1st dimension
n2       length of the signal along the 2nd dimension
c1       table for the 1st dimension
c2       table for the 2nd dimension


dct_2:
Input:
x        array[][] of the signal before and after transform
n1       length of the signal along the 1st dimension
n2       length of the signal along the 2nd dimension
c1       table for the 1st dimension
c2       table for the 2nd dimension
type     0 for forward and 1 for inverse transform
******************************************************************************
Author:		Tong Chen, 03/16/95
Modifier:       Tong Chen, 06/01/95, use pre-generated table
*****************************************************************************/

#include "../includes/comp.h"


/* function used internally */
static void dctiv_row(float **x, int n1, int n2, float **c);
static void dct_row(float **x, int n1, int n2, float **c, int type);


void dctiv_2(float **x, int n1, int n2, float **c1, float **c2)
/*****************************************************************************
 in place IV-type 2D-DCT
******************************************************************************
x        array[][] of the signal before and after transform
n1       length of the signal along the 1st dimension
n2       length of the signal along the 2nd dimension
c1       table for the 1st dimension
c2       table for the 2nd dimension
******************************************************************************
Author:		Tong Chen, 03/16/95
Modifier:       Tong Chen, 06/01/95, use pre-generated table
*****************************************************************************/
{
   int i;
   
   /* first along the faster dimension */
   for(i=0; i<n2; i++)
      dctiv(x[i], n1, c1);

   /* then along the slower dimension */
   dctiv_row(x, n1, n2, c2);
}


void dct_2(float **x, int n1, int n2, float **c1, float **c2, int type)
/*****************************************************************************
 in place 2D-DCT
******************************************************************************
x        array[][] of the signal before and after transform
n1       length of the signal along the 1st dimension
n2       length of the signal along the 2nd dimension
c1       table for the 1st dimension
c2       table for the 2nd dimension
type     0 for forward and 1 for inverse transform
*****************************************************************************/
{
   int i;
   
   /* first along the faster dimension */
   for(i=0; i<n2; i++)
      dct(x[i], n1, c1, type);

   /* then along the slower dimension */
   dct_row(x, n1, n2, c2, type);
}


static void dctiv_row(float **x, int n1, int n2, float **c)
/*****************************************************************************
 in place IV-type DCT along the rows of a 2D array
******************************************************************************
x        array[][] of the signal before and after transform
n1       length of the signal along the 1st dimension
n2       length of the signal along the 2nd dimension
c2       table for the 2nd dimension
*****************************************************************************
Notes:   Internal subroutine to dctiv_2 
*****************************************************************************
Author:		Tong Chen, 03/16/95
*****************************************************************************/
{
	float **tmp;
	int i, j, k;

	tmp = alloc2float(n1, n2);
	
	/* forward transform */
	for(i=0; i<n2; i++){
	      for(k=0; k<n1; k++) tmp[i][k] = 0.;

	    for(j=0; j<n2; j++)
	       for(k=0; k<n1; k++)
		  tmp[i][k] += x[j][k]*c[i][j];
       }

       for(i=0; i<n2; i++)	
	  for(k=0; k<n1; k++)
	     x[i][k] = tmp[i][k];

       /* free the spaces */
       free2float(tmp);
}




static void dct_row(float **x, int n1, int n2, float **c, int type)
/*****************************************************************************
 in place DCT along the rows of a 2D array
******************************************************************************
x        array[][] of the signal before and after transform
n1       length of the signal along the 1st dimension
n2       length of the signal along the 2nd dimension
c2       table for the 2nd dimension
type     0 for forward and 1 for inverse transform
*****************************************************************************
Notes:   Internal subroutine to dct_2 
*****************************************************************************
Author:		Tong Chen, 03/16/95
*****************************************************************************/
{
	float **tmp;
	int i, j, k;

	tmp = alloc2float(n1, n2);
	
	/* forward transform */
	if(!type)
	{
	   
	   for(i=0; i<n2; i++){
		 for(k=0; k<n1; k++) tmp[i][k] = 0.;

		 for(j=0; j<n2; j++)
		    for(k=0; k<n1; k++)
		       tmp[i][k] += x[j][k]*c[i][j];
	      }
	}
	/* inverse transform */
	else
	{
	   
	   for(i=0; i<n2; i++)
		 for(k=0; k<n1; k++) tmp[i][k] = 0.;

	   for(j=0; j<n2; j++)
	      for(i=0; i<n2; i++)
		 for(k=0; k<n1; k++)
		    tmp[i][k] += x[j][k]*c[j][i];
	}
	
       for(i=0; i<n2; i++)	
	  for(k=0; k<n1; k++)
	     x[i][k] = tmp[i][k];

       /* free the spaces */
       free2float(tmp);
}
