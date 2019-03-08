#ifndef UBikeHashTableIMP_h
#define UBikeHashTableIMP_h

#include "readonly/UBikeHashTableADT.h"

class UBikeHashTableIMP : public UBikeHashTableADT
{
public:
    void addUBikePtr(UBike* ubptr);
	UBike* findUBikePtr(std::string license, bool toRemove);
};

#endif
