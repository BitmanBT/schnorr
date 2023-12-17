#include <iostream>
#include <map>
#include <string>
#include <cstdint>

#include <console.h>
#include <schnorr.h>
#include <hacker.h>
#include <factory.h>

using namespace colors;

// Legal commands to simulator
enum COMMANDS : int {CLIENT = 1, KEYS, AUTH, SIGN, VERIFY, HACK, QUIT};

int main() {
    // Greeting to user
    console::Greeting();

    // Preparatory activities
    crypto::Server server;
    crypto::ClientFactory clis;
    
    // A map of the correspondence of commands and their string representation
    std::map<std::string, int> map = { {"client", COMMANDS::CLIENT}, {"keys", COMMANDS::KEYS}, {"auth", COMMANDS::AUTH},
                                       {"sign", COMMANDS::SIGN}, {"verify", COMMANDS::VERIFY}, {"hack", COMMANDS::HACK},
                                       {"quit", COMMANDS::QUIT} };
    
    // Working part
    bool quit = false;
    while (!quit) {
        std::cout << ">> ";
        std::string in;
        std::cin >> in;

        switch (map[in])
        {
        case COMMANDS::CLIENT:
            {
                std::cout << setcolor(COLOR::MAGENTA) << "Enter new client's name: " << setcolor(COLOR::WHITE);
                std::string name;
                std::cin >> name;
                clis.createClient(name);
                break;
            }

        case COMMANDS::KEYS:
            {
                if (clis.clientPtrs.empty()) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No clients exist!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                std::cout << setcolor(COLOR::MAGENTA) << "Enter the name of the client you want to generate keys: " << setcolor(COLOR::WHITE);
                std::string name;
                std::cin >> name;
                crypto::schnorr* chosenOne = clis.findByName(name);
                if (chosenOne == nullptr) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No client with such name!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                chosenOne->generateKeys(server);
                std::cout << chosenOne->name_ << " generated such public key: " << chosenOne->pub_k << std::endl;
                break;
            }

        case COMMANDS::AUTH:
            {
                if (clis.clientPtrs.empty()) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No clients exist!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                std::cout << setcolor(COLOR::MAGENTA) << "Enter the name of the client you want to perform authentication on the server: " << setcolor(COLOR::WHITE);
                std::string name;
                std::cin >> name;
                crypto::schnorr* chosenOne = clis.findByName(name);
                if (chosenOne == nullptr) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No client with such name!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                crypto::public_key emptykey;
                if (chosenOne->pub_k == emptykey) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] This client hasn't generated keys!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                std::string out = server.authentification(*chosenOne);
                std::cout << "The server recognized " << out << std::endl;
                break;
            }

        case COMMANDS::SIGN:
            {
                if (clis.clientPtrs.empty()) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No clients exist!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                std::cout << setcolor(COLOR::MAGENTA) << "Enter the name of the client you want to sign a message: " << setcolor(COLOR::WHITE);
                std::string name;
                std::cin >> name;
                crypto::schnorr* chosenOne = clis.findByName(name);
                if (chosenOne == nullptr) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No client with such name!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                crypto::public_key emptykey;
                if (chosenOne->pub_k == emptykey) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] This client hasn't generated keys!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                std::cout << setcolor(COLOR::MAGENTA) << "Enter the message: " << setcolor(COLOR::WHITE);
                std::string message;
                std::getline(std::cin >> std::ws, message);
                if (message.empty()) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] Empty message!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                chosenOne->sign(message);
                std::cout << "Message signed" << std::endl;
                break;
            }

        case COMMANDS::VERIFY:
            {
                if (clis.clientPtrs.empty()) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No clients exist!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                if (clis.clientPtrs[0]->mSign.M.empty()) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No message exists!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                std::cout << setcolor(COLOR::MAGENTA) << "Enter the name of the client you want to verify existing message: " << setcolor(COLOR::WHITE);
                std::string name;
                std::cin >> name;
                crypto::schnorr* chosenOne = clis.findByName(name);
                if (chosenOne == nullptr) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No client with such name!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                std::cout << std::boolalpha << "Result of verification: " << chosenOne->verify(clis.clientPtrs[0]->mSign) << std::endl;
                break;
            }
        
        case COMMANDS::HACK:
            {
                if (clis.clientPtrs.empty()) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No clients exist! Nobody to hack!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                std::cout << setcolor(COLOR::MAGENTA) << "Enter the name of the client you want to hack: " << setcolor(COLOR::WHITE);
                std::string name;
                std::cin >> name;
                crypto::schnorr* chosenOne = clis.findByName(name);
                if (chosenOne == nullptr) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] No client with such name!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                crypto::public_key emptykey;
                if (chosenOne->pub_k == emptykey) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] This client hasn't generated keys!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                if (chosenOne->auth.e == 0) {
                    std::cout << setcolor(COLOR::RED) << "[ERROR] This client hasn't performed authentification yet!" << setcolor(COLOR::WHITE) << std::endl;
                    break;
                }
                crypto::hacker hacker(*chosenOne, server);
                hacker.hack();
                uint64_t out = hacker.getPrivateKey();
                if (out) {
                    std::cout << "Success! Private key of " << name << " is " << out << std::endl;
                } else {
                    std::cout << "Hacker ran out of time. He went through " << hacker.getPercentages() << '%' << " of the passwords" << std::endl;
                }
                break;
            }

        case COMMANDS::QUIT:
            quit = true;
            break;
        
        default:
            std::cout << setcolor(COLOR::RED) << "Invalid command! Try again!" << std::endl << setcolor(COLOR::WHITE);
            break;
        }
    }
}