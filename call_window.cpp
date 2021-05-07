#include "call_window.h"
#include "ui_call_window.h"

Call_window::Call_window(int call_id, int status, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Call_window),
    id(call_id)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    connect(ui->accept_btn, &QPushButton::clicked ,this, &Call_window::accept_slot);    //accepting incoming call connect
    connect(ui->reject_btn, &QPushButton::clicked ,this, &Call_window::reject_slot);    //rejecting incoming call connect
    connect(ui->hangup_btn, &QPushButton::clicked ,this, &Call_window::hangup_slot);    //hangup call connect
    connect(adapter,&Sip_adapter::changing_status_signal,this,&Call_window::changing_status_slot);
    std::string name=adapter->get_call_name(call_id);
    ui->name_value->setText(QString::fromStdString(name));
    changing_status_slot (status);
}

Call_window::~Call_window()
{
    delete ui;
}

void Call_window::accept_slot()
{
    adapter->answer_call(id, 200);
}

void Call_window::reject_slot()
{
    adapter->answer_call(id, 603);
}

void Call_window::hangup_slot()
{
    adapter->hangup_call(id);
}

void Call_window::changing_status_slot(int status)
{
    switch (status)
    {
    case 0:
        ui->status_value->setText("Null");
        break;
    case 1:
        ui->accept_btn->hide();
        ui->reject_btn->hide();
        ui->hangup_btn->show();
        ui->status_value->setText("Calling");
        break;
    case 2:
        ui->accept_btn->show();
        ui->reject_btn->show();
        ui->hangup_btn->hide();
        ui->status_value->setText("Incoming");
        break;
    case 3:
        ui->accept_btn->hide();
        ui->reject_btn->hide();
        ui->hangup_btn->show();
        ui->status_value->setText("Early");
        break;
    case 4:
        ui->accept_btn->hide();
        ui->reject_btn->hide();
        ui->hangup_btn->show();
        ui->status_value->setText("Connecting");
        break;
    case 5:
        ui->accept_btn->hide();
        ui->reject_btn->hide();
        ui->hangup_btn->show();
        ui->status_value->setText("Confirmed");
        break;
    case 6:
        ui->status_value->setText("Disconnecting");
        delete this;
        break;
    }
}
