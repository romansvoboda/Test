/* 
 * File:   main.c
 * Author: jirka
 *
 * Created on October 19, 2014, 6:09 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * 
 Vagner te vidi.
 Ale ty jsi  jeho služebníèek
 Cokoliv sire Roumane.
 */

void mergeSort(uint64_t* array, uint64_t* aux, uint32_t left, uint32_t right);
void merge(uint64_t* array, uint64_t* aux, uint32_t left, uint32_t right);
int binarySearch(uint64_t distance,uint64_t *sortedArray,uint32_t count,uint64_t *position,int direction);
int binarySearchBoundery(uint64_t distance,uint64_t *sortedArray,uint32_t count,uint64_t *position,int direction);
int compareTo(uint64_t  distance,uint64_t  distance2);
uint32_t getCount(uint32_t posL,uint32_t posR,uint32_t count);

int main(int argc, char** argv) {
    
    unsigned long int N; /* N count trees,*/ 
    unsigned long long int tmp,M,combinations = 0;
    uint64_t i,j=0,positionR,positionLAgainst,positionRAgainst;
    uint64_t counterALarge,numberASmall,numberALarge,numberAAfter;
    uint64_t aCount,bCount,aAgainstL,bAgainstRLarge,bAgainstR,oddMultiply=1;
    uint64_t *sortedArray,*aux;
    uint64_t halfM,counterAAll,counterAAfter,counterASmall;


    scanf("%lu %llu", &N, &M);
    
    sortedArray =(uint64_t *) malloc(N * sizeof (uint64_t));

    if(M%2==1)
    {
        oddMultiply=4;
        M*=oddMultiply;
    }
    else
    {
        oddMultiply=2;
        M*=oddMultiply;
    }
    
    halfM = M / 2;
    
    for (i = 0; i < N; i++) {
        
        scanf("%llu", &tmp);
        tmp*=oddMultiply;
        sortedArray[i]=tmp;
    }
    
    aux = (uint64_t *) malloc(N * sizeof (uint64_t));
    mergeSort(sortedArray,aux,0,N-1);
    
    free(aux);
    
    /*for (i = 0; i < N; i++) {
        printf("Hod: %llu  \n", sortedArray[i]);
    }*/
    
    if(oddMultiply==2)/*even*/
    {
    
        for(i=0;i<N;i++)
        {
            if(sortedArray[i]<halfM)
            {
                if(binarySearch(sortedArray[i]+halfM,sortedArray,N,&positionLAgainst,0))
                {
                    
                    binarySearch(sortedArray[i]+halfM,sortedArray,N,&positionRAgainst,1);
                    binarySearch(sortedArray[i],sortedArray,N,&positionR,1);

                    aCount=positionR-i+1;
                    bCount=positionRAgainst-positionLAgainst+1;

                    combinations += aCount *(aCount-1) / 2 * bCount +
                                            aCount * bCount* (bCount-1) / 2 +
                                            aCount * bCount * (N-aCount-bCount);
                                           
                    i=positionR;
                }

            }
            else
                break;

        }
    }
    
    
    /*binarySearchBoundery(sortedArray[0]+halfM+1,sortedArray,N,&positionR,0);
    printf("POS OPL: %lu \n",positionR);
    binarySearchBoundery(sortedArray[1]+halfM-1,sortedArray,N,&positionR,1);
    printf("POS OPR: %lu \n",positionR);*/
    
    if (N>=3) 
    {
        binarySearchBoundery(sortedArray[0]+halfM+1,sortedArray,N,&aAgainstL,0);
        counterASmall=0;
        counterALarge=0;
        counterAAll=0;
        numberASmall=0;
        numberALarge=0;
        
        for(i=1;i<N;i++)
        {
            if(sortedArray[i]>=(sortedArray[0]+halfM))
                break;
            
            binarySearchBoundery(sortedArray[i]+halfM-1,sortedArray,N,&bAgainstR,1);
            
            counterAAll+=getCount(aAgainstL,bAgainstR,N);
            if(i==1)
            {
                counterASmall=counterAAll;
                binarySearchBoundery(sortedArray[i]+halfM+1,sortedArray,N,&bAgainstRLarge,1);
                counterALarge=getCount(aAgainstL,bAgainstRLarge,N);
            }
            
            if ((i==1) ||(sortedArray[i] == sortedArray[1]))
                numberASmall++;
            else
                numberALarge++;
          /*  printf("I: %lu DIS: %lu CNT: %lu \n", i,sortedArray[i],counterA);*/
        }
        combinations+=counterAAll;
        
        
        numberAAfter=numberASmall+numberALarge +1;
        
        for(i=1;i<N;i++)
        {
            if(sortedArray[i]>=(sortedArray[0]+halfM))
                break;
 
            counterAAfter=0;
            binarySearchBoundery(sortedArray[i]+halfM+1,sortedArray,N,&aAgainstL,0);
            
            for(j=numberAAfter;j<N;j++)
            {
                if(sortedArray[j]>=(sortedArray[i]+halfM))
                    break;

                /*osetrit pres M*/
                binarySearchBoundery(sortedArray[j]+halfM-1,sortedArray,N,&bAgainstR,1);
            
            counterAAfter+=getCount(aAgainstL,bAgainstR,N);
            numberAAfter++;
            
            }
            
            
            counterAAll = counterAAll-(numberASmall*counterASmall +
                               numberALarge*counterALarge) +counterAAfter;/* formula*/
            combinations+=counterAAll;
            
            if(i+1<N)
            {
                numberASmall=0;
                numberALarge=0;
                for(j=i+1;j<numberAAfter;j++)
                {
                    /*lze zrychlit binary*/
                    if ((j==i+1) || (sortedArray[j+3] == sortedArray[i+1]))
                        numberASmall++;
                    else
                        break;
                }
            
                numberALarge = numberAAfter-i-1 - numberASmall;
  
                binarySearchBoundery(sortedArray[i]+halfM+1,sortedArray,N,&aAgainstL,0);
                binarySearchBoundery(sortedArray[i+1]+halfM-1,sortedArray,N,&bAgainstR,1);
            
                counterASmall=getCount(aAgainstL,bAgainstR,N);
                binarySearchBoundery(sortedArray[i+1]+halfM+1,sortedArray,N,&bAgainstRLarge,1);
                counterALarge=getCount(aAgainstL,bAgainstRLarge,N);
            }
        }
        
    }
    printf("%llu\n", combinations);
    free(sortedArray);
    return (0);
}




