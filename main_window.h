#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <sip_adapter.h>
#include <QMainWindow>
#include "call_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Main_window; }
QT_END_NAMESPACE

class Main_window : public QMainWindow
{
    Q_OBJECT

private:
    Ui::Main_window *ui;
    Sip_adapter *adapter=Sip_adapter::get_instance();   //creating singleton pointer
    Call_window* newcall;                               //pointer for incoming call window

public:
    Main_window(QWidget *parent = nullptr);
    ~Main_window();

public slots:
    void login_slot();          //registration slot, called by pushing button (слот регистрации, реагирующий на нажатие кнопки.)
    void logout_slot();         //unregistration slot, called by pushing button (слот разрегистрации, реагирующий на нажатие кнопки.)

    void renew_status_slot(int status); //renew status slot (слот обновления статуса)
    void make_outcall_slot();        //making an outgoing call slot (слот совершения исходящего вызова)

    void incoming_slot(int call_id, int status);        //incoming call handling  slot (слот обработки входящего вызова)
};
#endif // MAIN_WINDOW_H
