#include "game.hpp"
#include "cell.hpp"
#include "gamebar.hpp"
#include "utils.hpp"
#include <QMessageBox>
#include <QQueue>
#include <QSet>
#include <QTimer>
#include <algorithm>
#include <random>

GameWindow::GameWindow(int rows, int cols, int mines)
    : rows(rows), cols(cols), mines(mines) {

  remaining_flags = mines;
  elapsed_time = 0;
  is_first_reveal = true;
  main_layout = new QVBoxLayout(this);
  gamebar = new GameBar(mines, this);
  grid_layout = new QGridLayout();
  timer = new QTimer(this);

  mine_map.resize(rows, QVector<bool>(cols, false));

  create_board();
  resize(cols * CELL_SIZE, rows * CELL_SIZE);
  setWindowTitle(WINDOW_TITLE);

  connect(timer, &QTimer::timeout, this, &GameWindow::update_timer);
  connect(gamebar, &GameBar::reset_game, this, &GameWindow::reset_game);

  main_layout->addWidget(gamebar);
  main_layout->addLayout(grid_layout);
  setLayout(main_layout);
}

bool GameWindow::get_first_reveal() { return is_first_reveal; }
void GameWindow::set_first_reveal(bool boolean) { is_first_reveal = boolean; }

void GameWindow::update_timer() {
  elapsed_time++;
  gamebar->update_timer(elapsed_time);
}

void GameWindow::reset_game() {
  emit gameClosed();
  close();
}

void GameWindow::create_board() {
  grid_buttons.resize(rows, QVector<CellBtn *>(cols, nullptr));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      grid_buttons[i][j] = new CellBtn(this);
      grid_buttons[i][j]->setMinimumSize(30, 30);
      grid_buttons[i][j]->set_font();
      grid_layout->setSpacing(1);
      grid_layout->setContentsMargins(0, 0, 0, 0);
      grid_layout->addWidget(grid_buttons[i][j], i, j);

      connect(grid_buttons[i][j], &CellBtn::leftClicked,
              [this, i, j]() { reveal_cell(i, j); });

      connect(grid_buttons[i][j], &CellBtn::rightClicked,
              [this, i, j]() { put_flag(i, j); });
    }
  }
}

void GameWindow::make_opening(int start_row, int start_col) {
  opening_cells.clear();

  int total_cells = rows * cols;
  int cells_to_open = total_cells * (utils::rng(12, 24) / 100.0);

  QSet<QPair<int, int>> opened_cells;
  QQueue<QPair<int, int>> queue;

  queue.enqueue(qMakePair(start_row, start_col));
  opened_cells.insert(qMakePair(start_row, start_col));

  while (!queue.isEmpty() && opened_cells.size() < cells_to_open) {
    auto cell = queue.dequeue();
    int row = cell.first;
    int col = cell.second;

    reveal_cell(row, col);

    for (int i = -1; i <= 1; ++i) {
      for (int j = -1; j <= 1; ++j) {
        int new_row = row + i;
        int new_col = col + j;
        if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols) {
          QPair<int, int> new_cell = qMakePair(new_row, new_col);
          if (!opened_cells.contains(new_cell)) {
            opened_cells.insert(new_cell);
            queue.enqueue(new_cell);
          }
        }
      }
    }
  }

  opening_cells = opened_cells;

  for (const auto &cell : opened_cells) {
    mine_map[cell.first][cell.second] = false;
  }
}

void GameWindow::set_mines() {
  QVector<QPair<int, int>> possible_positions;

  // collect all possible positions excluding the opening cells
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      QPair<int, int> cell = qMakePair(i, j);
      if (!opening_cells.contains(cell)) {
        possible_positions.append(cell);
        grid_buttons[cell.first][cell.second]->unflag();
      }
    }
  }

  // shuffle the possible positions
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(possible_positions.begin(), possible_positions.end(), g);

  // place mines in the first 'mines' positions
  for (int i = 0; i < mines; ++i) {
    int row = possible_positions[i].first;
    int col = possible_positions[i].second;
    mine_map[row][col] = true;
    grid_buttons[row][col]->set_icon(STRAIGHTBOMB_IMG_PATH);
  }

  // reveal opening cells
  for (const auto &cell : opening_cells) {
    reveal_cell(cell.first, cell.second);
  }
}

