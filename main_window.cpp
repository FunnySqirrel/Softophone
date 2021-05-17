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


    connect(adapter, &Sip_adapter::incoming_call_signal ,this, &Main_window::incoming_slot);     //incoming call connect

    connect(ui->contact_list_btn, &QPushButton::clicked ,this, &Main_window::contact_list_slot); //contact list connect

    connect(ui->outcall_btn, &QPushButton::clicked ,this, &Main_window::outcall_click_slot); //binding uri to make_outcall
    connect(this, &Main_window::outcall_signal ,this, &Main_window::make_outcall_slot); //out call connect
    connect(&contacts, &Contact_window::outcall_contact_signal ,this, &Main_window::make_outcall_slot);

    settings= new QSettings("settings.ini", QSettings::IniFormat);
    settings->beginGroup( "registration_info" );
    QString name= settings->value("name").toString();
    ui->name_value->setText(name);
    QString pass= settings->value("password").toString();
    ui->pass_value->setText(pass);
    QString domain= settings->value("domain").toString();
    ui->domain_value->setText(domain);
    settings->endGroup();
}

Main_window::~Main_window()
{
    delete ui;
    delete adapter;
    delete settings;
}

void Main_window::closeEvent(QCloseEvent *event)
{
    emit im_logout_signal();
    if (adapter->get_status()==1)
    {adapter->unreg();}
    contacts.close();
    adapter->sip_adapter_destroy();
    if (ui->remember_check->QAbstractButton::isChecked()==false)
    {
        settings->remove( "registration_info" );
    }
    event->accept();
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
    emit im_logout_signal();
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
        break;
    case 1:
        ui->status_value->setText("Registered");

        ui->logout_btn->setEnabled(true);
        ui->outcall_btn->setEnabled(true);
        ui->outcall_name_value->setEnabled(true);

        ui->login_btn->setEnabled(false);
        ui->name_value->setEnabled(false);
        ui->pass_value->setEnabled(false);
        ui->domain_value->setEnabled(false);

        settings->beginGroup( "registration_info" );
        settings->setValue( "name", ui->name_value->text());
        settings->setValue( "password", ui->pass_value->text());
        settings->setValue( "domain", ui->domain_value->text());
        settings->endGroup();

        break;
    }
}

void Main_window::outcall_click_slot()
{
    QString qOutCallName=ui->outcall_name_value->text();
    std:: string uri=qOutCallName.toStdString();
    emit outcall_signal(uri);
}

void Main_window::make_outcall_slot(std::string uri)
{
    int call_id=adapter->make_call(uri);
    new_call= new Call_window(call_id);
    connect(this, &Main_window::im_logout_signal, new_call, &Call_window::hangup_slot);
    new_call->show();            //show call window
}

void Main_window::incoming_slot(int call_id, int status)
{
    new_call= new Call_window(call_id, status);                 //creating call window object
    connect(this, &Main_window::im_logout_signal, new_call, &Call_window::hangup_slot);
    new_call->show();            //show call window
}

void Main_window::contact_list_slot()
{
    contacts.show();
}
