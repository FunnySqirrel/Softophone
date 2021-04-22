#include "main_window.h"
#include "ui_main_window.h"

Main_window::Main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main_window)
{
    ui->setupUi(this);

    connect(adapter, &Sip_adapter::changing_reg_signal,this, &Main_window::renew_status_slot);       //renew status connect

    connect(ui->login_btn, &QPushButton::clicked ,this, &Main_window::login_slot);          //login connect
    connect(ui->logout_btn, &QPushButton::clicked ,this, &Main_window::logout_slot);        //logout connect

    connect(ui->outcall_btn, &QPushButton::clicked ,this, &Main_window::make_outcall_slot); //out call connect
    connect(adapter, &Sip_adapter::incoming_call_signal ,this, &Main_window::incoming_slot);     //incoming call connect
}

Main_window::~Main_window()
{
    adapter->sip_adapter_destroy();
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
    switch (status)
    {
    case 0:
        ui->status_value->setText("Unregistered");

        ui->login_btn->setEnabled(true);
        ui->name_value->setEnabled(true);
        ui->pass_value->setEnabled(true);
        ui->domain_value->setEnabled(true);

        ui->logout_btn->setEnabled(false);
        ui->outcall_btn->setEnabled(false);
        ui->outcall_name_value->setEnabled(false);
        ui->outcall_domain_value->setEnabled(false);
        break;
    case 1:
        ui->status_value->setText("Registered");

        ui->logout_btn->setEnabled(true);
        ui->outcall_btn->setEnabled(true);
        ui->outcall_name_value->setEnabled(true);
        ui->outcall_domain_value->setEnabled(true);

        ui->login_btn->setEnabled(false);
        ui->name_value->setEnabled(false);
        ui->pass_value->setEnabled(false);
        ui->domain_value->setEnabled(false);

        break;
    }

}

void Main_window::make_outcall_slot()
{
    std::string uri;
    QString qOutCallName=ui->outcall_name_value->text();
    QString qOutCallDomain=ui->outcall_domain_value->text();
    uri="sip:"+qOutCallName.toStdString()+"@"+qOutCallDomain.toStdString();
    int call_id=adapter->make_call(uri);
    newcall= new Call_window(nullptr, call_id);
    newcall->show();            //show call window
}

void Main_window::incoming_slot(int call_id, int status)
{
    newcall= new Call_window(nullptr, call_id, status);                 //creating call window object
    newcall->show();            //show call window
}
