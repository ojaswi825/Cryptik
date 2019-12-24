//includes
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

            Crypt(std::string originalString, std::string salt, std::string hashed) {

                this->originalString = originalString;
                this->salt = salt;
                this->hashedString = hashed;
            }                
        };

        std::unordered_map<std::string, struct Crypt>  encryptionTable;   //a map to store generated hashed value to info of string.

        std::string getSalt() {
            //returns a randomly generated salt from given string.

            static const char saltChars[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890!@#$%&";
            std::string salt = "";

            for (int i=0; i<10; i++) {

                int randInt = rand() % 68;

                salt += saltChars[randInt];
            }

            std::cout << "Salt: " << salt << std::endl;

            return salt;
        }

        std::string getHash(std::string compositeString) {
            //generates a hashed string based on a hash function (to be implemented).

            unsigned long int sum = 0;
            std::string hashedString = "";

            for (int i=0; i<compositeString.length(); i++) {

                sum += (int)compositeString[i];
            }

            hashedString = std::to_string(sum);

            return hashedString;
        }

        void mapEncryption(std::string hashedString, struct Crypt info) {
            //adds the encryption details to encryptionTable map<string, struct Cryptic>

            encryptionTable.insert({hashedString, info});
        }

        struct Crypt getHashInfo(std::string hashedString) {
            // returns hashed info struct

            if (encryptionTable.find(hashedString) == encryptionTable.end()) {
                struct Crypt none("", "", "");

                return none;
            }    

            else {
                return encryptionTable.find(hashedString)->second;  //find returns a pair of key and value.
            }
        }

    public:

        std::string encrypt(std::string originalString) {
            //encrypts a string and returns the encrypted string, the encrypted string is called as 'hashedValue' everywhere in preogram.

            std::string salt = getSalt();

            std::string compositeString = originalString + salt;

            std::string hashedString = getHash(compositeString);
            
            struct Crypt info(originalString, salt, hashedString);

            mapEncryption(hashedString, info);

            return hashedString;
        }

        bool compare(std::string hashedString, std::string originalString) {

            try {
                struct Crypt hashInfo = getHashInfo(hashedString);

                if (hashInfo.salt == "") {
                    throw "String never encrypted";
                }

                else {
                    std::string compositeString = originalString + hashInfo.salt;
                    std::string newHashString = getHash(compositeString);

                    if (newHashString == hashedString) {
                        return true;
                    }

                    else {
                        return false;
                    }
                }
            }

            catch (std::string NeverEncryptedError) {
                std::cout << NeverEncryptedError << std::endl;

                return false;
            }
        }    

};


int main() {
    
    Cryptik C;

    std::string enc = C.encrypt("a");

    bool res_a = C.compare(enc, "a");
    std::cout << "Comparing with a: " << res_a << std::endl;

    bool res_A = C.compare(enc, "A");
    std::cout << "Comparing with A: " << res_A << std::endl;

    return 0;
}