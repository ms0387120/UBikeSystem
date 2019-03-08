#include "PriceTableIMP.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

std::map< std::string, int > oriPriceTable =
{
    {"Electric", 40},
    {"Lady", 30},
    {"Road", 20},
    {"Hybrid", 25}
};
std::map< std::string, int > dscntPriceTable =
{
    {"Electric", 25},
    {"Lady", 20},
    {"Road", 10},
    {"Hybrid", 15}
};

void PriceTableIMP::calcAllPairsShortestPath(std::string mapFile)
{
	int i,j,k,x;
	string a,b;
	
	//initialize
	for(i=0;i<12;i++){
		for(j=0;j<12;j++){
			if(i==j) this->distTable[StationNames[i]][StationNames[j]]= 0;
			else this->distTable[StationNames[i]][StationNames[j]]= 99999;
		}
	}
	
	//read 
	ifstream ifs(mapFile);
	while(ifs >> a >> b >> x){
		this->distTable[a][b]= x;
		this->distTable[b][a]= x;
	}
	
	//calculate shortest path
	for(k=0;k<12;k++){
		for(i=0;i<12;i++){
			for(j=0;j<12;j++){
				if(this->distTable[StationNames[i]][StationNames[j]] > this->distTable[StationNames[i]][StationNames[k]]+this->distTable[StationNames[k]][StationNames[j]]){
					this->distTable[StationNames[i]][StationNames[j]]= this->distTable[StationNames[i]][StationNames[k]]+this->distTable[StationNames[k]][StationNames[j]];
				}
			}
		}
	}
	
}
int PriceTableIMP::calcPrice(int mileageDiff, std::string bClass, std::string from, std::string toStation)
{
	int ans=0;
    if(mileageDiff <= this->distTable[from][toStation]){
        ans= dscntPriceTable.find(bClass)->second*mileageDiff;
    }
    else{
        ans= oriPriceTable.find(bClass)->second*mileageDiff;
    }
	return ans;
}