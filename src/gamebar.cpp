#include "gamebar.hpp"

GameBar::GameBar(int mines, QWidget *parent) : QWidget(parent) {
  timer_display = new QLCDNumber(this);
  flag_count_display = new QLCDNumber(this);
  reset_button = new QPushButton(this);

  timer_display->setDigitCount(3);
  timer_display->setMaximumHeight(55);
  flag_count_display->setDigitCount(3);
  flag_count_display->setMaximumHeight(55);

  update_timer(0);
  update_flag_count(mines);

  reset_button->setText("Quit");
  reset_button->setFixedSize(50, 50);

  connect(reset_button, &QPushButton::clicked, this,
          &GameBar::handle_reset_button);

  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->addWidget(timer_display);
  layout->addWidget(reset_button);
  layout->addWidget(flag_count_display);

  setLayout(layout);
}

void GameBar::update_timer(int seconds) {
  timer_display->display(seconds); 
}

void GameBar::update_flag_count(int flags) {
  flag_count_display->display(flags);
}

void GameBar::handle_reset_button() {
  emit reset_game(); 
}
