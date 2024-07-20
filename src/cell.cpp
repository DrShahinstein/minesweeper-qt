#include "cell.hpp"

CellBtn::CellBtn(QWidget *parent) : QPushButton(parent) {
  setFocusPolicy(Qt::NoFocus);
};

void CellBtn::set_font(FontColor font_color) {
  cell_font.setPointSize(13);
  cell_font.setBold(true);
  QPalette palette = this->palette();

  switch (font_color) {
  case BLUE:
    palette.setColor(QPalette::ButtonText, BLUE_RGB);
    break;
  case GREEN:
    palette.setColor(QPalette::ButtonText, GREEN_RGB);
    break;
  case LIGHTRED:
    palette.setColor(QPalette::ButtonText, LIGHTRED_RGB);
    break;
  case DARKBLUE:
    palette.setColor(QPalette::ButtonText, DARKBLUE_RGB);
    break;
  case DARKRED:
    palette.setColor(QPalette::ButtonText, DARKRED_RGB);
    break;
  case AQUA:
    palette.setColor(QPalette::ButtonText, AQUA_RGB);
    break;
  case PURPLE:
    palette.setColor(QPalette::ButtonText, PURPLE_RGB);
    break;
  case YELLOWISH:
    palette.setColor(QPalette::ButtonText, YELLOWISH_RGB);
    break;
  case AMETHYST:
    palette.setColor(QPalette::ButtonText, AMETHYST_RGB);
    break;
  default:
    palette.setColor(QPalette::ButtonText, Qt::black);
    cell_font.setBold(false);
    cell_font.setPointSize(11);
    break;
  }

  setFont(cell_font);
  setPalette(palette);
}

void CellBtn::remove_icon() { setIcon(QIcon()); }
void CellBtn::set_icon(QString icon_path) {
  pixmap = QPixmap(icon_path);
  setIcon(pixmap);
  setIconSize(size());
}

void CellBtn::disable() {
  disconnect(this, &CellBtn::leftClicked, nullptr, nullptr);
  disconnect(this, &CellBtn::rightClicked, nullptr, nullptr);
}

bool CellBtn::is_flagged() { return flagged; }
void CellBtn::flag() { flagged = true; }
void CellBtn::unflag() { flagged = false; }

void CellBtn::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton) {
    emit rightClicked();
  } else if (event->button() == Qt::LeftButton) {
    emit leftClicked();
  }
  QPushButton::mouseReleaseEvent(event);
}
