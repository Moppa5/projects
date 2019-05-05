/*
####################################################################
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: Simple snake game with GUI implemented on   #
#					   to it. You can move the snake with W,A,S,D. #
#					   For more details, read the instructions.txt #
#                                                                  #
# File: api.cpp                                                    #
# Description: Implementation for public functions to sync data    #
#              between different classes                           #
#                                                                  #
####################################################################
*/

#include "api.hh"


void createConfig(int x, int y, int speed, std::string file) {

    std::ifstream file_object(file);

    if (file_object) {
        // Reset the config if it exists
        file_object.open(file, std::ios::out | std::ios::trunc);
    }
    std::ofstream configFile(file);
    configFile << x << ";" << y << ";" << speed;

    configFile.close();
    file_object.close();
}

bool isFile() {

    std::ifstream file_object(filename);
    if (not file_object) {
        return false;
    }

    file_object.close();
    return true;
}

std::vector<std::string> split(std::string s, std::string delimiter, bool ignore_empty) {

    // Split from exercise 6.5

    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

std::vector<int> readData()
{
    std::vector<int> dataVec;
    std::vector<std::string> tempVec;
    int x;
    int y;
    int wormspeed;

    if (isFile()) {
        std::ifstream object(filename);
        std::string row;

        while( getline(object,row)) {
            tempVec = split(row);
        }
        object.close();

        if (tempVec.size() == parameterCount) {
            /* I haven't implemented any "try catch exception" check
             * since we've been adviced not to do so. If errors
             * occur the game will just crash
            */

            x = stoi(tempVec.at(0));
            y = stoi(tempVec.at(1));
            wormspeed = stoi(tempVec.at(2));

            dataVec.push_back(x);
            dataVec.push_back(y);
            dataVec.push_back(wormspeed);
          }
    }
    return dataVec;
}
