#pragma once

#include "data_structures.h"

#include <string>
#include <vector>

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
         * Gives authentification iniformation to server if needed.
         *
         * @return Information needed for server to perform an authentification
        */
        std::vector<uint64_t>& give_authentification_info() const;

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
        bool verify(const messageSign& input) const;

        static public_key pub_k;
        authentification_info_schnorr auth;
        static messageSign mSign;

    private:
        private_key pr_k;
    };

    class Server
    {
    public:
        Server() = default;
        ~Server() = default;

        /**
         * Performs authentification.
         *
         * Object of schnorr class (who makes a try for authentification) is needed.
         *
         * @remark Fills authentification_info fields in schnorr class.
         * @param Alice the one who makes a try for authentification
         * @return Name of the one who tried to connect
        */
        std::string& authentification(schnorr& Alice);

        authentification_info_server auth;

    private:
        /**
         * Gives information to schnorr class object needed while performing an authentification.
         *
         * @param Alice schnorr class object which tries to connect
        */
        void give_authentification_info(schnorr& Alice) const;

        /**
         * Asks for information stored in schnorr class object needed for authentification.
         *
         * @param Alice schnorr class object which tries to connect
        */
        void get_authentification_info(schnorr& Alice);
    };
} // namespace crypto