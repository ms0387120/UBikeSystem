#include "UBikeSystemIMP.h"
#include "UBikeHashTableIMP.h"
#include "UBikeHeapIMP.h"
#include "PriceTableIMP.h"
#include <iostream>
using namespace std;

void UBikeSystemIMP::InitDistTable(std::string MapFile){
    priceTable.calcAllPairsShortestPath(MapFile);
}

void UBikeSystemIMP::NewBike(std::string classType, std::string license,int mile, std::string station){
    //new a Ubike
    UBike* ubptr=new UBike;
    ubptr->classType= classType;
    ubptr->license= license;
    ubptr->mileage= mile;
    ubptr->station= station;
    ubptr->isRented= false;
    ubptr->heapIndex= 0;
    //add to the hash table
    ubHashTable.addUBikePtr(ubptr);
    //add to the heap
    ubStations[station][classType].addUBikePtr(ubptr);
}

void UBikeSystemIMP::JunkIt(std::string license){
        //remove the pointer from the hash table
        UBike* ptr=ubHashTable.findUBikePtr(license, false);
        if(ptr==NULL) return;
        else if(ptr->isRented==true) return;
        else{//remove the pointer from the heap
			ubStations[ptr->station][ptr->classType].removeUBikePtr(ptr->heapIndex);
			ubHashTable.findUBikePtr(license, true);
		}
}

void UBikeSystemIMP::Rent(std::string classType, std::string station){
    if(ubStations[station][classType].isEmpty()) return;
    else{//find the min milage in the heap and turn in to Rent
		UBike* ptr= ubStations[station][classType].removeUBikePtr(1);
		ubStations[station]["Rented"].addUBikePtr(ptr);
		ptr->isRented=1;
	}
}

void UBikeSystemIMP::Return(std::string station, std::string license, int returnMile){
    //find
    UBike* ubptr=ubHashTable.findUBikePtr(license, false);
    if(ubptr==NULL)
        return;
    else if(ubptr->isRented==false)
        return;
    else{//calculate the rental and add it to net
		int mileDiff=returnMile-ubptr->mileage;
		net+=priceTable.calcPrice(mileDiff, ubptr->classType, ubptr->station, station);
		//cout << net << endl;
		//update the mileage & set ieRented to false
		ubptr->mileage=returnMile;
		ubptr->isRented=false;
		//change heap
		ubStations[ubptr->station]["Rented"].removeUBikePtr(ubptr->heapIndex);
		ubStations[ubptr->station][ubptr->classType].addUBikePtr(ubptr);
		//§ó·sstation??
		//ubptr->station=station;
	}
}

void UBikeSystemIMP::Trans(std::string station, std::string license){
    //find
    UBike* ubptr=ubHashTable.findUBikePtr(license, false);
    if(ubptr==NULL)
        return;
    else if(ubptr->isRented==true)
        return;
    else{
		ubStations[ubptr->station][ubptr->classType].removeUBikePtr(ubptr->heapIndex);
		ubStations[station][ubptr->classType].addUBikePtr(ubptr);
		ubptr->station=station;
	}
}

void UBikeSystemIMP::ShutDown(){
    for(int i=0; i<256; i++){
        for(auto iter=ubHashTable[i].begin(); iter!=ubHashTable[i].end(); iter++){
            delete *iter;
        }
    }
}
