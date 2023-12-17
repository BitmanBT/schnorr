#pragma once

#include <iostream>
#include <string>

namespace colors {
    enum class COLOR : int { BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
    enum class BG_COLOR : int { BLACK = 40, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

    /**
     * Set color of console text output
     * 
     * @param color color of the text
    */
    std::string setcolor(COLOR color) {
        return "\e[" + std::to_string(static_cast<int>(color)) + "m";
    }

    /**
     * Set color of console text output
     * 
     * @param color color code of the text
    */
    std::string setcolor(int color) {
        return "\e[" + std::to_string(color) + "m";
    }

    /**
     * Set color of console text output and of console background
     * 
     * @param f_color color code of the text
     * @param b_color color code of the background
    */
    std::string setcolor(COLOR f_color, BG_COLOR b_color) {
        return "\e[" + std::to_string(static_cast<int>(f_color)) + ";" + std::to_string(static_cast<int>(b_color)) + "m";
    }
} // namespace colors

namespace console {
    void Greeting() {
        std::cout << colors::setcolor(colors::COLOR::CYAN)
              << "Welcome to the Schnorr cryptosystem simulation program!" << std::endl
              << "Now we will introduce you to the basic functionality of our simulator." << std::endl
              << "After each action performed, the program will require new instructions from you." << std::endl
              << "To instruct the program, type the action code in the suggested line." << std::endl
              << colors::setcolor(colors::COLOR::GREEN) << "The action codes can be as follows:" << std::endl
              << colors::setcolor(colors::COLOR::RED) << "[client]" << colors::setcolor(colors::COLOR::YELLOW) << " - create new client for the server (you will be asked to enter it's name)" << std::endl
              << colors::setcolor(colors::COLOR::RED) << "[keys]" << colors::setcolor(colors::COLOR::YELLOW) << " - generate pair of public and private keys (you will be asked for whom keys will be generated)" << std::endl
              << colors::setcolor(colors::COLOR::RED) << "[auth]" << colors::setcolor(colors::COLOR::YELLOW) << " - try to authenticate on the server (you will be asked who will make a try)" << std::endl
              << colors::setcolor(colors::COLOR::RED) << "[sign]" << colors::setcolor(colors::COLOR::YELLOW) << " - sign a message (you will be asked to enter a message and to enter who will sign a message)" << std::endl
              << colors::setcolor(colors::COLOR::RED) << "[verify]" << colors::setcolor(colors::COLOR::YELLOW) << " - verify existing message (you will be asked who will verify it)" << std::endl
              << colors::setcolor(colors::COLOR::RED) << "[replace]" << colors::setcolor(colors::COLOR::YELLOW) << " - replace existing signature's message (completely mess it up)" << std::endl
              << colors::setcolor(colors::COLOR::RED) << "[hack]" << colors::setcolor(colors::COLOR::YELLOW) << " - try to find out client's private key (you will be asked for the name of this client)" << std::endl
              << colors::setcolor(colors::COLOR::RED) << "[quit]" << colors::setcolor(colors::COLOR::YELLOW) << " - quit simulator" << std::endl
              << colors::setcolor(colors::COLOR::WHITE, colors::BG_COLOR::BLACK);
    }
} // namespace console