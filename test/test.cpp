#include<iostream>
#include<fstream>
#include<unordered_map>
#include"Cryptik.h"

using namespace std;

int main(void) {

    ifstream dict("dict.txt");
    ofstream results("results.txt");
    unordered_map<string, int> mapping;
    Cryptik Cr(0);

    for (int i=0; i<10000; i++) {

        string word;
        getline(dict, word);

        string hashed = Cr.encrypt(word);

        if (mapping.find(hashed) == mapping.end()) {

            mapping.insert({hashed, 1});
        }

        else {
            mapping[hashed] ++;
        }
    }

    for (auto& i: mapping) {

        results << i.first <<":\t" << i.second << endl;
    }

    dict.close();
    results.close();

    return 0;
}