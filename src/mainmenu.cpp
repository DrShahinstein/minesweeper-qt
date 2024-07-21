#include "mainmenu.hpp"

MainMenu::MainMenu(QWidget *parent) : QDialog(parent) {
  setup_layout();
}

void MainMenu::setup_layout() {
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  QGridLayout *grid_layout = new QGridLayout();

  QVector<ButtonInfo> button_infos = {
      {"16x16", "40 Mines"},  {"16x16", "50 Mines"},  {"16x16", "60 Mines"},
      {"20x20", "75 Mines"},  {"20x20", "90 Mines"},  {"20x20", "120 Mines"},
      {"24x24", "140 Mines"}, {"24x24", "160 Mines"}, {"24x24", "180 Mines"}};

  QFont font;
  font.setPointSize(16);

  for (int i = 0; i < button_infos.size(); ++i) {
    QPushButton *button = new QPushButton(this);

    button->setFocusPolicy(Qt::NoFocus);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setMinimumSize(200, 100);
    button->setCursor(QCursor(Qt::OpenHandCursor));

    QVBoxLayout *button_layout = new QVBoxLayout(button);
    QLabel *size_label = new QLabel(button_infos[i].size_label, button);
    QLabel *mine_label = new QLabel(button_infos[i].mine_label, button);

    size_label->setAlignment(Qt::AlignCenter);
    mine_label->setAlignment(Qt::AlignCenter);
    size_label->setFont(font);
    mine_label->setFont(font);
    button_layout->addWidget(size_label);
    button_layout->addWidget(mine_label);

    connect(button, &QPushButton::clicked, this, [this, i]() {
      variant = static_cast<GameVariants>(i);
      select_variant();
    });

    grid_layout->addWidget(button, i / 3, i % 3);
  }

  main_layout->addLayout(grid_layout);

  setLayout(main_layout);
  setWindowTitle(MENU_WINDOW_TITLE);
  setFixedSize(MENU_FIXED_WIDTH, MENU_FIXED_HEIGHT);
}

GameVariants MainMenu::get_variant() {
  return variant;
}

void MainMenu::select_variant() {
  accept();
}
