/*
####################################################################
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: Simple snake game with GUI implemented on   #
#					   to it. You can move the snake with W,A,S,D. #
#					   For more details, read the instructions.txt #
#                                                                  #
# File: main_window.cpp                                            #
# Description: Defines a class implementing a UI for the game.     #
#                                                                  #
####################################################################
*/

#include "main_window.hh"
#include <api.hh>
#include <settings.hh>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QDebug>


MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent) {

    ui_.setupUi(this);
    ui_.graphicsView->setScene(&scene_);
    ui_.resetButton->setDisabled(true);
    ui_.pauseButton->setDisabled(true);
    ui_.diedLabel->hide();
    connect(&timer_, &QTimer::timeout, this, &MainWindow::moveSnake);
    // Create config file for the game
    createConfig();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {

    if (isOver_ != true) {
        if (event->key() == Qt::Key_S and direction_ != "up") {
            ui_.statusLabel->setText("Moving down");
            direction_ = "down";

        } else if (event->key() == Qt::Key_A and direction_ != "right") {
            ui_.statusLabel->setText("Moving left");
            direction_ = "left";

        } else if (event->key() == Qt::Key_D and direction_ != "left") {
            ui_.statusLabel->setText("Moving right");
            direction_ = "right";

        } else if (event->key() == Qt::Key_W and direction_ != "down") {
            ui_.statusLabel->setText("Moving up");
            direction_ = "up";
        } else if (event->key() == Qt::Key_Space) {
            on_pauseButton_clicked();
        }
    }
}

void MainWindow::readGameData()
{
    std::vector<int> gameData = readData();
    if (gameData.size() == countOfConfigParameters) {
        // Read the game data from the vector
        int x;
        int y;
        int speed;
        x = gameData.at(0);
        y = gameData.at(1);
        speed = gameData.at(2);

        if (x>= fieldMinimum && x<= fieldMaximum && y >= fieldMinimum &&
                y <= fieldMaximum && speed >= speedMinimum
                && speed <= speedMaximum) {
                updateGameData(x,y,speed);
        }
    }
}

void MainWindow::updateGameData(int x, int y, int speed)
{
    game_height_ = y;
    game_width_ = x;
    timer_value_ = speed;
}

bool MainWindow::isGameOver()
{
    if (wholeSnake_.back()->x() >= game_width_ or wholeSnake_.back()->x() < 0) {
        return true;
    } else if (wholeSnake_.back()->y() >= game_height_ or wholeSnake_.back()->y()<0) {
        return true;
    } else if (static_cast<int>(wholeSnake_.size()) >= game_width_ * game_height_) {
        return true;
    }

    return false;
}

void MainWindow::setGameOver()
{
    isOver_ = true;
    timer_.stop();
    delete game_timer;

    ui_.statusLabel->setText("Game over");
    int newScore = ui_.lcdNumberScore->value();
    QString scoreMessage = "Your best score: ";

    if (newScore > score_) {
        scoreMessage = "New best score: ";
        scoreMessage += QString::number(newScore);
        score_ = newScore;
    } else {
        scoreMessage+= QString::number(score_);
    }

    ui_.showScoreLabel->setText(scoreMessage);
    ui_.diedLabel->setText("Game over");

    ui_.diedLabel->show();
    ui_.showScoreLabel->show();
    ui_.resetButton->setDisabled(true);
    ui_.pauseButton->setDisabled(true);
    ui_.settingsButton->setEnabled(true);
    ui_.playButton->setEnabled(true);
}
bool MainWindow::isValidFoodArea(int x, int y) {

    for (QGraphicsRectItem* part: wholeSnake_) {
        // If snek is not there
        if (part->x() == x and part->y() == y) {
            return true;
        }
    }
   return false;
}
void MainWindow::newFood()
{
    std::uniform_int_distribution<int> width(0,game_width_-1);
    std::uniform_int_distribution<int> height(0,game_height_-1);
    int x;
    int y;

    while (true) {
        x = width(rng_);
        y = height(rng_);

        if (!isValidFoodArea(x,y)) {
            break;
        }
    }
    food_->setPos(x,y);
}

void MainWindow::newSuperFood()
{
    std::uniform_int_distribution<int> width(0,game_width_-1);
    std::uniform_int_distribution<int> height(0,game_height_-1);
    int x;
    int y;

    while (true) {
        x = width(rng_);
        y = height(rng_);

        if (!isValidFoodArea(x,y) and x != food_->x() and y != food_->y()) {
            break;
        }
    }
    superFood_->show();
    superFood_->setPos(x,y);
}

void MainWindow::superFoodEffect()
{
    /* Effects here
     * 0 => score multiplier
     * 1 => More speed
     * 2 => Less speed
     */
    std::uniform_int_distribution<int> random(0,2);
    isEffect_ = true;
    int effect = random(rng_);

    if (effect == 0) {
        // Add score multiplier
        scoreMultiplier_ += 30;
        effectDuration_ = 10;
    } else if (effect == 1) {
        // Set faster speed
        if (timer_value_ >= 100) {
            timer_.start(100);
            timer_value_ = 100;
            effectDuration_ = 7;
            adjustScore();
        }
    } else if (effect == 2) {
        if (timer_value_ < 750) {
            // Set slower speed
            timer_value_ = 750;
            timer_.start(750);
            effectDuration_ = 7;
            adjustScore();
        }
    }
    effectTime_ = ui_.lcdNumberSec->value();
    isSuperFood_ = false;
}

void MainWindow::on_playButton_clicked() {
    // Clear the widgets and put settings default
    // Tl;dr reset the game
    readGameData();
    scene_.clear();
    wholeSnake_.clear();
    isSuperFood_ = false;
    isEffect_ = false;
    isOver_ = false;
    direction_ = "right";

    ui_.playButton->setDisabled(true);
    ui_.settingsButton->setDisabled(true);
    ui_.resetButton->setEnabled(true);
    ui_.pauseButton->setEnabled(true);
    ui_.welcomeLabel->hide();
    ui_.diedLabel->hide();
    ui_.instructionsBrowser->hide();
    ui_.showScoreLabel->hide();

    ui_.lcdNumberMin->display(0);
    ui_.lcdNumberSec->display(0);
    ui_.lcdNumberScore->display(0);
    startGameTimer();
    adjustScore();
    ui_.statusLabel->setText("Moving right");

    // Create game elements
    const QRect food_rect(0, 0, 1, 1);
    const QPen pen(Qt::white, 0);
    const QBrush brush(Qt::green);
    food_ = scene_.addEllipse(food_rect, pen, brush);
    food_->setPos(7, 5);

    QRectF snake_rect(0,0,1,1);
    const QPen snake_pen(Qt::green,0);
    const QBrush snake_brush(Qt::yellow);
    snake_ = scene_.addRect(snake_rect,snake_pen,snake_brush);
    snake_->setPos(2,3);

    const QBrush superBrush(Qt::blue);
    superFood_ = scene_.addEllipse(food_rect, pen, superBrush);
    superFood_->hide();

    wholeSnake_.push_back(snake_);
    adjustSceneArea();
    timer_.start(timer_value_);
    originalSpeed_ = timer_value_;
}

void MainWindow::updateSnake(QGraphicsRectItem* newHead)
{
    // Eat the food and get more points or continue with the same
    if (newHead->pos() == food_->pos()) {
        wholeSnake_.at(wholeSnake_.size()-1)->setBrush(QBrush(Qt::magenta));
        updateGameScore();
        newFood();

    // Eat superfood and get some effect
    } else if (isSuperFood_ == true) {
        /* Needed to make the if statements like this
           since otherwise the game would've crashed
           because superFood_ isn't in the game area */
        if (newHead->pos() == superFood_->pos()) {
            // Snake eats the superfood
            wholeSnake_.at(wholeSnake_.size()-1)->setBrush(QBrush(Qt::magenta));
            superFoodEffect();

            isSuperFood_ = false;
            superFood_->hide();

        } else {
            QGraphicsRectItem* tail = wholeSnake_.front();
            wholeSnake_.erase(wholeSnake_.begin());
            delete tail;
        }
    } else {
        QGraphicsRectItem* tail = wholeSnake_.front();
        wholeSnake_.erase(wholeSnake_.begin());
        delete tail;
     }
}

void MainWindow::moveSnake() {

    // Adds some effect for the superfood
    if (foodEffect_ == 0) {
        superFood_->setBrush(QBrush(Qt::magenta));
        foodEffect_ = 1;
    } else {
        superFood_->setBrush(QBrush(Qt::blue));
        foodEffect_ = 0;
    }

    QGraphicsRectItem* head = wholeSnake_.back();
    int newPosx = 0;
    int newPosy = 0;

    // Snake direction
    if (direction_ == "right") {
        newPosx = head->x()+1;
        newPosy = head->y();
    } else if (direction_ == "left") {
        newPosx = head->x()-1;
        newPosy = head->y();
    } else if (direction_ == "up") {
        newPosx = head->x();
        newPosy = head->y()-1;
    } else if (direction_ == "down") {
        newPosx = head->x();
        newPosy = head->y()+1;
    }

    const QRectF food_rect(0, 0, 1, 1);
    const QPen pen(Qt::green, 0);
    const QBrush brush(Qt::yellow);
    QGraphicsRectItem* newHead = scene_.addRect(food_rect,pen,brush);
    newHead->setPos(newPosx,newPosy);
    // When new head is inserted, the former head will become body
    wholeSnake_.at(wholeSnake_.size()-1)->setBrush(QBrush(Qt::red));

    // If new head would eat the snake itself or new head is not in valid area
    if (isValidFoodArea(newPosx,newPosy) or isGameOver()) {
        setGameOver();
    } else {
        wholeSnake_.push_back(newHead);
        updateSnake(newHead);
    }
}

void MainWindow::adjustSceneArea() {
    const QRectF area(0,0,game_width_,game_height_);
    scene_.setSceneRect(area);
    ui_.graphicsView->fitInView(area);
}

void MainWindow::adjustScore()
{
    if (timer_value_ <= 300 and timer_value_ >= 250) {
        scoreMultiplier_ = 3;
    } else if (timer_value_ < 250 and timer_value_ > 100) {
        scoreMultiplier_ = 5;
    } else if (timer_value_ <=100) {
        scoreMultiplier_ = 10;
    }
    else {
        scoreMultiplier_ = 1;
    }
}

void MainWindow::startGameTimer() {
    game_timer = new QTimer(this);
    connect(game_timer, SIGNAL(timeout()), this, SLOT(updateGameTimer()));
    game_timer->start(1000);
}

void MainWindow::updateGameTimer() {

    int temp_min = ui_.lcdNumberMin->value();
    int temp_sec = ui_.lcdNumberSec->value();
    int isTime = temp_sec-foodTime_;

    if (temp_sec%superFoodTime == 0 and isSuperFood_ == false and temp_sec != 0) {
        // Sets the superfood on
        isSuperFood_ = true;
        foodTime_ = temp_sec;
        newSuperFood();

    } else if (isEffect_ == true and abs(temp_sec-effectTime_) == effectDuration_) {
        // Reset the defaults when effect is over
        isEffect_ = false;
        timer_value_ = originalSpeed_;
        timer_.start(timer_value_);
        adjustScore();

    } else if (isEffect_ == true and effectDuration_+effectTime_>59) {
        /* Case when seconds lcd timer is reset to zero
         * so we need to calculate the effect time in different way
         * Limit time is around 55-56 when the food disappears
        */

        //how much time is left after minute changes
        effectDuration_ = effectDuration_-(59-effectTime_);

        if (effectDuration_ == temp_sec) {
            isEffect_ = false;
            timer_value_ = originalSpeed_;
            timer_.start(timer_value_);
            adjustScore();
        }

    } else if (isEffect_ == false and abs(isTime) == superFoodDuration
               and isSuperFood_ == true) {
        // No superfood was eaten in given time
        superFood_->hide();
        isSuperFood_ = false;
    }

    if (temp_sec+1 == 60) {
        ui_.lcdNumberMin->display(temp_min+1);
        ui_.lcdNumberSec->display(0);
    } else {
        ui_.lcdNumberSec->display(temp_sec+1);
    }
}

void MainWindow::updateGameScore() {
    int temp = ui_.lcdNumberScore->value();
    ui_.lcdNumberScore->display(temp+scoreMultiplier_);
}

void MainWindow::on_resetButton_clicked()
{
    delete game_timer;
    timer_.stop();
    scene_.clear();
    snake_ = nullptr;
    direction_ = "right";
    // Widget setting resets
    ui_.lcdNumberSec->display(0);
    ui_.lcdNumberMin->display(0);
    ui_.lcdNumberScore->display(0);
    ui_.playButton->setEnabled(true);
    ui_.settingsButton->setEnabled(true);
    ui_.resetButton->setDisabled(true);
    ui_.pauseButton->setDisabled(true);
    ui_.pauseButton->setText("Pause");
    ui_.diedLabel->hide();
    ui_.statusLabel->setText("Game reset");
    ui_.welcomeLabel->show();
}

void MainWindow::on_settingsButton_clicked()
{
    QWidget *settings = new Settings();
    settings->setWindowTitle("Settings");
    settings->setGeometry(200,100,600,450);
    settings->show();
}


void MainWindow::on_pauseButton_clicked()
{
    if (paused_ == false) {
        timer_.stop();
        game_timer->stop();
        paused_ = true;
        ui_.pauseButton->setText("Go");
        ui_.diedLabel->show();
        ui_.diedLabel->setText("Game paused");
    } else {
        timer_.start();
        game_timer->start();
        paused_ = false;
        ui_.pauseButton->setText("Pause");
        ui_.diedLabel->hide();
    }
}
