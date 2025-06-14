#ifndef BALANCEMANAGER_H
#define BALANCEMANAGER_H
class balanceManager{
private:
    double balance;
public:
    balanceManager():balance(0.0){}
    balanceManager(double _balance):balance(_balance){}
    balanceManager(const balanceManager& other):balance(other.balance){}
    ~balanceManager(){}

    double getBalance()const{
        return balance;
    }
    void setBalance(double money){
        balance=money;
    }
    void updateBalance(double money){
        balance=balance+money;
    }
    bool reduceBalance(double money){
        if(balance>=money){
            balance=balance-money;
            return true;
        }
        return false;
    }
};
#endif //BALANCEMANAGER_H