void mergeSort(uint64_t* array, uint64_t* aux, uint32_t left, uint32_t right)
{
    uint32_t i,middleIndex;
    
    if (left == right) return;
    middleIndex = (left + right)/2;
    mergeSort(array, aux, left, middleIndex);
    mergeSort(array, aux, middleIndex + 1, right);
    merge(array, aux, left, right);
 
    for ( i= left; i <= right; i++) 
    {
        array[i] = aux[i];
    }
}   
 

void merge(uint64_t* array, uint64_t* aux, uint32_t left, uint32_t right)
{
    
    uint32_t middleIndex = (left + right)/2;
    uint32_t leftIndex = left;
    uint32_t rightIndex = middleIndex + 1;
    uint32_t auxIndex = left;
    while (leftIndex <= middleIndex && rightIndex <= right)
    {
        if (array[leftIndex] < array[rightIndex]) {
        aux[auxIndex] = array[leftIndex++];
        } 
        else {
        aux[auxIndex] = array[rightIndex++];
    }
    auxIndex++;
    }
    while (leftIndex <= middleIndex) 
    {
        aux[auxIndex] = array[leftIndex++];
        auxIndex++;
    }
    while (rightIndex <= right) 
    {
    aux[auxIndex] = array[rightIndex++];
    auxIndex++;
    }
} 
int binarySearch(uint64_t distance,uint64_t *sortedArray,uint32_t count,uint64_t *position,int direction){

  int left = 0;
  int right=count-1;
  uint32_t center;
  int res;

 while (left <= right) 
 {
       center = (left + right) / 2; 
       *position=center;
       res=compareTo(distance,sortedArray[center]);
       if (res>0)
       {
           left = center + 1;  
       }
       else if (res<0) 
           right = center - 1; 
       else
       {   
           if(direction==0)
           {
                if(center!=0)
                {
                    if(compareTo(distance,sortedArray[center-1])==0)
                        right = center - 1;
                    else
                        return 1;
                }
                else
                    return 1;
           }
           else
           {
                if(center==count-1)
                    return 1;    
             
                else
                {
                    if(compareTo(distance,sortedArray[center+1])==0)
                        left = center + 1;
                else
                   return 1;  
                }
           }
               
       }
   }
  
   return 0;    
}

int binarySearchBoundery(uint64_t distance,uint64_t *sortedArray,uint32_t count,uint64_t *position,int direction){

  int left = 0;
  int right=count-1;
  int center;
  int res;
  
  if(distance>sortedArray[count-1])
  {
      *position=count;
      return 0;
  }
  

 while (left <= right) {
       center = (left + right) / 2; 
       *position=center;
       res=compareTo(distance,sortedArray[center]);
       if (res>0)
       {
           left = center + 1;  
       }
       else if (res<0) 
           right = center - 1; 
       else
           return 1;
       
   }
  
   if(*position<count-1)
   { 
        if(res>0)
        {
            (*position)++;
            res=compareTo(distance,sortedArray[*position]);
        }
   }

  
  if(direction==0&&res>0)/*first from left*/
      (*position)=count;
  
  if(direction&&res<0)
      (*position)--;
      
      
   return 0;    
}

int compareTo(uint64_t  distance,uint64_t  distance2)
{
    if(distance<distance2)
        return -1;
    else if(distance>distance2)
        return 1;
    return 0; 

}

uint32_t getCount(uint32_t posL,uint32_t posR,uint32_t count)
{
    if(posL>=count)
        return 0;
    if(posR>=count)
        return posR-posL;
    
    return posL>posR?0:posR-posL+1;
}