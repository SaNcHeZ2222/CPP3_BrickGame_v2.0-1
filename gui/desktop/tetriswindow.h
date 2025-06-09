// tetriswindow.h
#ifndef TETRISWINDOW_H
#define TETRISWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QVector>

#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QPainter>

class GameField : public QWidget {
    Q_OBJECT
public:
    GameField(QWidget *parent = nullptr);
    ~GameField();

protected:
    void paintEvent(QPaintEvent *e) override;
};

#endif // GAMEFIELD_H


class TetrisWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TetrisWindow(QWidget *parent = nullptr);
    ~TetrisWindow();

    void setScore();
    void setLevel();
    void setSpeed();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:

    GameField *gameField;

    QFrame *nextPieceFrame;
    QGraphicsScene *nextPieceScene;
    QGraphicsView *nextPieceView;

    QLabel *highScoreLabel;
    QLabel *scoreLabel;
    QLabel *levelLabel;
    QLabel *speedLabel;
    QLabel *nextPieceLabel;

    int highScore;
    QString highScoreFile;

    void setHighScore(int high_score);
    void saveHighScore();
    void loadHighScore();
    // void updateGameBoard();
    // void spawnSquare();

    QTimer *timer;

private slots:
  void timer_go();
  void repaintNextFigure();
  void exitApp();
  void changeTimerInterval(int newInterval);
  void returnPauseWindow();

};

#endif // TETRISWINDOW_H
