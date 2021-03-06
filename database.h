#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDebug>

#define DATABASE_NAME       "contacts.db"

#define TABLE                   "Contact_list"
#define TABLE_NAME              "Name"
#define TABLE_URI               "URI"

class Database: public QObject
{
    Q_OBJECT;
private:
    QSqlDatabase    db;
public:
    explicit Database();

    void connect_to_database();

    bool open_database();
    bool restore_database();
    void close_database();

    bool create_table();

public slots:
    bool add_record_slot(QString name, QString uri);
    bool edit_record_slot(int id, QString name, QString uri);
signals:
    void renew_signal();
};

#endif // DATABASE_H
