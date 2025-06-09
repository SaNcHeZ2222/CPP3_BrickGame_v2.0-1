#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "snakegame.h"
#include "tetriswindow.h"

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void openMainGame();
    void openTetrisGame();

private:
    QPushButton *mainGameButton;
    QPushButton *tetrisGameButton;
};

#endif // STARTWINDOW_H
