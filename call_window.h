#ifndef CALL_WINDOW_H
#define CALL_WINDOW_H

#include <QWidget>

namespace Ui {
class Call_window;
}

class Call_window : public QWidget
{
    Q_OBJECT

private:
    Ui::Call_window *ui;
    int id;

public:
    explicit Call_window(QWidget *parent = nullptr, int call_id=0);
    ~Call_window();

public slots:
    void accept_slot();
    void reject_slot();

signals:
    void accept_signal(int call_id);
    void reject_signal(int call_id);
};

#endif // CALL_WINDOW_H
