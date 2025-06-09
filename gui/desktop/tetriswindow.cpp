// tetriswindow.cpp
#include "tetriswindow.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QGraphicsRectItem>
#include <QMessageBox>
#include <QTextStream>
#include <QWidget>
extern "C" {
#include "../../brick_game/tetris/tetris_back_desktop.h"
}

GameField::GameField(QWidget *parent) : QWidget(parent) {
  setFixedSize(202, 401);
}

GameField::~GameField() {}

QColor getColor(int numColor) {
  QColor res;
  if (numColor == 1)
    res = QColor(165, 48, 48);
  else if (numColor == 2)
    res = QColor(168, 202, 88);
  else if (numColor == 3)
    res = QColor(222, 158, 65);
  else if (numColor == 4)
    res = QColor(79, 143, 186);
  else if (numColor == 5)
    res = QColor(223, 132, 165);
  else if (numColor == 6)
    res = QColor(232, 193, 112);
  else
    res = QColor(192, 203, 220);
  return res;
}

void GameField::paintEvent(QPaintEvent *e) {
  QPainter painter;
  painter.begin(this);  // Начало рисования
  painter.drawRect(0, 0, 202, 401);

  int blockSize = 20;  // Размер каждого блока
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (getInfoGame().field[i][j] != 0) {
        QColor color = getColor(getInfoGame().field[i][j] - 1);
        QBrush brush(color);
        painter.setBrush(brush);
        painter.drawRect(j * blockSize, i * blockSize, blockSize, blockSize);
      }
    }
  }
}

TetrisWindow::TetrisWindow(QWidget *parent)
    : QMainWindow(parent), highScore(0), highScoreFile("highscore.txt") {
  gameField = new GameField();

  nextPieceFrame = new QFrame(this);
  nextPieceScene = new QGraphicsScene(this);
  nextPieceView = new QGraphicsView(nextPieceScene, this);
  nextPieceView->setMinimumSize(100, 100);

  highScoreLabel = new QLabel(this);
  scoreLabel = new QLabel("Score: 0", this);
  levelLabel = new QLabel("Level: 1", this);
  speedLabel = new QLabel("Speed: 200", this);
  nextPieceLabel = new QLabel("Next Piece:", this);

  loadHighScore();

  QVBoxLayout *infoLayout = new QVBoxLayout;
  infoLayout->addWidget(highScoreLabel);
  infoLayout->addWidget(scoreLabel);
  infoLayout->addWidget(levelLabel);
  infoLayout->addWidget(speedLabel);
  infoLayout->addWidget(nextPieceLabel);
  infoLayout->addWidget(nextPieceView);
  infoLayout->addStretch();

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(gameField);

  mainLayout->addLayout(infoLayout);

  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(mainLayout);

  setCentralWidget(centralWidget);

  setWindowTitle("Tetris Window");

  updateInfoGameScore(0);
  setScore();

  updateInfoGameLevel(1);
  setLevel();

  updateInfoGameSpeed(150);
  setSpeed();

  updateInfoGameNext(getRandNum());

  addFigure(getInfoGame().current);

  updateFlagInfoGame(1);
  updateFlagInfoStatus(1);

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &TetrisWindow::timer_go);
  timer->start(1500);
}

void TetrisWindow::changeTimerInterval(int newInterval) {
  timer->setInterval(newInterval);
}

void TetrisWindow::returnPauseWindow() {
  QMessageBox messageBox;
  messageBox.setText("Уведомление");
  messageBox.setInformativeText(
      "Вы поставили игру на паузу, нажмите ПРОБЕЛ, чтобы продолжить");
  messageBox.setStandardButtons(QMessageBox::Ok);
  messageBox.setDefaultButton(QMessageBox::Ok);
  messageBox.exec();
}

void TetrisWindow::keyPressEvent(QKeyEvent *event) {
  UserAction_t action = Action;

  if (event->key() == Qt::Key_P) action = Pause;
  if (event->key() == Qt::Key_Space) action = Start;
  if (event->key() == Qt::Key_Q) action = Terminate;

  if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) action = Left;
  if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
    action = Right;
  if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W) action = Up;
  if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S) action = Down;

  userInput(action);
  if (action == Pause) returnPauseWindow();
  repaintNextFigure();
  gameField->repaint();
}

void TetrisWindow::repaintNextFigure() {
  // Отрисовка следующей фигуры
  nextPieceScene->clear();
  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x = figures[getInfoGame().next][0][i][0];
    int y = figures[getInfoGame().next][0][i][1];

    QColor color = getColor(getInfoGame().next);
    QBrush brush(color);
    QGraphicsRectItem *rect = nextPieceScene->addRect(x * 20, y * 20, 20, 20);
    rect->setBrush(QBrush(color));
  }
}

void TetrisWindow::exitApp() {
  QApplication *app = static_cast<QApplication *>(QApplication::instance());
  if (app) {
    app->exit();
  }
}

void TetrisWindow::timer_go() {
  if (getFlagInfo().flagGo == -1) {
    exitApp();
  }

  if (getFlagInfo().flagGo == 0) {
    clearTable();
    gameField->repaint();

    updateGameInfoPauseTetris(1);

    updateFlagInfoStatus(0);

    updateInfoGameScore(0);
    setScore();

    updateInfoGameLevel(1);
    setLevel();

    updateInfoGameSpeed(150);
    setSpeed();

    QMessageBox messageBox;
    messageBox.setText("Уведомление");
    messageBox.setInformativeText(
        "Вы проиграли, нажмите пробел, чтобы начать заново");
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.exec();

    updateFlagInfoGo(1);
    updateFlagInfoGame(1);
  }

  if (getInfoGame().pause != 1 && getFlagInfo().flagGo != 0) {
    if (getFlagInfo().flagAddNewFigure == 1 && getFlagInfo().flagGame == 1 &&
        getFlagInfo().flagGo != -1) {
      int numberNewFigure = getInfoGame().next;
      checkLine();
      addFigure(numberNewFigure);
      updateInfoGameNext(getRandNum());
      updateFlagNewFigure(0);
    }

    // Падение текущей фигруы вниз каждые 2 секунды
    shiftCurrent(Down);

    changeTimerInterval(2000 - getInfoGame().speed);

    // Перерисовка игрового поля
    gameField->repaint();
    repaintNextFigure();
    setScore();
    setLevel();
    setSpeed();
  }
}

TetrisWindow::~TetrisWindow() {}

void TetrisWindow::setScore() {
  scoreLabel->setText(QString("Score: %1").arg(getInfoGame().score));
  if (getInfoGame().score > getInfoGame().high_score) {
    setHighScore(getInfoGame().score);
  }
}

void TetrisWindow::setLevel() {
  levelLabel->setText(QString("Level: %1").arg(getInfoGame().level));
}

void TetrisWindow::setSpeed() {
  speedLabel->setText(QString("Speed: %1").arg(getInfoGame().speed));
}

void TetrisWindow::setHighScore(int high_score) {
  highScoreLabel->setText(QString("High Score: %1").arg(high_score));
  updateGameInfoHighScoreTetris(getInfoGame().score);
  saveHighScore();
}

void TetrisWindow::saveHighScore() {
  QFile file(highScoreFile);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    out << getInfoGame().high_score;
    file.close();
  }
}

void TetrisWindow::loadHighScore() {
  QFile file(highScoreFile);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    in >> highScore;
    file.close();
  }
  highScoreLabel->setText(QString("High Score: %1").arg(highScore));
  updateInfoGameHighScore(highScore);
}
