#include "../../gui/cli/tetris_front.h"
#include "tetris_back.h"

void updateAddInfo() {}

void setSetting() {
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  start_color();
  initColor();
}

void setStartSetting() {
  updateInfoGameScore(0);

  updateInfoGameLevel(1);

  updateInfoGameSpeed(200);

  updateInfoGameNext(getRandNum());

  updateInfoGameCurrent(getRandNum());
}

void updateFlagFoZero() {
  updateInfoFlagGame(0);

  updateInfoStatusGame(3);

  updateInfoflagGo(1);
  clearTable();
  updateInfoGameScore(0);

  updateInfoGameLevel(1);

  updateInfoGameSpeed(200);
}

void delAllWin(WINDOW *highScore, WINDOW *Level, WINDOW *Score, WINDOW *Speed,
               WINDOW *nextFigure, WINDOW *win) {
  delwin(win);
  delwin(highScore);
  delwin(Score);
  delwin(Level);
  delwin(Speed);
  delwin(nextFigure);
}

void launchTetris() {}

int main() {
  initscr();
  setSetting();

  int fpsCount = 0;

  GameInfo_t infoGame = updateCurrentState();
  WINDOW *highScore = updateHighScoreFront();
  WINDOW *Level = updateLevel();
  WINDOW *Score = updateScore();
  WINDOW *Speed = updateSpeed();
  WINDOW *nextFigure = updateNextFigure();
  WINDOW *win = updateWin();
  setStartSetting();
  int flagGo = updateFlagGo();
  int flagGame, statusGame;

  while (flagGo != -1) {
    initStartWindow();
    halfdelay(1);
    int key = getch();
    userInput(translateKeyToAction(key));
    if (key == 49) {
      updateInfoStatusGame(0);
      updateGameType(1);
      break;

    } else if (key == 50) {
      updateGameType(0);
      updateInfoStatusGame(-2);
      break;
    }
  }

  if (updateStatusGame() == 0) {
    while (flagGo != -1) {
      infoGame = updateCurrentState();
      flagGo = updateFlagGo();
      flagGame = updateFlagGame();
      statusGame = updateStatusGame();

      initStartWindow();
      if (flagGo == 0) {
        updateFlagFoZero();
      }
      halfdelay(1);
      int key = getch();
      if (key == 49) updateInfoStatusGame(0);
      userInput(translateKeyToAction(key));
      if (fpsCount >= 7) {
        fpsCount = 0;
        if (flagGame == 1 && statusGame == 1) shiftCurrent(Down);
      }
      usleep(50000 - infoGame.speed * infoGame.level);
      fpsCount++;
    }
    delAllWin(highScore, Level, Score, Speed, nextFigure, win);
    endwin();
  } else {
    startSettingSnake();

    updateDirection(LeftSnake);

    while (flagGo != -1) {
      flagGo = getFlagInfoSnake().flagGo;
      flagGame = getFlagInfoSnake().flagGame;
      statusGame = getFlagInfoSnake().statusGame;

      int key = getch();
      UserActionSnake action = translateKeyToActionSnake(key);
      if (action == TerminateSnake) break;

      userInputSnake(action);

      if (getFlagInfoSnake().flagGame == 0 ||
          getFlagInfoSnake().statusGame == -3) {
        if (getGameInfoSnake().snakeSize == winDigit)
          updateInfoStatusGame(-2);
        else
          updateInfoStatusGame(-3);

        initStartWindowSnake();
        if (action == StartSnake) {
          startSettingSnake();
          updateInfoStatusGame(0);
          updateDirection(LeftSnake);
        }
      } else if (getFlagInfoSnake().flagGame != 0 &&
                 getFlagInfoSnake().flagGo != 5) {
        if ((action == UpSnake || action == DownSnake || action == LeftSnake ||
             action == RightSnake) &&
            getFlagInfoSnake().statusGame == 1) {
          updateDirection(action);
        }

        moveSnakeBack(getDirection());
        checkCollisionBackConsole();

        setScoreSnake(getGameInfoSnake().score);
        setLevelSnake(getGameInfoSnake().level);
        setHighScoreSnake(getGameInfoSnake().high_score);

        drawSnake();
        updateAddInfo();
        usleep(50000 - infoGame.speed * infoGame.level);
      }
    }
    delAllWin(highScore, Level, Score, Speed, nextFigure, win);
    endwin();
  }

  return 0;
}
