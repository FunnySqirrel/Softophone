#include "call_window.h"
#include "ui_call_window.h"

Call_window::Call_window(QWidget *parent, int call_id) :
    QWidget(parent),
    ui(new Ui::Call_window)
{
    ui->setupUi(this);
    connect(ui->accept_btn, &QPushButton::clicked ,this, &Call_window::accept_slot);    //accepting incoming call connect
    connect(ui->reject_btn, &QPushButton::clicked ,this, &Call_window::reject_slot);    //rejecting incoming call connect
    id=call_id;
}

Call_window::~Call_window()
{
    delete ui;
}

void Call_window::accept_slot()
{emit accept_signal(id);}

void Call_window::reject_slot()
{emit reject_signal(id);}
