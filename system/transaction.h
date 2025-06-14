#ifndef TRANSACTION_H
#define TRANSACTION_H
#include<iostream>
#include<ctime>
#include"Mystr.h"
#include"cryptocoin.h"
using namespace std;
struct Date {
    int day, month, year;
    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    void setToCurrentDate() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        day = localTime->tm_mday;
        month = localTime->tm_mon + 1;
        year = localTime->tm_year + 1900;
    }
};
struct Time {
    int hour, minute, second;
    Time() : hour(0), minute(0), second(0) {}
    Time(int h, int m, int s) : hour(h), minute(m), second(s) {}

    void setToCurrentTime() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        hour = localTime->tm_hour;
        minute = localTime->tm_min;
        second = localTime->tm_sec;
    }
};

class transaction{
private:
    cryptoCoin* coins;
    String Symbol;
    String type;
    double quantity;
    double price;
    Date date;
    Time time;
public:
    transaction():coins(nullptr),Symbol("Unknown"),type("Unknown"),quantity(0.0),price(0.0),date(),time(){}
    transaction(cryptoCoin* _cn,const String& _sym,const String& _type,double _quantity,double _price,
    const Date& _date,const Time& _time):coins(_cn),Symbol(_sym),type(_type),quantity(_quantity),
    price(_price),date(_date),time(_time){}
    transaction(const transaction& other):coins(other.coins),Symbol(other.Symbol),type(other.type),
    quantity(other.quantity),price(other.price),date(other.date),time(other.time){}
    ~transaction(){}
    void displayTransaction() const {
        cout << "Transaction [" << type << "] - Coin: " << Symbol
             << ", Quantity: " << quantity << ", Price: $" << price
             << ", Date: " << date.day << "/" << date.month << "/" << date.year
             << ", Time: " << time.hour << ":" << time.minute << ":" << time.second << endl;
    }
    cryptoCoin* getCoin() const { return coins; }
    String getSymbol() const { return Symbol; }
    double getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    String getType() const { return type; }
    const Date& getdate()const{
        return date;
    }

    const Time& gettime()const{
        return time;
    }
    
};
#endif //TRANSACTION_H