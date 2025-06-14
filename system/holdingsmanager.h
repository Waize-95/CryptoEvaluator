//default: \033[0m
//green : \033[32m
//red : \033[31m
//yellow : \033[33m
//bold : \033[1m 


#ifndef HOLDINGSMANAGER_H
#define HOLDINGSMANAGER_H
#include<iostream>
#include<fstream>
#include"dynamic_template.h"
#include"holdings.h"
#include"Mystr.h"
using namespace std;
class holdingsManager{
private:
    Dynamic_array<holdings> hold;
public:
    holdingsManager():hold(){}
    holdingsManager(Dynamic_array<holdings>& _hold):hold(_hold){}
    holdingsManager(const holdingsManager& other):hold(other.hold){}
    ~holdingsManager(){}

    void addToHoldings(const holdings& h){
        hold.push(h);
    }
    void displayAllHoldings()const{
        if(hold.size()==0){
            cout<<"NO Holdings yet!"<<endl;
            return;
        }
        for(int i=0;i<hold.size();i++){
            cout<<"\033[32m Holding["<<i+1<<"]:\033[0m  ";
            hold[i].displayHolding();
        }
    }
    bool CheckCoinAvailabilityAndQuantity(cryptoCoin* coin,double quantity){
        for(int i=0;i<hold.size();i++){
            if(hold[i].getHoldCoin()==coin){
                if(hold[i].getQuantity()>=quantity){
                    return true;
                }
            }
        }
        return false;
    }
    void updateholdingsinmanager(cryptoCoin* coin,double _quantity,double _price){
        String Symbol=coin->getSymbol();
        for(int i=0;i<hold.size();i++){
            if(hold[i].getcoinsymbol()==Symbol){
                hold[i].updateHolding(_quantity,_price);
                return;
            }
        }
        holdings h1(coin,_quantity,_price);
        addToHoldings(h1);
    }
    void reduceholding(cryptoCoin* coin,double _quantity){
        String Symbol=coin->getSymbol();
        for(int i=0;i<hold.size();i++){
            if(hold[i].getcoinsymbol()==Symbol){
                hold[i].reduceHolding(_quantity);
                if(hold[i].getQuantity()==0){
                    hold.delete_at(i);
                }
                return;
            }
        }
    }
    double CheckHoldingQuantityByCoin(cryptoCoin* coin)const{
        for(int i=0;i<hold.size();i++){
            if(hold[i].getHoldCoin()==coin){
                return hold[i].getQuantity();
            }
        }
        return 0;
    }
    int getholdingsSize()const{
        return hold.size();
    }
    const holdings& getholdingbyIndex(int index)const{
        return hold[index];
    }
   void saveToFile(std::string filename) const {
    ofstream out(filename, ios::binary | ios::app);  // Added ios::app
    if (!out) {
        cerr << "Couldn't open file" << endl;
        return;
    }
    
    int holdingscount=hold.size();
        out.write(reinterpret_cast<char*>(&holdingscount),sizeof(holdingscount));
        for(auto& h: hold){
            String name=h.getHoldCoin()->getname();
            double quantity=h.getQuantity();
            double price=h.getHoldCoin()->getPrice();
            int len=name.getlen();
            out.write(reinterpret_cast<char*>(&len),sizeof(len));
            out.write(name.c_str(),len);
            out.write(reinterpret_cast<char*>(&quantity),sizeof(quantity));
            out.write(reinterpret_cast<char*>(&price),sizeof(price));
        }
    
    out.close();  // Added explicit close
}
};
#endif //HOLDINGSMANAGER_H

