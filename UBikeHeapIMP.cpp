#include "UBikeHeapIMP.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

void UBikeHeapIMP::addUBikePtr(UBike* ubptr)
{
	int currentNode= ++number;
	while(currentNode !=1 && (*this)[currentNode/2]->mileage > ubptr->mileage){
		(*this)[currentNode]= (*this)[currentNode/2];
		(*this)[currentNode]->heapIndex= currentNode;
		currentNode/=2;
	}
	(*this)[currentNode]= ubptr;
	ubptr->heapIndex= currentNode;
}
UBike* UBikeHeapIMP::removeUBikePtr(int heapIndex)
{
	if(number==0 || heapIndex>number) return NULL;
	UBike* lastE= (*this)[number--];
	UBike* ans= (*this)[heapIndex];
	
	int currentNode= heapIndex;
	int child= 2*currentNode;
	while(child<=number){
		if(child < number && (*this)[child]->mileage > (*this)[child+1]->mileage) child++;
		if(lastE->mileage <= (*this)[child]->mileage) break;
		
		(*this)[currentNode]= (*this)[child];
		(*this)[child]->heapIndex= currentNode;
		currentNode= child;
		child*=2;
	}
	(*this)[currentNode]= lastE;
	(*this)[currentNode]->heapIndex= currentNode;
	return ans;
}
