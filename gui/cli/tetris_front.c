#include "tetris_front.h"

extern void updateGameInfoScore(int newScore);
extern void updateGameInfoHighScore(int newHighScore);

static WINDOW *win;

static WINDOW *highScore;

static WINDOW *Score;

static WINDOW *Level;

static WINDOW *Speed;

static WINDOW *nextFigure;

void showField(WINDOW *win) {
  GameInfo_t infoGame = updateCurrentState();

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      chtype symbol = ' ';
      if (infoGame.field[i][j] != 0) {
        symbol = '#';
      }
      mvwaddch(win, i + 1, j + 1,
               symbol | COLOR_PAIR(infoGame.field[i][j] + 1));
    }
  }
}

void freshWindows() {
  wrefresh(win);
  wrefresh(highScore);
  wrefresh(Score);
  wrefresh(Level);
  wrefresh(Speed);
  wrefresh(nextFigure);
}

void paintSpeed() {
  GameInfo_t infoGame = getInfoGame();
  Speed = newwin(3, 20, 9, 25);
  box(Speed, 0, 0);
  mvwprintw(Speed, 1, 1, "Speed");
  mvwprintw(Speed, 1, 14, "%d", infoGame.speed * infoGame.level);
}

void paintSpeedSnake() {
  GameInfoSnake infoGame = getGameInfoSnake();
  Speed = newwin(3, 20, 9, 25);
  box(Speed, 0, 0);
  mvwprintw(Speed, 1, 1, "Speed");
  mvwprintw(Speed, 1, 14, "%d", infoGame.speed * infoGame.level);
}

void paintNextFigure() {
  int statusGame = updateStatusGame();
  GameInfo_t infoGame = getInfoGame();

  nextFigure = newwin(10, 20, 12, 25);
  box(nextFigure, 0, 0);

  if (statusGame == 1 || statusGame == 2) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      int x = figures[infoGame.next][0][i][0];
      int y = figures[infoGame.next][0][i][1];
      mvwaddch(nextFigure, x + 4, y + 6, '#' | COLOR_PAIR(infoGame.next + 2));
    }
  }
}

void paintLevel() {
  GameInfo_t infoGame = getInfoGame();
  Level = newwin(3, 20, 6, 25);
  box(Level, 0, 0);
  mvwprintw(Level, 1, 1, "Level");
  mvwprintw(Level, 1, 14, "%d", infoGame.level);
}

void paintLevelSnake() {
  GameInfoSnake infoGame = getGameInfoSnake();
  Level = newwin(3, 20, 6, 25);
  box(Level, 0, 0);
  mvwprintw(Level, 1, 1, "Level");
  mvwprintw(Level, 1, 14, "%d", infoGame.level);
}

void paintScore() {
  GameInfo_t infoGame = getInfoGame();

  Score = newwin(3, 20, 3, 25);
  box(Score, 0, 0);
  mvwprintw(Score, 1, 1, "Score");
  mvwprintw(Score, 1, 14, "%d", infoGame.score);
}

void paintScoreSnake() {
  GameInfoSnake infoGame = getGameInfoSnake();

  Score = newwin(3, 20, 3, 25);
  box(Score, 0, 0);
  mvwprintw(Score, 1, 1, "Score");
  mvwprintw(Score, 1, 14, "%d", infoGame.score);
}

void paintHighScore() {
  highScore = newwin(3, 20, 0, 25);
  box(highScore, 0, 0);
  mvwprintw(highScore, 1, 1, "High Score:");
  FILE *file = NULL;
  if (updateStatusGame() != -1) {
    if (updateStatusGame() < 0)
      file = fopen("gui/cli/highScoreSnake.txt", "r");
    else
      file = fopen("gui/cli/highScore.txt", "r");
  }

  int highScoreDigit;
  if (file != NULL) {
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    highScoreDigit = atoi(buffer);
    fclose(file);
  } else
    highScoreDigit = 0;
  mvwprintw(highScore, 1, 14, "%d", highScoreDigit);
}

void paintHighScoreSnake() {
  highScore = newwin(3, 20, 0, 25);
  box(highScore, 0, 0);
  mvwprintw(highScore, 1, 1, "High Score:");
  FILE *file = NULL;
  if (getFlagInfoSnake().statusGame != -1) {
    file = fopen("gui/cli/highScoreSnake.txt", "r");

    int highScoreDigit;
    if (file != NULL) {
      char buffer[256];
      fgets(buffer, sizeof(buffer), file);

      highScoreDigit = atoi(buffer);
      fclose(file);
    } else
      highScoreDigit = 0;
    mvwprintw(highScore, 1, 14, "%d", highScoreDigit);
  }
}

