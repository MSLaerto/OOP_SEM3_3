/**
 * @file funcs.h
 * @brief This file contains the functions definitions.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */
#ifndef MLAB3_FUNCS_H
#define MLAB3_FUNCS_H

#include <iostream>
#include <numeric>
#include <limits>
#include <exception>

/**
 * @brief This function reads a number from the standard input within a specified range.
 *
 * @tparam T The type of the number to read (must be a numeric type)
 * @param min The minimum value for the number (default is the lowest possible value for the type)
 * @param max The maximum value for the number (default is the highest possible value for the type)
 * @return T The number read from the standard input
 * @throw std::runtime_error If there is an error reading the number or if the number is outside the specified range
 */
template<class T>
inline T getNum(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
    T a;
    while(true) {
        std::cin >> a;
        if(std::cin.eof())
            throw std::runtime_error("Failed to read number: EOF");
        else if(std::cin.bad())
            throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
        else if(std::cin.fail() || a < min || a > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You are wrong; repeat please!" << std::endl;
        }
        else
            std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return a;
    }
}

/**
 * @brief This function reads a line from the standard input.
 *
 * @return std::string The line read from the standard input
 * @throw std::runtime_error If there is an error reading the line
 */
inline std::string readLine() {
    std::string line;
    try {
        if (!std::getline(std::cin, line)) {
            if (std::cin.eof()) {
                throw std::runtime_error("End of file reached.");
            } else if (std::cin.fail()) {
                if (std::cin.bad()) {
                    throw std::runtime_error("Critical stream error occurred.");
                } else {
                    throw std::runtime_error("Input error occurred.");
                }
            } else {
                throw std::runtime_error("Unknown error occurred while reading input.");
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        line = "";
    }
    return line;
}

#endif //MLAB3_FUNCS_H
