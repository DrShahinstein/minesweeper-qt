#ifndef GAMEBAR_HPP
#define GAMEBAR_HPP

#include <QHBoxLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QWidget>

class GameBar : public QWidget {
  Q_OBJECT

public:
  explicit GameBar(int mines, QWidget *parent = nullptr);

  void update_timer(int seconds);
  void update_flag_count(int flags);

private:
  QLCDNumber *timer_display;
  QLCDNumber *flag_count_display;
  QPushButton *reset_button;

signals:
  void reset_game();

private slots:
  void handle_reset_button();
};

#endif // GAMEBAR_HPP
