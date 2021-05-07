#ifndef CONTACT_EDITOR_H
#define CONTACT_EDITOR_H

#include <QDialog>

namespace Ui {
class Contact_editor;
}

class Contact_editor : public QDialog
{
    Q_OBJECT

private:
    Ui::Contact_editor *ui;
    int id;

public:
    explicit Contact_editor(int=-1, QWidget *parent = nullptr);
    ~Contact_editor();

public slots:
    void accept_slot();
    void dismiss_slot();

signals:
    void accept_new_signal(QString name, QString uri);
    void accept_edit_signal(int id, QString name, QString uri);
};

#endif // CONTACT_EDITOR_H
