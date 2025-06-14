#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H
#include"transaction.h"
#include"dynamic_template.h"
using namespace std;
class transactionHistory{
private:
Dynamic_array<transaction>trans;
public:
    transactionHistory():trans(){}
    transactionHistory(const Dynamic_array<transaction>& _trans):trans(_trans){}
    transactionHistory(const transactionHistory& other):trans(other.trans){}
    ~transactionHistory(){}

    void addTransaction(const transaction& _trans){
        trans.push(_trans);
    }
    int returnTransactionCount()const{
        return trans.size();
    }
    void removeTransaction(int index){
        trans.delete_at(index);
    }
    void displayAllTransactions()const{
        if(trans.size()==0){
            cout<<"No transactions found"<<endl;
            return;
        }
        for(int i=0;i<trans.size();i++){
            transaction t;
            t=trans[i];
            cout<<"Transaction No.["<<i+1<<"]: ";
            t.displayTransaction();
        }
    }
    const transaction& getTransactionByIndex(int index)const{
        if(index>0 && index<trans.size()){
            return trans[index];
        }
        //throw error here
    }
    void saveToFile(std::string filename) const {
    ofstream out(filename, ios::binary | ios::app);  
    if (!out) {
        cerr << "Couldn't open file" << endl;
        return;
    }
    
    int count = trans.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    for (int i = 0; i < count; i++) {
        const transaction& t = trans[i];
        
        int symbolLen = t.getSymbol().getlen();
        out.write(reinterpret_cast<const char*>(&symbolLen), sizeof(symbolLen));
        out.write(t.getSymbol().c_str(), symbolLen);
        
        int typeLen = t.getType().getlen();
        out.write(reinterpret_cast<const char*>(&typeLen), sizeof(typeLen));
        out.write(t.getType().c_str(), typeLen);
        
        double quantity = t.getQuantity();
        out.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
        
        double price = t.getPrice();
        out.write(reinterpret_cast<const char*>(&price), sizeof(price));
        
        Date d = t.getdate();
        out.write(reinterpret_cast<const char*>(&d), sizeof(d));
        
        Time tt = t.gettime();
        out.write(reinterpret_cast<const char*>(&tt), sizeof(tt));
    }
    out.close();  // Added explicit close
}
};
#endif //TRANSACTIONHISTORY_H 