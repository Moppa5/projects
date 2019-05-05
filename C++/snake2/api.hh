/*
####################################################################
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: Simple snake game with GUI implemented on   #
#					   to it. You can move the snake with W,A,S,D. #
#					   For more details, read the instructions.txt #
#                                                                  #
# File: api.hh                                                     #
# Description: Defines some public functions in class template     #
#              for main_window and settings classes                #
#                                                                  #
####################################################################
*/

#ifndef API_HH
#define API_HH

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// config settings
const std::string filename = "config";
const int width = 20;
const int height = 10;
const int wormspeed = 300;
const int parameterCount = 3;

/* @brief Creates config file
 * For game's data purposes a config file
 * Can also be used to update config file
 */
void createConfig(int x = width, int y = height, int speed = wormspeed, std::string file=filename);


/* @brief Checks if the file still exists
 * For security purposes
 */
bool isFile();

/* @brief Splits the data into string vector
 */
std::vector<std::string> split(std::string s, std::string delimiter = ";",
                               bool ignore_empty = false);

/* @brief Reads the data from config file
 */
std::vector<int> readData();

#endif // API_HH
