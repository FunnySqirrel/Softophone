#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <QWidget>

namespace Ui {
class Settings_window;
}

class Settings_window : public QWidget
{
    Q_OBJECT

private:
    Ui::Settings_window *ui;

public:
    explicit Settings_window(QWidget *parent = nullptr);
    ~Settings_window();
};

#endif // SETTINGS_WINDOW_H
