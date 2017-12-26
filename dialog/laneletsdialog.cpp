/* ----------------------------------------------------------
 * v_repExtLanelets plugin
 * (c) Candido Otero, 2017, Universidade de Vigo
 * ----------------------------------------------------------*/

#include "laneletsdialog.h"
#include "ui_laneletsdialog.h"
#include "v_repLib.h"
#include <QFileInfo>
#include "lanelet2obj.hpp"
#include "MRT/libLanelet/llet_xml.hpp"

#include <iostream>

#include <MRT/libLanelet/llet_xml.hpp>
#include <MRT/libLanelet/Lanelet.hpp>
#include <MRT/libLanelet/LaneletMap.hpp>
#include <MRT/libLanelet/BoundingBox.hpp>

#include <boost/foreach.hpp>

#include <vector>
#include <tuple>
#include <memory>



bool laneletsdialog::simulationStopped = true;

laneletsdialog::laneletsdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::laneletsdialog)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    refresh();
}

laneletsdialog::~laneletsdialog()
{
    delete ui;
}

void laneletsdialog::refresh(){
    ui->buttonBrowse->setEnabled(simulationStopped);
    ui->buttonImport->setEnabled(simulationStopped);
    ui->linEdLat->setEnabled(simulationStopped);
    ui->linEdLon->setEnabled(simulationStopped);
    ui->linEdMap->setEnabled(simulationStopped);
}

void laneletsdialog::makeVisible(bool visible){
    setVisible(visible);
    simSetModuleMenuItemState(dialogMenuItemHandle,(visible?3:1),NULL);
}

bool laneletsdialog::getVisible(){
    return isVisible();
}

void laneletsdialog::reject(){
    makeVisible(false);
    done(0);
}

void laneletsdialog::setSimulationStopped(bool stopped){
    simulationStopped = stopped;
}

void laneletsdialog::on_buttonBrowse_clicked(){
    simChar* pathAndFile=simFileDialog(sim_filedlg_type_load,"LANELETS PLUGIN LOADER","","","OSM Files","osm");
    if (pathAndFile!=NULL)
    {
        std::string fileOSM(pathAndFile);
        simReleaseBuffer(pathAndFile);
        ui->linEdMap->setText(QString::fromStdString(fileOSM));
    }
}

void laneletsdialog::on_buttonImport_clicked()
{
    using namespace LLet;

    QString file = ui->linEdMap->text();
    QString lat = ui->linEdLat->text();
    QString lon = ui->linEdLon->text();

    QFileInfo check_file (file);

    if (!check_file.exists() || !check_file.isFile()){
        simMsgBox(sim_msgbox_type_warning,
                  sim_msgbox_buttons_ok,
                  "Error",
                  "Map file not found");
        return;
    }else if(lat.length()==0 || lon.length() == 0){
        simMsgBox(sim_msgbox_type_warning,
                  sim_msgbox_buttons_ok,
                  "Error",
                  "Origin must not be left empty");
        return;
    }

    int handleShape = lanelet2obj::importLanelets(file.toStdString(),
                                lat.toDouble(),
                                lon.toDouble(),
                                true);
    std::string msg;
    msg = handleShape == -1 ? "The lanelets map could not be imported" :
                              "Lanelets map succesfully imported";

    simMsgBox(sim_msgbox_type_info,
              sim_msgbox_buttons_ok,
              "RESULT",
              msg.c_str());

    makeVisible(false);
}
