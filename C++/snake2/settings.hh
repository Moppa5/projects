/*
####################################################################
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: Simple snake game with GUI implemented on   #
#					   to it. You can move the snake with W,A,S,D. #
#					   For more details, read the instructions.txt #
#                                                                  #
# File: settings.hh                                                #
# Description: Defines a class and ui for settings in snake game   #
#                                                                  #
####################################################################
*/

#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <QMainWindow>
#include <api.hh>

namespace Ui {
class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:

    /* @brief Updates field data
     */
    void on_fieldUpdateButton_clicked();

    /* @brief Updates speed data
     */
    void on_speedUpdateButton_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_HH
