#ifndef CONTACT_WINDOW_H
#define CONTACT_WINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include <QMenu>
#include <QCloseEvent>
#include "database.h"
#include "contact_editor.h"
#include "sip_adapter.h"


namespace Ui {
class Contact_window;
}

class Contact_window : public QWidget
{
    Q_OBJECT

private:
    Ui::Contact_window *ui;
    Contact_editor *new_cont;

    Database *database;
    QSqlTableModel *model;

    Sip_adapter *adapter=Sip_adapter::get_instance();

    void setup_model (const QString &table_name, const QStringList &headers);
    void create_ui();
    void closeEvent(QCloseEvent *event);

public:
    explicit Contact_window(QWidget *parent = nullptr);
    ~Contact_window();

public slots:
    void renew_table_slot();
    void context_menu_slot(QPoint pos);
    void outcall_contact_slot();

    void new_contact_slot();
    void edit_contact_slot();
    void delete_contact_slot();

signals:
    void outcall_contact_signal(std::string uri);
    void im_closed_signal();
};

#endif // CONTACT_WINDOW_H
