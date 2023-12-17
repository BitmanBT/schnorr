#pragma once

#include <data_structures.h>
#include <schnorr.h>

namespace crypto {
    class hacker : public schnorr
    {
    public:
        hacker() = default;
        hacker(const Server& Server);
        hacker(const schnorr& Alice, const Server& Server);

        /**
         * Steals public key from schnorr object.
         * 
         * @param Alice who to steal public key from
        */
        void stealPublicKey(const schnorr& Alice);

        /**
         * Steal authentification info from server.
         * 
         * @param Server
        */
        void stealInfoFromServer(const Server& Server);

        /**
         * Trying to calculate schnorr's object's (given in constructor) private key.
        */
        void hack();

        /**
         * Shows progress in hacking before we ran out of time.
         * 
         * @return hacking progress
        */
        double getPercentages();

        /**
         * Gives you calculated private key.
         * 
         * @return 0 if key was not calculated and private key if it was
        */
        uint64_t getPrivateKey();

    private:
        /**
         * Stolen authentification info from server
        */
        authentification_info_server forHacker;

        /**
         * Hacking progress
        */
       double percentages = 0;
    };
} // namespace crypto