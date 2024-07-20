#ifndef CELL_HPP
#define CELL_HPP

#include "workingdir.h"
#include <QColor>
#include <QMouseEvent>
#include <QPixmap>
#include <QPushButton>

#define STRAIGHTBOMB_IMG_PATH   WDIR "assets/bomb.png"
#define MISPLACED_BOMB_IMG_PATH WDIR "assets/misplacedbomb.png"
#define REDBOMB_IMG_PATH        WDIR "assets/redbomb.png"
#define FLAG_IMG_PATH           WDIR "assets/flag.png"

#define BLACK_RGB     QColor(20, 20, 20)
#define BLUE_RGB      QColor(0, 0, 205)
#define GREEN_RGB     QColor(0, 128, 0)
#define LIGHTRED_RGB  QColor(237, 28, 36)
#define DARKBLUE_RGB  QColor(25, 80, 232)
#define DARKRED_RGB   QColor(216, 0, 0)
#define AQUA_RGB      QColor(7, 147, 131)
#define PURPLE_RGB    QColor(149, 3, 168)
#define YELLOWISH_RGB QColor(206, 140, 8)
#define AMETHYST_RGB  QColor(191, 50, 242)

enum FontColor {
  BLACK,
  BLUE,
  GREEN,
  LIGHTRED,
  DARKBLUE,
  DARKRED,
  AQUA,
  PURPLE,
  YELLOWISH,
  AMETHYST,
};

class CellBtn : public QPushButton {
  Q_OBJECT

public:
  explicit CellBtn(QWidget *parent = nullptr);

  void set_font(FontColor font_color = BLACK);
  void set_icon(QString icon_path);
  void remove_icon();
  void disable();
  void flag();
  void unflag();
  bool is_flagged();

private:
  QFont cell_font;
  QPixmap pixmap;
  bool flagged;

private slots:
  void mousePressEvent(QMouseEvent *e);

signals:
  void leftClicked();
  void rightClicked();
};

#endif // CELL_HPP
