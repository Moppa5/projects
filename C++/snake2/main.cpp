/*
####################################################################
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: Simple snake game with GUI implemented on   #
#					   to it. You can move the snake with W,A,S,D. #
#					   For more details, read the instructions.txt #
#                                                                  #
# File: main.cpp                                                   #
# Description: Starts executing the program.                       #
#                                                                  #
####################################################################
*/

#include "main_window.hh"
#include <QApplication>


int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Snake the Game");
    w.show();
    return a.exec();
}
