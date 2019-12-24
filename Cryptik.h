#ifndef CRYPTIK_H_
#define CRYPTIK_H_

#include<iostream>
#include<string>
#include<unordered_map>

class Cryptik {
    //cryptik main class

    private:

        struct Crypt {
            //Cryptic info of string

            std::string originalString;      //the original string
            std::string salt;                //a randomly generated salt
            std::string hashedString;              //result of hashing

            Crypt(std::string originalString, std::string salt, std::string hashed);              
        };

        std::unordered_map<std::string, struct Crypt>  encryptionTable;   //a map to store generated hashed value to info of string.

        std::string getSalt();
        std::string getHash(std::string compositeString);
        void mapEncryption(std::string hashedString, struct Crypt info);
        struct Crypt getHashInfo(std::string hashedString);

    public:

        std::string encrypt(std::string originalString);
        bool compare(std::string hashedString, std::string originalString) ;
};

#endif // !CRYPTIK_H_
