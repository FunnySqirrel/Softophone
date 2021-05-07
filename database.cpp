#include "database.h"

Database::Database()
{
}

void Database::connect_to_database()
{
    if(!QFile("../db/" DATABASE_NAME).exists())
    {this->restore_database();}
    else
    {this->open_database();}
}

bool Database::open_database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../db/contacts.db");
    if(db.open())
    {return true;}
    else
    {return false;}
}

bool Database::restore_database()
{
    if(this->open_database())
    {
        if(!this->create_table())
        {return false;}
        else
        {return true;}
    }
    else
    {
        qDebug() << "Can't open database!";
        return false;
    }
    return false;
}

void Database::close_database()
{
    db.close();
}

bool Database::create_table()
{
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_NAME    " VARCHAR(255)    NOT NULL,"
                            TABLE_URI     " VARCHAR(255)    NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool Database::add_record(QString name, QString uri)
{
    QVariantList data;
    data.append(name);
    data.append(uri);

    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " ( " TABLE_NAME ", "
                                             TABLE_URI ") "
                  "VALUES (:Name, :URI)");
    query.bindValue(":Name", data[0].toString());
    query.bindValue(":URI", data[1].toString());

    if(!query.exec())
    {
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        emit renew_signal();
        return true;
    }
    return false;
}

//bool Database::remove_record(int id)
//{
//    QSqlQuery query;
//
//    query.prepare("DELETE FROM " TABLE " WHERE id=:ID;");
//    query.bindValue(":ID", id);
//
//    if(!query.exec())
//    {
//        qDebug() << "error delete row " << TABLE;
//        qDebug() << query.lastError().text();
//        return false;
//    }
//    else
//    {
//        emit renew_signal();
//        return true;
//    }
//    return false;
//}

bool Database::edit_record(int id, QString name, QString uri)
{
    QVariantList data;
    data.append(id);
    data.append(name);
    data.append(uri);

    QSqlQuery query;
    query.prepare("UPDATE " TABLE " SET " TABLE_NAME " = :Name , "   TABLE_URI " = :URI " "WHERE id = :ID");
    query.bindValue(":ID",  data[0].toString());
    query.bindValue(":Name", data[1].toString());
    query.bindValue(":URI", data[2].toString());
    if (!query.exec())
    {
        qDebug() << "error edit row " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        emit renew_signal();
        return true;
    }
    return false;
}