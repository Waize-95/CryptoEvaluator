#ifndef HOLDINGS_H
#define HOLDINGS_H
#include"cryptocoin.h"
#include"Mystr.h"
using namespace std;
class holdings{
private:
    cryptoCoin* coin;
    double quantity;
    double averagePrice;
public:
    holdings():coin(nullptr),quantity(0.0),averagePrice(0.0){}
    holdings(cryptoCoin* _cn,double _quantity,double _averagePrice):
    coin(_cn),quantity(_quantity),averagePrice(_averagePrice){}
    holdings(const holdings& other):coin(other.coin),quantity
    (other.quantity),averagePrice(other.averagePrice){}
    ~holdings(){}

    cryptoCoin* getHoldCoin()const{
        return coin;
    }
    double getQuantity()const{
        return quantity;
    }
    double getaveragePrice()const{
        return averagePrice;
    }
    void updateHolding(double newQty,double price){
        //(newQty*price) this expression is for the new coin that we are buying
        //(quantity+averagePrice) this expression is for what we have already bought
        //example we may buy some BTC when it is 99K $ and we may buy some later
        double totalcost=(newQty*price)+(quantity*averagePrice);
        quantity=quantity+newQty;
        //may use later for profit/loss
        averagePrice=totalcost/quantity;
    }
    void reduceHolding(double sellQty){
        if(quantity>=sellQty){
            quantity=quantity-sellQty;
        }
        if(quantity==0){
            averagePrice=0;
        }
    }
    void displayHolding()const{
        if(coin){
            coin->displayCoinInfo();
            cout<<" Quantity: "<<quantity<<" Worth: $"<<coin->getPrice()*quantity<<" averagePrice: $"<<averagePrice<<endl;;
        }
    }
    const String getcoinsymbol()const{
        return coin->getSymbol();
    }
};
#endif //HOLDINGS_H