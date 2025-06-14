#include<iostream>
#include"Mystr.h"
using namespace std;

int String::STRLEN(const char* string) {
	int c = 0;
	if (string == nullptr) {
		return 0;
	}
	while (string[c] != '\0') {
		c++;
	}
	return c;
}
String::String() : Cs(nullptr), len(0), cap(0) {
	// cout << "String default constructor" << endl;
};
String::String(const char* _cs) {
	// cout << "String Parameterized constructor" << endl;
	setCs(_cs);
}
String::String(const String& other) :len(other.len), cap(other.cap), Cs(new char[len + 1]) {
	// cout << "Copy String constructor" << endl;
	for (int i = 0; i < this->len; i++) {
		this->Cs[i] = other.Cs[i];
	}
	this->Cs[len] = '\0';
}
String::String(const int num) {
	Cs = itos(num);
	this->len = STRLEN(Cs);
	cap = len;
}
String::~String() {
	// cout << "String destructor" << endl;
	delete[] Cs;
	Cs = nullptr;
}
String& String::operator=(const String& other) {
	// cout << "String overloaded = opertor" << endl;
	this->len = other.len;
	this->cap = other.cap;
	delete[] Cs;
	this->Cs = new char[len + 1];
	for (int i = 0; i < len; i++) {
		this->Cs[i] = other.Cs[i];
	}
	this->Cs[len] = '\0';
	return *this;
}
String operator+(const String& str1, const String& str2) {
	String res;
	res.len = str1.len + str2.len;
	res.len = res.len + 1;
	res.cap = res.len;
	res.Cs = new char[res.len];
	int index = 0;
	for (int i = 0; i < str1.len; i++) {
		res.Cs[index] = str1.Cs[i];
		index++;
	}
	res.Cs[index] = ' ';
	index++;
	for (int i = 0; i < str2.len; i++) {
		res.Cs[index] = str2.Cs[i];
		index++;
	}
	res.Cs[index] = '\0';
	return res;
}
ostream& operator<<(ostream& strm, const String& str) {
	for (int i = 0; i < str.len &&str.Cs[i]!='\0' ; i++) {
		strm << str.Cs[i];
	}
	return strm;
}
istream& operator>>(istream& strm, String& str) {
	char temp[100];
	strm.getline(temp, 100);
	String tempStr(temp);
	str = tempStr;
	return strm;
}

char& String::operator[] (const int index) {
	if (index >= 0 && index < this->len) {
		return Cs[index];
	}
	return Cs[0];
}
const char& String::operator[] (const int num) const {
	if (num >= 0 && num < this->len) {
		return Cs[num];
	}
	return Cs[0];
}
String* String::split(char delim, int &count) const {
    // First pass: count how many pieces we’ll get.
    count = 1;
    for (int i = 0; i < len; ++i) {
        if (Cs[i] == delim) {
            ++count;
        }
    }

    // Allocate an array of Strings to hold each piece.
    String* parts = new String[count];

    int start = 0;    // start index of current piece
    int partIdx = 0;  // which part we're filling

    // Second pass: extract each substring
    for (int i = 0; i < len; ++i) {
        if (Cs[i] == delim) {
            int pieceLen = i - start;
            // copy characters into a temporary C-string
            char* buffer = new char[pieceLen + 1];
            for (int j = 0; j < pieceLen; ++j) {
                buffer[j] = Cs[start + j];
            }
            buffer[pieceLen] = '\0';
            // construct a String from it
            parts[partIdx++] = String(buffer);
            delete[] buffer;
            start = i + 1;
        }
    }

    // handle the final piece after the last delimiter
    int pieceLen = len - start;
    char* buffer = new char[pieceLen + 1];
    for (int j = 0; j < pieceLen; ++j) {
        buffer[j] = Cs[start + j];
    }
    buffer[pieceLen] = '\0';
    parts[partIdx++] = String(buffer);
    delete[] buffer;

    return parts;
}

char* String::itos(int num) {
	int temp = 0;
	char* array = new char[10];
	int index = 0;
	while (num != 0) {
		temp = num % 10;
		array[index] = temp + '0';
		index++;
		num = num / 10;
	}
	array[index] = '\0';
	char* temparr = new char[index];
	int tempindex = 0;
	for (int i = index - 1; i > -1; i--) {
		temparr[tempindex++] = array[i];
	}
	delete[] array;
	array = new char[index];
	for (int i = 0; i < index; i++) {
		array[i] = temparr[i];
	}
	return array;
}
int String::stoi() {
	int num = 0;
	int size = STRLEN(Cs);
	for (int i = 0; i < size; i++) {
		num = num * 10 + (Cs[i] - '0');
	}
	return num;
}

