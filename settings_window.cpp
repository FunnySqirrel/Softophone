#include "settings_window.h"
#include "ui_settings_window.h"

Settings_window::Settings_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings_window)
{
    ui->setupUi(this);
}

Settings_window::~Settings_window()
{
    delete ui;
}
