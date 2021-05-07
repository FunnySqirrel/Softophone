#include "contact_window.h"
#include "ui_contact_window.h"

Contact_window::Contact_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contact_window)
{
    ui->setupUi(this);
    connect (ui->add_btn, &QPushButton::clicked, this, &Contact_window::new_contact_slot);
    connect (&database, &Database::renew_signal, this, &Contact_window::renew_table_slot);


    QDir db("../db");
    if (!db.exists())
    {db.mkdir("../db");}

    database.connect_to_database();

    this->setup_model(TABLE, QStringList() << trUtf8("id")<< trUtf8("Name")<< trUtf8("URI"));
    this->create_ui();
}

Contact_window::~Contact_window()
{
    delete ui;
}

void Contact_window::new_contact_slot()
{
    new_cont= new Contact_editor();
    connect(new_cont, &Contact_editor::accept_new_signal, &database, &Database::add_record);
    new_cont->show();
}

void Contact_window::setup_model(const QString &table_name, const QStringList &headers)
{
    model=new QSqlTableModel(this);
    model->setTable(table_name);
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++)
    {model->setHeaderData(i,Qt::Horizontal,headers[j]);}
}

void Contact_window::create_ui()
{
    ui->contact_table->setModel(model);
    ui->contact_table->setSelectionBehavior(QAbstractItemView::SelectRows);

    //Устанавливаем режим выделения лишь одно строки в таблице
    ui->contact_table->setSelectionMode(QAbstractItemView::SingleSelection);

    //скрываем id
    //ui->contact_table->setColumnHidden(0, true);

    //Устанавливаем размер колонок по содержимому
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
    QAction *edit_device = new QAction(trUtf8("Edit contact"), this);
    QAction *delete_device = new QAction(trUtf8("Delete contact"), this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(edit_device, &QAction::triggered, this, &Contact_window::edit_contact_slot);     // Обработчик вызова диалога редактирования
    connect(delete_device, &QAction::triggered, this, &Contact_window::delete_contact_slot); // Обработчик удаления записи

    /* Устанавливаем действия в меню */
    menu->addAction(edit_device);
    menu->addAction(delete_device);

    /* Вызываем контекстное меню */
    menu->popup(ui->contact_table->viewport()->mapToGlobal(pos));
}

void Contact_window::edit_contact_slot()
{
    int row = ui->contact_table->selectionModel()->currentIndex().row();
    new_cont= new Contact_editor(row);
    connect(new_cont, &Contact_editor::accept_edit_signal, &database, &Database::edit_record);
    new_cont->show();
}

void Contact_window::delete_contact_slot()
{
    int row = ui->contact_table->selectionModel()->currentIndex().row();
    model->removeRow(row);
    renew_table_slot();
    ui->contact_table->setCurrentIndex(model->index(-1, -1));
}
