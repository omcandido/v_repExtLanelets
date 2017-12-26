/* ----------------------------------------------------------
 * v_repExtLanelets plugin
 * (c) Candido Otero, 2017, Universidade de Vigo
 * ----------------------------------------------------------*/

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

    void refresh();

    void makeVisible(bool visible);

    bool getVisible();

    void reject();

    int dialogMenuItemHandle;

    void setSimulationStopped(bool stopped);

private slots:
    void on_buttonBrowse_clicked();

    void on_buttonImport_clicked();

    void on_buttonImport_2_clicked();

private:
    Ui::laneletsdialog *ui;
    static bool simulationStopped;

};

#endif // LANELETSDIALOG_H
