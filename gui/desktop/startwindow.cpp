#include "startwindow.h"

StartWindow::StartWindow(QWidget *parent) : QMainWindow(parent) {
  mainGameButton = new QPushButton("Игра Змейка", this);
  tetrisGameButton = new QPushButton("Игра Тетрис", this);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(mainGameButton);
  layout->addWidget(tetrisGameButton);

  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);

  connect(mainGameButton, &QPushButton::clicked, this,
          &StartWindow::openMainGame);
  connect(tetrisGameButton, &QPushButton::clicked, this,
          &StartWindow::openTetrisGame);

  setWindowTitle("Start Window");
}

StartWindow::~StartWindow() {}

void StartWindow::openMainGame() {
  SnakeGame *snakeGame = new SnakeGame();
  updateGameType(0);
  snakeGame->show();
  this->close();
}

void StartWindow::openTetrisGame() {
  TetrisWindow *tetrisWindow = new TetrisWindow();
  updateGameType(1);
  tetrisWindow->show();
  this->close();
}
