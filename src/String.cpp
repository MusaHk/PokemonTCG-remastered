//
// Created by User on 6/10/2025.
//
#include "String.h"
#include <iostream>
// Default constructor
string::string() {
    len = 0;
    cap = 50;
    str = new char[cap];
    str[0] = '\0';
}

string::string(const char* s, int n) {
    cap = n;
    len = get_size(s);
    str = new char[cap];
    for (int i = 0; i < len; i++) {
        str[i] = s[i];
    }
    str[len] = '\0';
}

string::string(const string &s) {
    if (s.str == nullptr) {
        cap = 0;
        len = 0;
        str = nullptr;
    } else {
        cap = s.cap;
        len = s.len;
        str = new char[len + 1];
        for (int i = 0; i < len; i++) {
            str[i] = s.str[i];
        }
        str[len] = '\0';
    }
}

string::string(const char* s) {
    cap = 50;
    len = get_size(s);
    str = new char[cap];
    for (int i = 0; i < len; i++) {
        str[i] = s[i];
    }
    str[len] = '\0';
}

string::string(int n) {
    *this = itos(n);
}

std::ostream& operator<<(std::ostream& os, const string& s) {
    os << s.str;
    return os;
}

std::istream& operator>>(std::istream& in, string& s) {
    char temp[100] = { '\0' };
    in >> temp;
    s.len = string::get_size(temp);
    if (s.len >= s.cap) {
        delete[] s.str;
        s.cap = s.len + 1;
        s.str = new char[s.cap];
    }
    for (int i = 0; i < s.len; i++) {
        s.str[i] = temp[i];
    }
    s.str[s.len] = '\0';
    return in;
}

string string::operator+(const string& s) const {
    string temp("", s.len + len + 1);
    for (int i = 0; i < len; i++) {
        temp.str[i] = str[i];
    }
    for (int i = len; i < len + s.len; i++) {
        temp.str[i] = s.str[i - len];
    }
    temp.str[len + s.len] = '\0';
    temp.len = len + s.len;
    return temp;
}

string& string::operator+=(const string& s) {
    int origLen = len;
    int newLen = len + s.len;
    char* temp = new char[newLen + 1];

    for (int i = 0; i < origLen; i++) {
        temp[i] = str[i];
    }
    for (int i = 0; i < s.len; i++) {
        temp[origLen + i] = s.str[i];
    }
    temp[newLen] = '\0';

    delete[] str;
    str = temp;
    len = newLen;

    return *this;
}
string& string::operator=(const string& s) {
    if (this == &s)
        return *this;
    delete[] str;
    cap = s.cap;
    len = s.len;
    str = new char[cap];
    for (int i = 0; i < len; i++) {
        str[i] = s.str[i];
    }
    str[len] = '\0';
    return *this;
}

const char string::operator[](int i) const {
    if (i < 0 || i >= len) {
        throw std::runtime_error("out of bounds access");
    }
    return str[i];
}

char& string::operator[](int i) {
    if (i < 0 || i >= len) {
        throw std::runtime_error("out of bounds access");
    }
    return str[i];
}

string string::itos(int n) {
    int i = 0;
    string s;
    if(n == 0) {
        s.str[0] = '0';
        s.str[1] = '\0';
        s.len = 1;
        return s;
    }
    bool isNeg = false;
    if(n < 0) {
        isNeg = true;
        n = -n;
    }
    while(n > 0) {
        int cur = n % 10;
        s.str[i++] = '0' + cur;
        n /= 10;
    }
    if(isNeg) {
        s.str[i++] = '-';
    }
    s.str[i] = '\0';
    s.len = i;
    s.cap = 50;
    for (int j = 0; j < s.len / 2; j++) {
        char temp = s.str[j];
        s.str[j] = s.str[s.len - j - 1];
        s.str[s.len - j - 1] = temp;
    }
    return s;
}

string string::insert_char(int n, char ch) {
    if (cap <= len + 1) {
        *this = regrow();
    }
    for (int i = len; i > n; i--) {
        str[i] = str[i - 1];
    }
    str[n] = ch;
    len++;
    str[len] = '\0';
    return *this;
}

// insert_string: insert a string at position n
string string::insert_string(int n, const string& sub) {
    if (cap <= len + sub.len) {
        *this = regrow();
    }
    int space = n - len;
    if (space > 0) {
        for (int i = 0; i < space; i++) {
            str[i + len] = ' ';
        }
    }
    for (int i = len; i >= sub.len; i--) {
        str[i + sub.len] = str[i];
    }
    for (int i = 0; i < sub.len; i++) {
        str[n + i] = sub.str[i];
    }
    len += sub.len;
    str[len] = '\0';
    return *this;
}

string& string::replace_first(char ch) {
    if (len > 0)
        str[0] = ch;
    return *this;
}

int string::get_size(const char* s) {
    int i = 0;
    while(s[i] != '\0') {
        i++;
    }
    return i;
}

void string::to_upper() {
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

void string::to_lower() {
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}

string& string::trim() {
    int start = 0;
    int end = len - 1;
    while (start < len && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')) {
        start++;
    }
    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')) {
        end--;
    }
    int new_len = end - start + 1;
    for (int i = 0; i < new_len; i++) {
        str[i] = str[start + i];
    }
    str[new_len] = '\0';
    len = new_len;
    return *this;
}

