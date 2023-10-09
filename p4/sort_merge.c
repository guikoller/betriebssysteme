#include "sort_merge.h"

static void swap(int *x, int *y);

static void swap(int *x, int *y)
{
   int h = *x;
   *x = *y;
   *y = h;
}


void quickSort(int *seq, int left, int right)
{
  if (right > left)
  {
    int li=left-1, re=right, pivot=right;
    
    for(;;) {
       while(seq[++li] < seq[pivot]);
       while(seq[pivot] < seq[--re] && li < re);
       if(li >= re) 
         break;
       swap(seq+li, seq+re);    // Vertauschung
     }
     swap(seq+li, seq+pivot);  // Positionieren des Pivoelements
     
     if (left < li-1)
       quickSort(seq, left, li-1);  // Sortieren linke Teilliste
     if( re+1 < right)
       quickSort(seq, re+1, right); // Sortieren rechte Teilliste
  }
}

void merge(int *seq, int *seq_sort, int len)
{
  int l=0, m=len/2, i=0;
  
  while (l < len/2 && m < len)
    if (seq[l] < seq[m]) 
       seq_sort[i++] = seq[l++];
    else
       seq_sort[i++] = seq[m++];
  while (l < len/2)
     seq_sort[i++] = seq[l++];
  while (m < len)
     seq_sort[i++] = seq[m++];
}
