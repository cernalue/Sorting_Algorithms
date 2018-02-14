#include "declare.h"

int main(int argc, char **argv)
{
unsigned int N_ofelements;
unsigned int operations;
unsigned int ID0 = 0;
unsigned int ID1 = 0;
unsigned int IDf = 0;
unsigned int IDff = 0;
double *arr;

N_ofelements = atoi( argv[2] );

ID0 = allocate(&arr, N_ofelements);
printf("\n\nAllocation succesfull.");
ID1 = src_File_manage(argv, arr, N_ofelements);
printf("\n\nFILE manage succesfull.");
IDf = merge_sort(arr, N_ofelements);
printf("\nMerge sort succesfull.");
printf("\nWriting sorted array in new file: 'sorted.txt'");
IDff = dst_File_manage(arr, N_ofelements);
printf("\nsorted array succesfully written in 'sorted.txt'\n\n");

free(arr);
return(6);
}

unsigned int allocate(double **array, unsigned int N_ofelements)
{
*array = malloc( N_ofelements * sizeof(double) );
if(*array == NULL)
  {
  printf("\n\nError during memory allocation\n\n"\
  "in 'allocation()' function.\n\n");
  }
return(0);
}

unsigned int src_File_manage(char **src, double *dst, unsigned int N_ofelements)
{
unsigned int i;
FILE *sc;
sc = fopen(src[1], "r");

if(sc == NULL)
  {  
  printf("\n\nError opening sorting file\n"\
  "in 'src_File_manage()'.\n\n");
  exit(1);
  }

for(i = 0; i < N_ofelements; i++)
  {
  fscanf(sc, "%lf\n", &dst[i] );
  }

fclose(sc);
return(1);
}

unsigned int dst_File_manage(double *dst, unsigned int N_ofelements)
{
unsigned int i;
FILE *dt;
dt = fopen("sorted.txt", "w+");

if(dt == NULL)
  {
  printf("\n\nError opening or creating 'sorted.txt' file\n"\
  "in 'dst_File_manage()'.\n\n");
  exit(7);
  }

for(i = 0; i < N_ofelements; i++)
  {
  fprintf(dt, "%lf\n", dst[i]);
  }
return(7);
}

unsigned int copy_arr(double *src, double *dst, unsigned int N_ofelements)
{
unsigned int i;
for(i = 0; i < N_ofelements; i++)
  {
  dst[i] = src[i];
  }
return(2);
}

unsigned int merge_sort(double *arr, unsigned int N_ofelements)
{
unsigned int ID2 = 0;
unsigned int ID3 = 0;
unsigned int ID5 = 0;
double *buffer;

ID2 = allocate(&buffer, N_ofelements);
printf("\n\nAllocation succesfull.");
ID3 = copy_arr(arr, buffer, N_ofelements);
printf("\n\nCopy of arr succesfull.", ID3);
ID5 = split_merge_sorted(buffer, arr, 0, N_ofelements-1);
printf("\n\nSplit merge sorted success.", ID5);

free(buffer);
return(5);
}

unsigned int split_merge_sorted(double *src, double *dst,\
                                unsigned int firstindex, unsigned int lastindex)
{
unsigned int op = 0;
unsigned int ID4 = 0;
unsigned int middleindex;

if(lastindex - firstindex < 1)
{
return(0);
}

middleindex = (firstindex + lastindex) / 2;

op += split_merge_sorted(dst, src, firstindex, middleindex);
op += split_merge_sorted(dst, src, middleindex+1, lastindex);
op += merge_sorted(src, dst, firstindex, middleindex, lastindex);

return(6);
}

unsigned int merge_sorted(double *src, double *dst,\
                          unsigned int firstindex, unsigned int middleindex,\
                          unsigned int lastindex)
{
unsigned int ID7 = 0;
unsigned int lo_srcindex, hi_srcindex, dstindex;

lo_srcindex = firstindex;
hi_srcindex = middleindex + 1;

for(dstindex = firstindex; dstindex <= lastindex; dstindex++)
  {
  if(lo_srcindex <= middleindex) /* Numbers remain in the lower array part */
    {
    if(hi_srcindex > lastindex) /* No numbers reamin in the higher array part */
      {
      dst[dstindex] = src[lo_srcindex];
      lo_srcindex++;
      }
    else /* Numbers remain in the higher array part */
      {
      if(src[lo_srcindex] < src[hi_srcindex])
        {
        dst[dstindex] = src[lo_srcindex];
        lo_srcindex++;
        }
      else 
        {
        dst[dstindex] = src[hi_srcindex];
        hi_srcindex++;
        }
      } 
    }   
  else /* No numbers remain in the lower array part */
    {
    dst[dstindex] = src[hi_srcindex];
    hi_srcindex++;
    }
  ID7++;
  }
return(ID7++);
}
