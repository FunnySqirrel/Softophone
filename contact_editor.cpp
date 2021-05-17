#include "contact_editor.h"
#include "ui_contact_editor.h"

Contact_editor::Contact_editor(int id_in, QString name, QString uri, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Contact_editor)
{
    ui->setupUi(this);
    id=id_in;
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    connect (ui->accept_btn, &QPushButton::clicked, this, &Contact_editor::accept_slot);
    connect (ui->dismiss_btn, &QPushButton::clicked, this, &Contact_editor::dismiss_slot);
    if (id==-1)
    {setWindowTitle("New Contact");}
    else
    {
        setWindowTitle(QString::fromStdString("Edit Contact "));
        ui->name_value->setText(name);
        ui->uri_value->setText(uri);
    }
}

Contact_editor::~Contact_editor()
{
    delete ui;
}

void Contact_editor::accept_slot()
{
    QString name=ui->name_value->text();
    QString uri=ui->uri_value->text();
    if (id==-1)
    {emit accept_new_signal(name,uri);}
    else
    {emit accept_edit_signal(id,name,uri);}
    this->close();
    delete this;
}

void Contact_editor::dismiss_slot()
{
    this->close();
    delete this;
}

void Contact_editor::closing_slot()
{
    this->close();
    delete this;
}
