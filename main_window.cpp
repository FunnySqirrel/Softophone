#include "main_window.h"
#include "ui_main_window.h"

Main_window::Main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main_window)
{
    ui->setupUi(this);

    connect(adapter, &Sip_adapter::get_status,this, &Main_window::renew_status_slot);       //renew status connect

    connect(ui->login_btn, &QPushButton::clicked ,this, &Main_window::login_slot);          //login connect
    connect(ui->logout_btn, &QPushButton::clicked ,this, &Main_window::logout_slot);        //logout connect

    connect(ui->outcall_btn, &QPushButton::clicked ,this, &Main_window::make_outcall_slot); //out call connect
    connect(adapter, &Sip_adapter::incoming_signal ,this, &Main_window::incoming_slot);     //incoming call connect
}

Main_window::~Main_window()
{
    delete ui;
}

void Main_window::login_slot()
{
    std::string name,           //user's name
    password,                   //password
    domain;                     //user's domain

    QString qname=ui->name_value->text();
    name=qname.toStdString();
    QString qpassword=ui->pass_value->text();
    password=qpassword.toStdString();
    QString qdomain=ui->domain_value->text();
    domain=qdomain.toStdString();
    adapter->reg(name, password, domain);
}

void Main_window::logout_slot()
{
    adapter->unreg();
}

void Main_window::renew_status_slot(int status)
{
    std::string st_status=std::to_string(status);
    QString q_status=QString::fromStdString(st_status);
    ui->status_value->setText(q_status);
}

void Main_window::make_outcall_slot()
{
    std::string uri;
    QString qOutCallName=ui->outcall_name_value->text();
    QString qOutCallDomain=ui->outcall_domain_value->text();
    uri="sip:"+qOutCallName.toStdString()+"@"+qOutCallDomain.toStdString();
    adapter->make_call(uri);
}

void Main_window::incoming_slot(int call_id)
{
    newcall= new Call_window(nullptr, call_id);                 //creating incoming call window object
    newcall->setAttribute(Qt::WA_DeleteOnClose);                //deleting window object when close
    connect(newcall, &Call_window::accept_signal ,this, &Main_window::incoming_accept);    //incoming call connect (accept)
    connect(newcall, &Call_window::reject_signal ,this, &Main_window::incoming_reject);    //incoming call connect (reject)
    newcall->show();            //show incoming call window
}

void Main_window::incoming_accept(int call_id)                  //accepting incoming call (200 OK)
{
    pjsua_call_answer(call_id, 200, NULL, NULL);
}
void Main_window::incoming_reject(int call_id)                  //rejecting incoming call (603 Decline)
{
    pjsua_call_answer(call_id, 603, NULL, NULL);
}
