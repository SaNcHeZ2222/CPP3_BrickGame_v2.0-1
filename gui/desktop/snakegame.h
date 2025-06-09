#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QMainWindow>
#include <QLabel>
#include "../../brick_game/snake/snakegame_back.h"


class GameFieldSnake : public QWidget {
    Q_OBJECT
public:
    GameFieldSnake(QWidget *parent = nullptr);
    ~GameFieldSnake();

};

class SnakeGame : public QMainWindow {
    Q_OBJECT

public:

    explicit SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

    void setScoreSnake();
    void setLevelSnake();
    void setSpeedSnake();

    void setHighScoreSnake(int high_score);

    void saveHighScoreSnake();

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

private:

    QString highScoreFileSnake;

    GameFieldSnake *gameField;

    int highScoreSnake;

    QLabel *highScoreLabelSnake;
    QLabel *scoreLabelSnake;
    QLabel *levelLabelSnake;
    QLabel *speedLabelSnake;

    void exitAppSnake();

    QTimer *timer;
    UserActionSnake direction; 

    void quserInput(UserActionSnake action);

    void moveSnake();
    void checkCollision();
    void timer_go();

    void loadHighScoreSnake();

    UserActionSnake translateKeyToAction(int key);
};

#endif // SNAKEGAME_H