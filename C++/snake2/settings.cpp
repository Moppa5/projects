/*
####################################################################
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: Simple snake game with GUI implemented on   #
#					   to it. You can move the snake with W,A,S,D. #
#					   For more details, read the instructions.txt #
#                                                                  #
# File: settings.cpp                                               #
# Description: Implementations for the class settings and its ui   #
#                                                                  #
####################################################################
*/

#include "settings.hh"
#include <api.hh>
#include "ui_settings.h"
#include <main_window.hh>


Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_fieldUpdateButton_clicked()
{
    std::vector<int> gameData = readData();
    int x;
    int y;
    int speed;

    x = ui->spinBoxWidth->value();
    y = ui->spinBoxHeight->value();
    speed = gameData.at(parameterCount-1);
    // Updates config through api
    createConfig(x,y,speed);
}

void Settings::on_speedUpdateButton_clicked()
{
    std::vector<int> gameData = readData();
    int x;
    int y;
    int speed;

    x = gameData.at(0);
    y = gameData.at(1);
    speed = ui->horizontalSlider->value();
    // Updates config through api
    createConfig(x,y,speed);
}