void initStartWindowSnake() {
  int statusGame = getFlagInfoSnake().statusGame;

  win = newwin(22, 22, 0, 0);

  refresh();

  box(win, 0, 0);
  if (statusGame == -1) {
    mvwprintw(win, 8, 1, "   Press 1");
    mvwprintw(win, 9, 1, "   to play Tetris");

    mvwprintw(win, 11, 1, "   Press 2 ");
    mvwprintw(win, 12, 1, "   to play Snake");
  } else if (statusGame == -3) {
    mvwprintw(win, 8, 1, "   You Win");

    mvwprintw(win, 9, 1, "   Press space");
    mvwprintw(win, 10, 1, "   to start");
  } else if (statusGame == -2) {
    mvwprintw(win, 8, 1, "   Game Over");

    mvwprintw(win, 9, 1, "   Press space");
    mvwprintw(win, 10, 1, "   to start");
  }
  paintHighScoreSnake();

  paintScore();
  paintLevel();
  paintSpeed();

  freshWindows();
}

void initStartWindow() {
  int statusGame = updateStatusGame();

  win = newwin(22, 22, 0, 0);

  refresh();

  box(win, 0, 0);
  if (statusGame == -1) {
    mvwprintw(win, 8, 1, "   Press 1");
    mvwprintw(win, 9, 1, "   to play Tetris");

    mvwprintw(win, 11, 1, "   Press 2 ");
    mvwprintw(win, 12, 1, "   to play Snake");
  } else if (statusGame == -2) {
    mvwprintw(win, 8, 1, "   You Win");

    mvwprintw(win, 9, 1, "   Press space");
    mvwprintw(win, 10, 1, "   to start");
  } else if (statusGame == -3) {
    mvwprintw(win, 8, 1, "   Game Over");

    mvwprintw(win, 9, 1, "   Press space");
    mvwprintw(win, 10, 1, "   to start");
  }

  else if (statusGame == 0) {
    mvwprintw(win, 8, 1, "   Press space");
    mvwprintw(win, 9, 1, "   to start");
  } else if (statusGame == 1) {
    showField(win);
  } else if (statusGame == 2) {
    mvwprintw(win, 8, 1, "   Pause");
    mvwprintw(win, 10, 1, "   Press space");
    mvwprintw(win, 11, 1, "   to continue");
  } else if (statusGame == 3) {
    mvwprintw(win, 8, 1, "   Game Over");
    mvwprintw(win, 10, 1, "   Press space");
    mvwprintw(win, 11, 1, "   to start");
  }

  // if (getGameType() == 0)
  paintHighScore();
  // else

  //   paintHighScoreSnake();

  paintScore();
  paintLevel();
  paintSpeed();
  paintNextFigure();

  freshWindows();
}

void drawSnake() {
  win = newwin(22, 22, 0, 0);
  box(win, 0, 0);

  refresh();

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      chtype symbol = ' ';
      mvwaddch(win, i + 1, j + 1, symbol | COLOR_PAIR(COLOR_WHITE));
    }
  }
  chtype symbol = '#';

  for (int i = 0; i < getGameInfoSnake().snakeSize; i++) {
    int x = getGameInfoSnake().snakeX[i];
    int y = getGameInfoSnake().snakeY[i];

    mvwaddch(win, y + 1, x + 1, symbol | COLOR_PAIR(COLOR_GREEN));
  }
  mvwaddch(win, getGameInfoSnake().foodY + 1, getGameInfoSnake().foodX + 1,
           symbol | COLOR_PAIR(COLOR_BLACK));

  updateHighScoreSnake();
  paintHighScoreSnake();
  paintScoreSnake();
  paintLevelSnake();
  paintSpeedSnake();

  freshWindows();
}

WINDOW *updateHighScoreFront() { return highScore; }

WINDOW *updateLevel() { return Level; }

WINDOW *updateScore() { return Score; }

WINDOW *updateSpeed() { return Speed; }

WINDOW *updateNextFigure() { return nextFigure; }

WINDOW *updateWin() { return win; }
