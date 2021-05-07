#ifndef CONTACT_WINDOW_H
#define CONTACT_WINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include <QDir>
#include <QMenu>
#include "database.h"
#include "contact_editor.h"


namespace Ui {
class Contact_window;
}

class Contact_window : public QWidget
{
    Q_OBJECT

private:
    Ui::Contact_window *ui;
    Contact_editor *new_cont;

    Database database;
    QSqlTableModel *model;

    void setup_model (const QString &table_name, const QStringList &headers);
    void create_ui();

public:
    explicit Contact_window(QWidget *parent = nullptr);
    ~Contact_window();

public slots:
    void new_contact_slot();
    void renew_table_slot();

    void edit_contact_slot();
    void delete_contact_slot();

    void context_menu_slot(QPoint pos);
};

#endif // CONTACT_WINDOW_H
