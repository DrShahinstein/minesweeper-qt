#include "game.hpp"
#include "mainmenu.hpp"
#include <QApplication>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  while (true) {
    MainMenu menu;

    if (menu.exec() == QDialog::Accepted) {
      GameVariants variant = menu.get_variant();
      int rows, cols, mines;

      switch (variant) {
      case _16x16_40:
        rows  = 16;
        cols  = 16;
        mines = 40;
        break;
      case _16x16_50:
        rows  = 16;
        cols  = 16;
        mines = 50;
        break;
      case _16x16_60:
        rows  = 16;
        cols  = 16;
        mines = 60;
        break;
      case _20x20_75:
        rows  = 20;
        cols  = 20;
        mines = 75;
        break;
      case _20x20_90:
        rows  = 20;
        cols  = 20;
        mines = 90;
        break;
      case _20x20_120:
        rows  = 20;
        cols  = 20;
        mines = 120;
        break;
      case _24x24_140:
        rows  = 24;
        cols  = 24;
        mines = 140;
        break;
      case _24x24_160:
        rows  = 24;
        cols  = 24;
        mines = 160;
        break;
      case _24x24_180:
        rows  = 24;
        cols  = 24;
        mines = 180;
        break;
      default:
        rows  = 16;
        cols  = 16;
        mines = 40;
        break;
      }

      GameWindow game(rows, cols, mines);

      QObject::connect(&game, &GameWindow::gameClosed,
                       [&app, &menu]() { menu.show(); });

      game.exec();
    } else {
      break;
    }
  }

  return 0; // app.exec() causes the program not to terminate
}
