#pragma once

#include <data_structures.h>

#include <string>

namespace crypto {
    class schnorr
    {
    public:
        schnorr() = default;
        ~schnorr() = default;

        /**
         * Generates public and private keys.
         * 
         * Public key is static so it could be common for the whole channel.
         * Private key can be stored in only one object of class.
         * 
         * @remark Uses public_key and private_key structures.
        */
        void generateKeys();

        /**
         * Makes a try for authentification.
         * 
         * A try is being made by the object whose method is called.
         * Verifies authentification an object whose link we gained.
         * 
         * @remark Uses authentification_info structure.
         * @param Bob the one who is going to verify (or not) our connection
         * @return If we succeeded or not
        */
        bool establish_connection(schnorr& Bob);

        /**
         * Signes a message.
         * 
         * @remark Uses messageSign structure.
         * 
         * @param M message to sign
        */
        void sign(std::string& M);

        /**
         * Verifies digital signature.
         * 
         * @remark Uses messageSign structure.
         * 
         * @param input digital signature to verify
        */
        void verify(const messageSign& input);

        /**
         * Structures to store all information needed
         * Static because we don't need more than one
        */
        static public_key pub_k;
        static authentification_info auth;
        static messageSign mSign;

    private:
        /**
         * Structure to store private key.
        */
        private_key pr_k;
    };
} // namespace crypto