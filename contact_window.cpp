#include "contact_window.h"
#include "ui_contact_window.h"

Contact_window::Contact_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contact_window)
{
    ui->setupUi(this);

    database = new Database;
    database->connect_to_database();

    this->setup_model(TABLE, QStringList() << trUtf8("id")<< trUtf8("Name")<< trUtf8("URI"));
    this->create_ui();

    connect (ui->add_btn, &QPushButton::clicked, this, &Contact_window::new_contact_slot);
    connect (database, &Database::renew_signal, this, &Contact_window::renew_table_slot);
}

Contact_window::~Contact_window()
{
    delete ui;
    delete model;
    delete database;
}

void Contact_window::closeEvent(QCloseEvent *event)
{
    emit im_closed_signal();
    event->accept();
}

void Contact_window::setup_model(const QString &table_name, const QStringList &headers)
{
    model = new QSqlTableModel(this);
    model->setTable(table_name);
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++)
    {
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}

void Contact_window::create_ui()
{
    ui->contact_table->setModel(model);
    ui->contact_table->setSelectionBehavior(QAbstractItemView::SelectRows);

    //Set selection of one string
    ui->contact_table->setSelectionMode(QAbstractItemView::SingleSelection);

    //hide id
    ui->contact_table->setColumnHidden(0, true);

    //Resize coloumns
    ui->contact_table->resizeColumnsToContents();
    ui->contact_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->contact_table->horizontalHeader()->setStretchLastSection(true);
    renew_table_slot();

    ui->contact_table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->contact_table, &QWidget::customContextMenuRequested, this, &Contact_window::context_menu_slot);
}

void Contact_window::renew_table_slot()
{
    model->select();
    ui->contact_table->resizeColumnsToContents();
}

void Contact_window::context_menu_slot(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    QAction *outcall_device = new QAction(trUtf8("Do Out call"), this);
    QAction *edit_device = new QAction(trUtf8("Edit contact"), this);
    QAction *delete_device = new QAction(trUtf8("Delete contact"), this);
    connect(outcall_device, &QAction::triggered, this, &Contact_window::outcall_contact_slot);
    connect(edit_device, &QAction::triggered, this, &Contact_window::edit_contact_slot);     // ???????????????????? ???????????? ?????????????? ????????????????????????????
    connect(delete_device, &QAction::triggered, this, &Contact_window::delete_contact_slot); // ???????????????????? ???????????????? ????????????

    /*Set menu actions*/
    outcall_device->setEnabled(false);
    if (adapter->get_status()==1)
    {outcall_device->setEnabled(true);}
    menu->addAction(outcall_device);
    menu->addAction(edit_device);
    menu->addAction(delete_device);

    /*summon conext menu*/
    menu->popup(ui->contact_table->viewport()->mapToGlobal(pos));
}

void Contact_window::outcall_contact_slot()
{
    int row = ui->contact_table->selectionModel()->currentIndex().row();
    emit outcall_contact_signal(model->data(model->index(row, 2)).toString().toStdString());
}

void Contact_window::new_contact_slot()
{
    new_cont= new Contact_editor();
    connect(new_cont, &Contact_editor::accept_new_signal, database, &Database::add_record_slot);
    connect(this, &Contact_window::im_closed_signal, new_cont, &Contact_editor::dismiss_slot);
    new_cont->show();
}

void Contact_window::edit_contact_slot()
{
    int row = ui->contact_table->selectionModel()->currentIndex().row();
    int id=model->data(model->index(row, 0)).toInt();
    QString name=model->data(model->index(row, 1)).toString();
    QString uri=model->data(model->index(row, 2)).toString();
    new_cont= new Contact_editor(id, name, uri);
    connect(new_cont, &Contact_editor::accept_edit_signal, database, &Database::edit_record_slot);
    connect(this, &Contact_window::im_closed_signal, new_cont, &Contact_editor::dismiss_slot);
    new_cont->show();
}

void Contact_window::delete_contact_slot()
{
    int row = ui->contact_table->selectionModel()->currentIndex().row();
    model->removeRow(row);
    renew_table_slot();
    ui->contact_table->setCurrentIndex(model->index(-1, -1));
}
