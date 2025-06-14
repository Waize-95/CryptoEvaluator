#ifndef CONFIGREADER_H
#define CONFIGREADER_H
#include<iostream>
#include<fstream>
#include<sstream>
#include"Mystr.h"
using namespace std;
class configReader{
private:
    double price;
    double marketcap;
    double trend;
    double risk;
public:
    configReader():price(0.0),marketcap(0.0),trend(0.0),risk(0.0){}
    void load(const std::string& filename){
        ifstream reader(filename);
        if(!reader){
            cerr<<"Couldn't open file"<<endl;
        }
        std::string line;
        while(getline(reader,line)){
            istringstream read(line);
            string key;
            double value;
            if(read>>key)
            read.ignore(100,'=');
            if(read>>value){
                if(key=="price"){price=value;}
                else if(key=="marketcap"){marketcap=value;}
                else if(key=="trend"){trend=value;}
                else if(key=="risk"){risk=value;}
            }
        }
        reader.close();
    }
    double getpriceThreshold()const{
        return price;
    }
    double getmarketcapThrehold()const{
        return marketcap;
    }
    double gettrendThreshold()const{
        return trend;
    }
    double getriskThreshold()const{
        return risk;
    }
};
#endif //CONFIGREADER_H