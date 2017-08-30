#ifndef LANELETSDIALOG_H
#define LANELETSDIALOG_H

#include <QDialog>

namespace Ui {
class laneletsdialog;
}

class laneletsdialog : public QDialog
{
    Q_OBJECT

public:
    explicit laneletsdialog(QWidget *parent = 0);
    ~laneletsdialog();

private:
    Ui::laneletsdialog *ui;
};

#endif // LANELETSDIALOG_H