void String::print() {
	for (int i = 0; i < len; i++) {
		cout << this->Cs[i];
	}
	cout << endl;
}
void String::setCs(const char* _cs) {
	len = STRLEN(_cs);
	this->Cs = new char[this->len + 1]{};
	for (int i = 0; i <= len; i++) {
		Cs[i] = _cs[i];
	}
}
void String::clear() {
	this->len = 0;
	delete[] Cs;
	Cs = nullptr;
}
void String::setChar(int i, char _c) {
	this->Cs[i] = _c;
}
String& String::trim() {
	if (Cs == nullptr && len == 0) {
		return *this;
	}
	int left = 0;
	while (Cs[left] == ' ' || Cs[left] == '\t' || Cs[left] == '\n') {
		left++;
	}
	int right = len - 1;
	while (Cs[right] == ' ' || Cs[right] == '\t' || Cs[right] == '\n') {
		right--;
	}
	int length = right - left + 1;
	char* NewCs = new char[length + 1];
	for (int i = 0; i < length; i++) {
		NewCs[i] = Cs[left + i];
	}
	NewCs[length] = '\0';
	delete[] Cs;
	Cs = NewCs;
	len = length;
	return *this;
}
String String::trim(const char* _cs) {
	String result = _cs;
	result.trim();
	return result;
}
bool String::compare(const String& str)const {
	int index = 0;
	while (this->Cs[index] != '\0' && str.Cs[index] != '\0') {
		if (Cs[index] != str.Cs[index]) {
			return 0;
		}
		index++;
	}
	return 1;
}
bool String::is_equal(const String& str)const {
	if (len != str.len) {
		return 0;
	}
	if (compare(str)) {
		return 1;
	}
	return 0;
}
bool String::is_greater(const String& str) {
	int index = 0;
	while (this->Cs[index] != '\0' && str.Cs[index] != '\0') {
		if (Cs[index] > str.Cs[index]) {
			return 1;
		}
		if (Cs[index] < str.Cs[index]) {
			return 0;
		}
		index++;
	}
	if (Cs[index] == '\0' && str.Cs[index] != '\0') {
		return 0;
	}
	if (Cs[index] != '\0' && str.Cs[index] == '\0') {
		return 1;
	}
	return 0;
}
bool String::is_smaller(const String& str) {
	int index = 0;
	while (this->Cs[index] != '\0' && str.Cs[index] != '\0') {
		if (Cs[index] < str.Cs[index]) {
			return 1;
		}
		if (Cs[index] > str.Cs[index]) {
			return 0;
		}
		index++;
	}
	if (Cs[index] == '\0' && str.Cs[index] != '\0') {
		return 1;
	}
	if (Cs[index] != '\0' && str.Cs[index] == '\0') {
		return 0;
	}
	return 0;
}
String String::concat(const String& str)const {
	String result;
	result.len = (len + str.len) + 2;
	result.Cs = new char[result.len];
	int index = 0;
	for (int i = 0; i < len; i++) {
		result.Cs[index] = Cs[i];
		index++;
	}
	result.Cs[index] = ' ';
	index++;
	for (int j = 0; j < str.len; j++) {
		result.Cs[index] = str.Cs[j];
		index++;
	}
	result.Cs[index] = '\0';

	return result;
}
String& String::append(const String& str) {
	int Newlen = (len + str.len) + 2;
	char* NewCs = new char[Newlen];
	int index = 0;
	for (int i = 0; i < len; i++) {
		NewCs[index] = Cs[i];
		index++;
	}
	NewCs[index] = ' ';
	index++;
	for (int j = 0; j < str.len; j++) {
		NewCs[index] = str.Cs[j];
		index++;
	}
	NewCs[index] = '\0';
	delete[] Cs;
	len = Newlen;
	Cs = NewCs;
	return *this;
}
int* String::all_sub_strings(const char* sub, int& count) {
	count = 0;
	int index = 0;
	int strindex = 0;
	strindex = STRLEN(sub);
	for (int i = 0; i <= len - strindex; i++) {
		bool found = true;
		for (int j = 0; j < strindex; j++) {
			if (Cs[i + j] != sub[j]) {
				found = false;
				break;
			}
		}
		if (found == true) {
			count++;
		}
	}
	int* indeces = new int[count];
	for (int i = 0; i <= len - strindex; i++) {
		bool found = true;
		for (int j = 0; j < strindex; j++) {
			if (Cs[i + j] != sub[j]) {
				found = false;
				break;
			}
		}
		if (found == true) {
			indeces[index++] = i;
		}
	}
	return indeces;
}

int String::find_first(char ch) {
	int index = 0;
	for (int i = 0; i < len; i++) {
		if (Cs[i] == ch) {
			index = i;
			break;
		}
	}
	return index;
}
int String::find_first_substring(const char* sub) {
	int subLen = STRLEN(sub);
	for (int i = 0; i <= len - subLen; i++) {
		bool found = true;
		for (int j = 0; j < subLen; j++) {
			if (Cs[i + j] != sub[j]) {
				found = false;
				break;
			}
		}
		if (found) {
			return i;
		}
	}
	return -1;
}
int String::find_last_substring(const char* sub) {
	int subLen = STRLEN(sub);
	int lastIndex = -1;
	for (int i = 0; i <= len - subLen; i++) {
		bool found = true;
		for (int j = 0; j < subLen; j++) {
			if (Cs[i + j] != sub[j]) {
				found = false;
				break;
			}
		}
		if (found) {
			lastIndex = i;
		}
	}
	return lastIndex;
}

