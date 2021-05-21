#ifndef CALL_WINDOW_H
#define CALL_WINDOW_H

#include <QWidget>
#include <QSound>
#include "sip_adapter.h"


namespace Ui {
class Call_window;
}

class Call_window : public QWidget
{
    Q_OBJECT

private:
    Ui::Call_window *ui;
    Sip_adapter *adapter = Sip_adapter::get_instance();
    int id;

public:
    explicit Call_window(int call_id = 0, int status = 0, QWidget *parent = nullptr);
    ~Call_window();

public slots:
    void accept_slot();                     //accept slot
    void reject_slot();                     //reject slot
    void hangup_slot();                     //hangup slot

    void changing_status_slot(int status);
};

#endif // CALL_WINDOW_H