string string::trim(const char* s) {
    int start = 0;
    int end = get_size(s) - 1;
    while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n') {
        start++;
    }
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')) {
        end--;
    }
    int new_len = end - start + 1;
    char* trimmed_str = new char[new_len + 1];
    for (int i = 0; i < new_len; i++) {
        trimmed_str[i] = s[start + i];
    }
    trimmed_str[new_len] = '\0';
    string result(trimmed_str);
    delete[] trimmed_str;
    return result;
}


int string::stoi() const {
    int i = 0;
    int num = 0;
    bool isNeg = false;
    if (str[0] == '-') {
        isNeg = true;
        i = 1;
    }
    while (i < len) {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return isNeg ? -num : num;
}

void string::display() const {
    std::cout << str;
}

string::~string() {
    delete[] str;
}


bool string::is_equal(const string& m) const {
    if (m.len != len) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (str[i] != m.str[i]) {
            return false;
        }
    }
    return true;
}

bool string::is_less(const string& m) const {
    int min_len = (len < m.len) ? len : m.len;
    for (int i = 0; i < min_len; i++) {
        if (str[i] < m.str[i]) {
            return true;
        }
        if (str[i] > m.str[i]) {
            return false;
        }
    }
    return len < m.len;
}

bool string::is_greater(const string& m) const {
    int min_len = (len < m.len) ? len : m.len;
    for (int i = 0; i < min_len; i++) {
        if (str[i] > m.str[i]) {
            return true;
        }
        if (str[i] < m.str[i]) {
            return false;
        }
    }
    return len > m.len;
}

string string::concat(const string& s) const {
    string temp("", s.len + len + 1);
    for (int i = 0; i < len; i++) {
        temp.str[i] = str[i];
    }
    for (int i = len; i < len + s.len; i++) {
        temp.str[i] = s.str[i - len];
    }
    temp.str[len + s.len] = '\0';
    temp.len = len + s.len;
    return temp;
}

string* string::split(char delimiter, int &count) const {
    count = 1;
    for (int i = 0; i < len; i++) {
        if (str[i] == delimiter) {
            count++;
        }
    }
    string* splitArr = new string[count];
    int curIndex = 0, curLen = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == delimiter) {
            splitArr[curIndex].len = curLen;
            splitArr[curIndex].str[curLen] = '\0';
            curLen = 0;
            curIndex++;
        } else {
            splitArr[curIndex].str[curLen] = str[i];
            curLen++;
        }
    }
    splitArr[curIndex].len = curLen;
    splitArr[curIndex].str[curLen] = '\0';
    return splitArr;
}

string* string::split(const string& delimiters, int &count) const {
    count = 1;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < delimiters.len; j++) {
            if (str[i] == delimiters.str[j]) {
                count++;
                break;
            }
        }
    }
    string* splitArr = new string[count];
    int curIndex = 0, curLen = 0;
    for (int i = 0; i < len; i++) {
        bool flag = false;
        for (int j = 0; j < delimiters.len; j++) {
            if (str[i] == delimiters.str[j]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            splitArr[curIndex].str[curLen] = '\0';
            splitArr[curIndex].len = curLen;
            curLen = 0;
            curIndex++;
        } else {
            splitArr[curIndex].str[curLen] = str[i];
            curLen++;
        }
    }
    splitArr[curIndex].len = curLen;
    splitArr[curIndex].str[curLen] = '\0';
    return splitArr;
}


void string::remove_char(int n) {
    for (int i = n; i < len - 1; i++) {
        str[i] = str[i + 1];
    }
    len--;
    str[len] = '\0';
}

void string::remove_first(char ch) {
    int first = find_first(ch);
    if (first != -1) {
        remove_char(first);
    }
}

void string::remove_last(char ch) {
    int last = find_last(ch);
    if (last != -1) {
        remove_char(last);
    }
}

void string::remove_all(char a) {
    int count = 0;
    int* indices = find_all(a, count);
    for (int i = 0; i < count; i++) {
        remove_char(indices[i] - i);
    }
    delete[] indices;
}

int* string::all_sub_string(const string& sub, int &count) const {
    int* temp = new int[len];
    count = 0;
    for (int i = 0; i < len; i++) {
        bool flag = true;
        for (int j = 0; j < sub.len; j++) {
            if (i + j >= len || str[i + j] != sub.str[j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            temp[count++] = i;
        }
    }
    return temp;
}

int string::find_first(char ch) const {
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            return i;
        }
    }
    return -1;
}

int string::find_last(char ch) const {
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == ch) {
            return i;
        }
    }
    return -1;
}

int* string::find_all(char ch, int &count) const {
    int* temp = new int[len];
    count = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            temp[count++] = i;
        }
    }
    return temp;
}

string string::regrow() {
    int newCap = cap + cap; // double the capacity
    string temp("", newCap);
    temp.len = len;
    for (int i = 0; i < len; i++) {
        temp.str[i] = str[i];
    }
    temp.str[len] = '\0';
    cap = newCap;
    delete[] str;
    str = new char[cap];
    for (int i = 0; i < len; i++) {
        str[i] = temp.str[i];
    }
    str[len] = '\0';
    return *this;
}


int string::length() const {
    return len;
}

void string::clear() {
    len = 0;
    if (str != nullptr) {
        str[0] = '\0';
    }
}