void GameWindow::reveal_cell(int row, int col) {
  if (grid_buttons[row][col]->text() != "")
    return;

  if (get_first_reveal()) {
    set_first_reveal(false);
    timer->start(1000);

    make_opening(row, col);
    set_mines();

    return;
  }

  if (mine_map[row][col] == true) {
    timer->stop();

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        grid_buttons[i][j]->disable();
        if (mine_map[i][j] == true && !grid_buttons[i][j]->is_flagged()) {
          grid_buttons[i][j]->set_icon(STRAIGHTBOMB_IMG_PATH);
        } else if (mine_map[i][j] == true && grid_buttons[i][j]->is_flagged()) {
          grid_buttons[i][j]->set_icon(MISPLACED_BOMB_IMG_PATH);
        }
      }
    }
    grid_buttons[row][col]->set_icon(REDBOMB_IMG_PATH);
  } else {
    int adjacent_mines = count_adjacent_mines(row, col);

    switch (adjacent_mines) {
    case 0:
      grid_buttons[row][col]->set_font(FontColor::BLACK);
      break;
    case 1:
      grid_buttons[row][col]->set_font(FontColor::BLUE);
      break;
    case 2:
      grid_buttons[row][col]->set_font(FontColor::GREEN);
      break;
    case 3:
      grid_buttons[row][col]->set_font(FontColor::LIGHTRED);
      break;
    case 4:
      grid_buttons[row][col]->set_font(FontColor::DARKBLUE);
      break;
    case 5:
      grid_buttons[row][col]->set_font(FontColor::DARKRED);
      break;
    case 6:
      grid_buttons[row][col]->set_font(FontColor::AQUA);
      break;
    case 7:
      grid_buttons[row][col]->set_font(FontColor::PURPLE);
      break;
    case 8:
      grid_buttons[row][col]->set_font(FontColor::YELLOWISH);
      break;
    case 9:
      grid_buttons[row][col]->set_font(FontColor::AMETHYST);
      break;
    }

    grid_buttons[row][col]->setText(QString::number(adjacent_mines));
    grid_buttons[row][col]->disable();

    if (check_win()) {
      timer->stop();
      QMessageBox::information(this, "Victory!", "Congrats, you won!");

      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
          if (grid_buttons[i][j]->is_flagged())
            grid_buttons[i][j]->disable();
        }
      }
    }
  }
}

void GameWindow::put_flag(int row, int col) {
  if (is_first_reveal)
    return;

  if (grid_buttons[row][col]->is_flagged()) {
    remaining_flags++;
    gamebar->update_flag_count(remaining_flags);

    grid_buttons[row][col]->remove_icon();
    grid_buttons[row][col]->unflag();
    connect(grid_buttons[row][col], &CellBtn::leftClicked, this,
            [this, row, col]() { reveal_cell(row, col); });
  } else if (remaining_flags > 0) {
    remaining_flags--;
    gamebar->update_flag_count(remaining_flags);

    grid_buttons[row][col]->set_icon(FLAG_IMG_PATH);
    grid_buttons[row][col]->flag();
    disconnect(grid_buttons[row][col], &CellBtn::leftClicked, nullptr, nullptr);
  }
}

int GameWindow::count_adjacent_mines(int row, int col) {
  int count = 0;

  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; j++) {
      int new_row = row + i;
      int new_col = col + j;
      if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols) {
        if (mine_map[new_row][new_col]) {
          count++;
        }
      }
    }
  }

  return count;
}

bool GameWindow::check_win() {
  bool all_flags_used = (remaining_flags == 0);

  int revealed_count = 0;
  for (const auto &row : grid_buttons) {
    for (CellBtn *btn : row) {
      if (!btn->text().isEmpty() && !btn->is_flagged()) {
        revealed_count++;
      }
    }
  }

  bool all_revealed = (revealed_count == rows * cols - mines);

  return all_flags_used && all_revealed;
}

/*

'mine_map[row][col] == true' is easier to read

*/
