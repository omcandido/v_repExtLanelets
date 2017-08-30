#include "laneletsdialog.h"
#include "ui_laneletsdialog.h"

laneletsdialog::laneletsdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::laneletsdialog)
{
    ui->setupUi(this);
}

laneletsdialog::~laneletsdialog()
{
    delete ui;
}
