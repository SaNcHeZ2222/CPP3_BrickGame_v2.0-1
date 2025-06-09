#include "snakegame.h"

extern "C" {
#include "../../brick_game/snake/snakegame_back.h"
}

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFrame>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QTextStream>
#include <QTimer>
#include <QVBoxLayout>
#include <QVector>

GameFieldSnake::GameFieldSnake(QWidget *parent) : QWidget(parent) {
  setFixedSize(201, 401);
}

GameFieldSnake::~GameFieldSnake() {}

SnakeGame::SnakeGame(QWidget *parent)
    : QMainWindow(parent), highScoreFileSnake("highscoreSnake.txt") {
  gameField = new GameFieldSnake();

  highScoreLabelSnake = new QLabel(this);
  scoreLabelSnake = new QLabel("Score: 0", this);
  levelLabelSnake = new QLabel("Level: 1", this);
  speedLabelSnake = new QLabel("Speed: 200", this);

  loadHighScoreSnake();

  QVBoxLayout *infoLayout = new QVBoxLayout;
  infoLayout->addWidget(highScoreLabelSnake);
  infoLayout->addWidget(scoreLabelSnake);
  infoLayout->addWidget(levelLabelSnake);
  infoLayout->addWidget(speedLabelSnake);

  infoLayout->addStretch();

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(gameField);

  mainLayout->addLayout(infoLayout);

  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(mainLayout);

  setCentralWidget(centralWidget);

  setWindowTitle("Tetris Window");

  direction = LeftSnake;

  startSettingSnake();

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &SnakeGame::timer_go);
  timer->start(1500 - getGameInfoSnake().speed);
}

SnakeGame::~SnakeGame() {}

void SnakeGame::setScoreSnake() {
  scoreLabelSnake->setText(QString("Score: %1").arg(getGameInfoSnake().score));
  if (getGameInfoSnake().score > getGameInfoSnake().high_score) {
    updateGameInfoHighScore(getGameInfoSnake().score);
    saveHighScoreSnake();
    setHighScoreSnake(getGameInfoSnake().score);
  }
}

void SnakeGame::setHighScoreSnake(int high_score) {
  highScoreLabelSnake->setText(QString("High Score: %1").arg(high_score));
}

void SnakeGame::saveHighScoreSnake() {
  QFile file(highScoreFileSnake);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    out << getGameInfoSnake().high_score;
    file.close();
  }
}

void SnakeGame::setLevelSnake() {
  levelLabelSnake->setText(QString("Level: %1").arg(getGameInfoSnake().level));
}

void SnakeGame::setSpeedSnake() {
  speedLabelSnake->setText(QString("Speed: %1").arg(getGameInfoSnake().speed));
}

void SnakeGame::loadHighScoreSnake() {
  QFile file(highScoreFileSnake);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    in >> highScoreSnake;
    file.close();
  }
  highScoreLabelSnake->setText(QString("High Score: %1").arg(highScoreSnake));
  updateGameInfoHighScore(highScoreSnake);
}

void SnakeGame::exitAppSnake() {
  QApplication *app = static_cast<QApplication *>(QApplication::instance());
  if (app) {
    app->exit();
  }
}

void SnakeGame::keyPressEvent(QKeyEvent *event) {
  UserActionSnake action = translateKeyToAction(event->key());
  if (action == TerminateSnake) {
    exitAppSnake();
  }

  if ((action == UpSnake || action == DownSnake || action == LeftSnake ||
       action == RightSnake) &&
      getFlagInfoSnake().statusGame == 1) {
    direction = action;
  }

  userInputSnake(action);
}

void SnakeGame::paintEvent(QPaintEvent *e) {
  QPainter painter;
  painter.begin(this);

  painter.drawRect(0, 0, 201, 401);

  for (int i = 0; i < getGameInfoSnake().snakeSize; i++) {
    int x = getGameInfoSnake().snakeX[i];
    int y = getGameInfoSnake().snakeY[i];

    QBrush brush(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(x * 20, y * 20, 20, 20);
  }

  QBrush brush(Qt::red);
  painter.setBrush(brush);
  painter.drawRect(getGameInfoSnake().foodX * 20, getGameInfoSnake().foodY * 20,
                   20, 20);
}

void SnakeGame::timer_go() {
  if (getFlagInfoSnake().statusGame == 1) {
    moveSnakeBack(direction);
    checkCollision();

    setScoreSnake();
    setLevelSnake();
    setHighScoreSnake(getGameInfoSnake().high_score);

    repaint();
  }
}

void SnakeGame::checkCollision() {
  checkCollisionBack();

  if (getFlagInfoSnake().flagGame == 0) {
    QMessageBox messageBox;
    messageBox.setText("Мне жаль! Вы проиграли!");
    messageBox.setInformativeText("Нажмите ПРОБЕЛ, чтобы сыграть ещё раз");
    messageBox.exec();
    startSettingSnake();
    direction = LeftSnake;
    updateFlagInfoStatusGameSnake(0);
  } else if (getFlagInfoSnake().flagGame == 2) {
    QMessageBox messageBox;
    messageBox.setText("Поздравляю! Вы победили!");
    messageBox.setInformativeText("Нажмите ПРОБЕЛ, чтобы сыграть ещё раз");
    messageBox.exec();
    startSettingSnake();
    direction = LeftSnake;
    updateFlagInfoStatusGameSnake(0);
  }
}

// void SnakeGame::updateScore() {
//     score++;
//     if (score > level * 10) {
//         level++;
//         speed -= 50;
//         timer->setInterval(1500 - speed);
//     }
// }

UserActionSnake SnakeGame::translateKeyToAction(int key) {
  switch (key) {
    case Qt::Key_Up:
      return UpSnake;
    case Qt::Key_W:
      return UpSnake;

    case Qt::Key_Down:
      return DownSnake;
    case Qt::Key_S:
      return DownSnake;

    case Qt::Key_Left:
      return LeftSnake;
    case Qt::Key_A:
      return LeftSnake;

    case Qt::Key_Right:
      return RightSnake;
    case Qt::Key_D:
      return RightSnake;

    case Qt::Key_Q:
      return TerminateSnake;

    case Qt::Key_P:
      return PauseSnake;

    case Qt::Key_Space:
      return StartSnake;

    default:
      return ActionSnake;
  }
}