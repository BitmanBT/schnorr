#pragma once

#include <data_structures.h>

#include <string>
#include <vector>
#include <utility>

namespace crypto {
    class Server;

    class schnorr
    {
    public:
        schnorr() = default;
        schnorr(std::string name);
        ~schnorr() = default;

        /**
         * Generates public and private keys.
         *
         * @remark Uses public_key and private_key structures.
         * @param server server who is going to perform authentification
        */
        void generateKeys(Server& server);

        /**
         * Gives authentification iniformation to server if needed.
         *
         * @return Information needed for server to perform an authentification
        */
        std::vector<uint64_t> give_authentification_info();

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

        public_key pub_k;
        authentification_info_schnorr auth;
        static messageSign mSign;

        /**
         * My name :)
        */
        std::string name_ = "";

    protected:
        private_key pr_k;
    };

    class Server
    {
    public:
        Server() = default;
        ~Server() = default;

        /**
         * Is called when new member of channel appears and we have to store its public key and name.
         * 
         * @param member_info member's public key and name paired
        */
        void setNewMember(std::pair<public_key, std::string> member_info);

        /**
         * Performs authentification.
         *
         * Object of schnorr class (who makes a try for authentification) is needed.
         *
         * @remark Fills authentification_info fields in schnorr class.
         * @param Alice the one who makes a try for authentification
         * @return Name of the one who tried to connect
        */
        std::string authentification(schnorr& Alice);

        authentification_info_server auth;

    private:
        /**
         * Gives information to schnorr class object needed while performing an authentification.
         *
         * @param Alice schnorr class object which tries to connect
        */
        void give_authentification_info(schnorr& Alice);

        /**
         * Asks for information stored in schnorr class object needed for authentification.
         *
         * @param Alice schnorr class object which tries to connect
        */
        void get_authentification_info(schnorr& Alice);

        /**
         * Here we store names of objects and their corresponding public keys.
        */
        std::vector<std::pair<public_key, std::string>> storage;
    };
} // namespace crypto