//includes
#include"Cryptik.h"

Cryptik::Cryptik(float delay) {

    this->wait = delay*1000000000;
}

Cryptik::Crypt::Crypt(std::string originalString, std::string salt, std::string hashed) {

    this->originalString = originalString;
    this->salt = salt;
    this->hashedString = hashed;
}

std::string Cryptik::getSalt() {
    //returns a randomly generated salt from given string.

    static const char saltChars[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890!@#$%&";
    std::string salt = "";

    for (int i=0; i<10; i++) {

        int randInt = rand() % 68;

        salt += saltChars[randInt];
    }

    return salt;
}

std::string Cryptik::getHash(std::string compositeString) {
    //generates a hashed string based on a hash function (to be implemented).

    std::string hashedString = "";

    for (unsigned long int i=0; i<compositeString.length()-1; i++) {
        
        int x = (int)compositeString[i] ^ (int)(compositeString[i+1]);
        int hf =  ((int)compositeString[i] + x) % 23;

        hashedString += std::to_string(hf);
    }

    return hashedString;
}

void Cryptik::mapEncryption(std::string hashedString, Crypt info) {
    //adds the encryption details to encryptionTable map<string, struct Cryptic>

    encryptionTable.insert({hashedString, info});
}

Cryptik::Crypt Cryptik::getHashInfo(std::string hashedString) {
    // returns hashed info struct

    if (encryptionTable.find(hashedString) == encryptionTable.end()) {
        struct Crypt none("", "", "");

        return none;
    }    

    else {
        return encryptionTable.find(hashedString)->second;  //find returns a pair of key and value.
    }
}

std::string Cryptik::encrypt(std::string originalString) {
    //encrypts a string and returns the encrypted string, the encrypted string is called as 'hashedValue' everywhere in preogram.

    std::string salt = getSalt();

    std::string compositeString = originalString + salt;

    std::string hashedString = getHash(compositeString);
    
    struct Crypt info(originalString, salt, hashedString);

    mapEncryption(hashedString, info);

    return hashedString;
}

bool Cryptik::compare(std::string hashedString, std::string originalString) {

    //compares the hashed string with given value of original string.

    try {
        struct Crypt hashInfo = getHashInfo(hashedString);

        if (hashInfo.salt == "") {
            throw "String never encrypted";
        }

        else {
            std::string compositeString = originalString + hashInfo.salt;
            std::string newHashString = getHash(compositeString);

            std::this_thread::sleep_for(std::chrono::nanoseconds(this->wait));

            if (newHashString == hashedString) {
                return true;
            }

            else {
                return false;
            }
        }
    }

    catch (std::string NeverEncryptedError) {

        return false;
    }
}