int* String::find_all_substrings(const char* sub, int& count) {
	count = 0;
	int subLen = STRLEN(sub);

	// First pass: Count occurrences
	for (int i = 0; i <= len - subLen; i++) {
		bool found = true;
		for (int j = 0; j < subLen; j++) {
			if (Cs[i + j] != sub[j]) {
				found = false;
				break;
			}
		}
		if (found) {
			count++;
		}
	}
	int* indices = new int[count];
	int index = 0;
	for (int i = 0; i <= len - subLen; i++) {
		bool found = true;
		for (int j = 0; j < subLen; j++) {
			if (Cs[i + j] != sub[j]) {
				found = false;
				break;
			}
		}
		if (found) {
			indices[index++] = i;
		}
	}

	return indices;
}

int String::find_last(char ch) {
	int index = 0;
	for (int i = len - 1; i > -1; i--) {
		if (Cs[i] == ch) {
			index = i;
			break;
		}
	}
	return index;
}
int* String::find_all(char ch, int& count) {
	count = 0;
	for (int i = 0; i < len; i++) {
		if (Cs[i] == ch) {
			count++;
		}
	}
	int* indexes = new int[count];
	int j = 0;
	for (int i = 0; i < len; i++) {
		if (Cs[i] == ch) {
			indexes[j] = i;
			j++;
		}
	}
	return indexes;
}


void String::insert_at(int i, char ch) {
	int newlen = len + 1;
	int newcap = cap + 1;
	char* NewCs = new char[newlen];
	for (int j = 0; j < i; j++) {
		NewCs[j] = Cs[j];
	}
	NewCs[i] = ch;
	for (int j = i; j < newlen; j++) {
		NewCs[j + 1] = Cs[j];
	}
	NewCs[newlen] = '\0';
	delete[] Cs;
	Cs = NewCs;
	len = newlen;
	cap = newcap;
}
void String::insert_sub(int i, const String str) {
	int newlen = len + str.len;
	int newCap = newlen + 1;
	char* NewCs = new char[newCap];
	int indexCs = 0;
	for (int j = 0; j < i; j++) {
		NewCs[j] = Cs[indexCs];
		indexCs++;
	}
	for (int j = 0; j < str.len; j++) {
		NewCs[j + i] = str.Cs[j];
	}
	for (int j = str.len; j < newlen; j++) {
		NewCs[j + i] = Cs[indexCs];
		indexCs++;
	}
	NewCs[newlen] = '\0';
	delete[] Cs;
	Cs = NewCs;
	len = newlen;
	cap = newCap;
}
void String::remove_at(int i) {
	for (int k = i; k < len; k++) {
		Cs[k] = Cs[k + 1];
	}
	len = len - 1;
}

void String::remove_first(char ch) {
	int index = 0;
	for (int i = 0; i < len; i++) {
		if (Cs[i] == ch) {
			index = i;
			break;
		}
	}
	for (int i = index; i < len; i++) {
		Cs[i] = Cs[i + 1];
	}
	len = len - 1;
}
void String::remove_last(char ch) {
	int index = 0;
	for (int i = len - 1; i > -1; i--) {
		if (Cs[i] == ch) {
			index = i;
			break;
		}
	}
	for (int i = index; i < len; i++) {
		Cs[i] = Cs[i + 1];
	}
	len = len - 1;
}
void String::remove_all(char ch) {
	int newlength = 0;
	for (int i = 0; i < len; i++) {
		if (Cs[i] != ch) {
			Cs[newlength] = Cs[i];
			newlength++;
		}
	}
	Cs[newlength] = '\0';
	len = newlength;
}
String& String::ToUPPER() {
	for (int i = 0; i < len; i++) {
		if (Cs[i] >= 'a' && Cs[i] <= 'z') {
			Cs[i] = Cs[i] - 32;
		}
	}
	return *this;
}
String& String::ToLower() {
	for (int i = 0; i < len; i++) {
		if (Cs[i] >= 'A' && Cs[i] <= 'Z') {
			Cs[i] = Cs[i] + 32;
		}
	}
	return *this;
}
// String String::ToLower()const {
// 	String result(*this);
// 	for (int i = 0; i < len; i++) {
// 		if (Cs[i] >= 'A' && Cs[i] <= 'Z') {
// 			Cs[i] = Cs[i] + 32;
// 		}
// 	}
// 	return result;
// }
bool String::operator==(const String& other) const{
    return String::is_equal(other);
}
bool String::operator<(const String& other) {
    return this->is_smaller(other);
}

const char* String::c_str() const {
    return Cs;
}

int String::getlen()const{
	return len;
}