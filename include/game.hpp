#ifndef GAME_HPP
#define GAME_HPP

#define WINDOW_TITLE "Minesweeper"
#define CELL_SIZE 30

#include "cell.hpp"
#include "gamebar.hpp"
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QSet>
#include <QVector>

class GameWindow : public QDialog {
  Q_OBJECT

public:
  explicit GameWindow(int rows, int cols, int mines);

private:
  int rows;
  int cols;
  int mines;
  int remaining_flags;
  bool is_first_reveal;
  GameBar *gamebar;

  QGridLayout *grid_layout;
  QVBoxLayout *main_layout;
  QVector<QVector<CellBtn *>> grid_buttons;
  QVector<QVector<bool>> mine_map;
  QSet<QPair<int, int>> opening_cells;
  QTimer *timer;
  int elapsed_time;

  bool get_first_reveal();
  void set_first_reveal(bool boolean);
  void create_board();
  void make_opening(int start_row, int start_col);
  void set_mines();
  void reveal_cell(int row, int col);
  void put_flag(int row, int col);
  int count_adjacent_mines(int row, int col);
  bool check_win();

private slots:
  void update_timer();
  void reset_game();

signals:
  void gameReset();
  void gameClosed();
};

#endif // GAME_HPP
