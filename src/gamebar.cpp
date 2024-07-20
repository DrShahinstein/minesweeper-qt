#include "gamebar.hpp"

GameBar::GameBar(int mines, QWidget *parent) : QWidget(parent) {
  timer_display = new QLCDNumber(this);
  mine_count_display = new QLCDNumber(this);
  reset_button = new QPushButton(this);

  timer_display->setDigitCount(3);
  timer_display->setMaximumHeight(55);
  mine_count_display->setDigitCount(3);
  mine_count_display->setMaximumHeight(55);

  update_timer(0);
  update_mine_count(mines);

  reset_button->setText("Quit");
  reset_button->setFixedSize(50, 50);

  connect(reset_button, &QPushButton::clicked, this,
          &GameBar::handle_reset_button);

  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->addWidget(timer_display);
  layout->addWidget(reset_button);
  layout->addWidget(mine_count_display);

  setLayout(layout);
}

void GameBar::update_timer(int seconds) {
  timer_display->display(seconds); 
}

void GameBar::update_mine_count(int mines) {
  mine_count_display->display(mines);
}

void GameBar::handle_reset_button() {
  emit reset_game(); 
}
