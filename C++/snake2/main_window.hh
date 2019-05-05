/*
####################################################################
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: Simple snake game with GUI implemented on   #
#					   to it. You can move the snake with W,A,S,D. #
#					   For more details, read the instructions.txt #
#                                                                  #
# File: main_window.hh                                             #
# Description: Declares a class implementing a UI for the game.    #
#                                                                  #
####################################################################
*/

#ifndef PRG2_SNAKE2_MAINWINDOW_HH
#define PRG2_SNAKE2_MAINWINDOW_HH

#include "ui_main_window.h"
#include <vector>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include <random>

// Config settings
const int countOfConfigParameters = 3;
const int fieldMaximum = 30;
const int fieldMinimum = 10;
const int speedMaximum = 750;
const int speedMinimum = 50;
const int superFoodTime = 15;
const int superFoodDuration = 10;

/* \class MainWindow
 * \brief Implements the main window through which the game is played.
 */
class MainWindow: public QMainWindow {
    Q_OBJECT

public:

    /* \brief Construct a MainWindow.
     *
     * \param[in] parent The parent widget of this MainWindow.
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /* \brief Destruct a MainWindow.
     */
    ~MainWindow() override = default;

    /* \brief Change the Snake's bearing when certain keys get pressed.
     *
     * \param[in] event Contains data on pressed and released keys.
     * Implemented W,A,S,D keys and movement for them
     */
    void keyPressEvent(QKeyEvent* event) override;

    /* @brief Reads game data from config file
     * Uses api.cpp readData() function to
     * gather the information and prompt it
     */
    void readGameData();

    /* @brief Updates game data
     * Sets width x, height y and speed for the game
     */
    void updateGameData(int x,int y, int speed);

    /* @brief Checks if the game is over
     * If snake goes over the edge
     */
    bool isGameOver();

    /* @brief If game is over
     * Well the game ends then
     */
    void setGameOver();

    /* @brief Checks if is valid place
     * If the snake is there is not valid
     * Else is valid
     */
    bool isValidFoodArea(int x, int y);

    /* @brief Places the new food
     */
    void newFood();

    /* @brief Spawns the super food
     */
    void newSuperFood();

    /* @brief Sets the effect after eating
     * Going slower, faster etc.
     */
    void superFoodEffect();

    /* @brief Timer for game
     */
    QTimer* game_timer;

private slots:

    /* \brief Start the game.
     */
    void on_playButton_clicked();

    /* @brief Updates the snake parts
     * If snake eats some food, update
     */
    void updateSnake(QGraphicsRectItem* newHead);

    /* \brief Move the Snake by a square and check for collisions.
     *
     * The game ends if a wall or the Snake itself gets in the way.
     * When a food gets eaten a point is gained and the Snake grows.
     */
    void moveSnake();

    /* @brief Starts the game timer
     *
     * The amount of time used in single game
     */
    void startGameTimer();

    /* @brief For update purpose
     * Updates game timer (minutes and seconds)
     * Keeps also track on superfood effects and time generally
     */
    void updateGameTimer();

    /* @brief For updating score "timer"
     */
    void updateGameScore();

    /* @brief Reset the game
     * Resets everything
     */
    void on_resetButton_clicked();

    /* @brief Prompts player for settings window
     * Player can change some settings for game
     */
    void on_settingsButton_clicked();

    /* @brief Pause button for the game
     * click for pause
     * click after pause and game continues
     */
    void on_pauseButton_clicked();

private:

    /* \brief Make the play field visible and fit it into the view.
     *
     * Should be called every time the field's size changes.
     */
    void adjustSceneArea();

    /* @brief Adjusts the score
     * Score multiplier will be updated in
     * respect of the speed
     */
    void adjustScore();

    Ui::MainWindow ui_;                   /**< Accesses the UI widgets. */
    QGraphicsEllipseItem* food_= nullptr; /**< The food item in the scene. */
    QGraphicsEllipseItem*
    superFood_ = nullptr;                 /**< Food that gives some special */
    QGraphicsRectItem* snake_ = nullptr;  /**< first snake part> */
    std::vector<QGraphicsRectItem*>       /**<Contains the snake's parts */
    wholeSnake_;
    std::string direction_ = "right";     /**< Contains snake movement direction */
    QGraphicsScene scene_;                /**< Manages drawable objects. */
    QTimer timer_;                        /**< Triggers the Snake to move. */
    std::default_random_engine rng_;      /**< Randomizes food locations. */

    int game_width_;                      /**< Game area width */
    int game_height_;                     /**< Game area height */
    int timer_value_;                     /**< Timer value for snake movement */
    bool isOver_ = true;                  /**< If game is over, default
                                               game is over */
    int scoreMultiplier_ = 1;             /**< Score multiplier for game scores */
    int score_ = 0;                       /**< Score for the game */
    bool paused_ = false;                 /**< If game is paused */
    bool isSuperFood_ = false;            /**< If the superfood is on */
    bool isEffect_ = false;               /**< If superfood effect is on */
    int effectTime_ = 0;                  /**< Time when effect is put on */
    int effectDuration_ = 0;              /**< Effect duration time */
    int originalSpeed_ = 0;               /**< Snake's original speed */
    int foodTime_ = 0;                    /**< How long the food is available */
    int foodEffect_ = 0;                  /**< Food has some color effect */

};  // class MainWindow


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
