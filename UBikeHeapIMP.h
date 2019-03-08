#ifndef UBikeHeapIMP_h
#define UBikeHeapIMP_h

#include "readonly/UBikeHeapADT.h"

class UBikeHeapIMP : public UBikeHeapADT
{
public:
    void addUBikePtr(UBike* ubptr);
	UBike* removeUBikePtr(int heapIndex);
};

#endif
