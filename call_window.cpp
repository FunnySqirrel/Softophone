#include "call_window.h"
#include "ui_call_window.h"


Call_window::Call_window(QWidget *parent, int call_id) :
    QWidget(parent),
    ui(new Ui::Call_window)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);

    connect(ui->accept_btn, &QPushButton::clicked ,this, &Call_window::accept_slot);    //accepting incoming call connect
    connect(ui->reject_btn, &QPushButton::clicked ,this, &Call_window::reject_slot);    //rejecting incoming call connect
    connect(ui->hangup_btn, &QPushButton::clicked ,this, &Call_window::hangup_slot);    //hangup call connect
    id=call_id;
    std::string st_call_dst=adapter->get_call_dst();
    ui->name_value->setText(QString::fromStdString(st_call_dst));
}

Call_window::~Call_window()
{
    delete ui;
}

void Call_window::accept_slot()
{
    adapter->answer_call(id, 200);
    std::string st_call_id=adapter->get_call_dst();
    QString q_call_id=QString::fromStdString(st_call_id);
    ui->name_value->setText(q_call_id);
}

void Call_window::reject_slot()
{
    adapter->answer_call(id, 603);
    delete this;
}

void Call_window::hangup_slot()
{
    adapter->hangup_call(id);
    delete this;
}
