#ifndef PriceTableIMP_h
#define PriceTableIMP_h

#include "readonly/PriceTableADT.h"

class PriceTableIMP : public PriceTableADT
{
public:
    void calcAllPairsShortestPath(std::string mapFile);
	int calcPrice(int mileageDiff, std::string bClass, std::string from, std::string toStation);
};

#endif
