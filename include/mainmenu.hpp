#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "game.hpp"
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#define MENU_WINDOW_TITLE "Select Game Variant"
#define MENU_FIXED_WIDTH 900
#define MENU_FIXED_HEIGHT 600

enum GameVariants {
  _16x16_40,
  _16x16_50,
  _16x16_60,
  _20x20_75,
  _20x20_90,
  _20x20_120,
  _24x24_140,
  _24x24_160,
  _24x24_180,
};

class MainMenu : public QDialog {
  Q_OBJECT

public:
  explicit MainMenu(QWidget *parent = nullptr);
  GameVariants get_variant();

private:
  void setup_layout();
  void select_variant();

  GameVariants variant;
  GameWindow *game_window;

  struct ButtonInfo {
    QString size_label;
    QString mine_label;
  };
};

#endif // MAINMENU_HPP
