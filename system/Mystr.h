#ifndef STRING_H
#define STRING_H
#include<iostream>
using namespace std;

class String{
    private:
        int len;
        int cap;
        char *Cs;
        public:
        static int STRLEN(const char*);
        String();
        String(const char* _cs);
        String(const String& obj);
        String(const int num);
        ~String();

        String& operator=(const String& str);
        friend String operator+(const String& str1,const String& str2);
        friend ostream& operator<<(ostream& strm,const String& str);
        friend istream& operator>>(istream& strm,String& str);
        friend istream& operator>>(std::istream& in, String& str);
        char& operator[](const int index);
        const char& operator[](const int num) const;

        char* itos(int num);
        int stoi();

        void print();
        void setCs(const char* _cs);
        void clear();
        void setChar(int i,char _c);
        bool is_greater(const String& str);
        bool is_smaller(const String& str);
        String& trim();
        static String trim(const char* _cs);
        bool is_equal(const String& str)const;
        bool operator==(const String& other)const;
        bool operator<(const String& other);
        // bool operator!=(const String& other) const {
        //     return !(*this == other);
        // }
        // bool operator<=(const String& other) const {
        //     return *this < other || *this == other;
        // }
        
        // bool operator>(const String& other) const {
        //     return other < *this;
        // }
        
        // bool operator>=(const String& other) const {
        //     return !(*this < other);
        // }
        bool compare(const String& str)const;
        String concat(const String& str)const;
        String& append(const String& str);
        void insert_at(int i, char ch);
        void insert_sub(int i, const String str);
        int* all_sub_strings(const char* sub, int& count);
        int find_first(char ch);
        int find_first_substring(const char* sub);
        int find_last(char ch);
        int find_last_substring(const char* sub);
        int* find_all(char ch,int& count);
        int* find_all_substrings(const char* sub, int& count);
        String* split(char delim,int &count) const;

        void remove_at(int i);
        void remove_first(char ch);
        void remove_last(char ch);
        void remove_all(char ch);
        String& ToUPPER();
        String& ToLower();
        // String ToLower()const;
        const char* c_str() const;
        int getlen()const;

};

#endif //STRING_H