#include "UBikeHashTableIMP.h"
#include <iostream>
#include <string>
#include <cctype>
#include <forward_list>
using namespace std;


void UBikeHashTableIMP::addUBikePtr(UBike* ubptr)
{
	string str;
	int i,total=0,binary[30]={},addr=0;
	str= ubptr->license;
	
	for(i=0;i<5;i++){
		if(isdigit(str[i])){
			total= total*29+(str[i]-48); //ASCII: 0->48 && 9->57
		}
		else{ //isupper
			total= total*29+(str[i]-55); //ASCII: A->65 && Z->90 || A->10 && Z->35
		}
	}
	
	// convert binary -> get 6th~13th bits (8bits) -> convert address into decimal
	for(i=0;i<30;i++){//轉二進位
        binary[i]= total%2;
        total= total/2;
    }
	for(i=12;i>=5;i--){ //取address & 轉十進位
		addr= addr*2+binary[i];
	}
	
	(*this)[addr].push_front(ubptr); //insert to the front
	
}
UBike* UBikeHashTableIMP::findUBikePtr(std::string license, bool toRemove)
{
	string str;
	int i,total=0,binary[30]={},addr=0;
	str= license;
	
	for(i=0;i<5;i++){
		if(isdigit(str[i])){
			total= total*29+(str[i]-48); //ASCII: 0->48 && 9->57
		}
		else{ //isupper
			total= total*29+(str[i]-55); //ASCII: A->65 && Z->90 || A->10 && Z->35
		}
	}
	
	// convert binary -> get 6th~13th bits (8bits) -> convert address into decimal
	for(i=0;i<30;i++){//轉二進位
        binary[i]= total%2;
        total= total/2;
    }
	for(i=12;i>=5;i--){ //轉十進位
		addr= addr*2+binary[i];
	}
	
	// find
	if ((*this)[addr].empty()) return NULL; //empty
	
	for(auto iter=(*this)[addr].begin();iter!=(*this)[addr].end();iter++){
		if((*iter)->license==license){
			if(toRemove){
				((*this)[addr]).remove(*iter);
				return NULL;
			}
			else return *iter;
		}
	}
	return NULL;
}
