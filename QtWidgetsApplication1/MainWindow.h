#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qdebug.h>
#include <qstring.h>
#include <string>
#include <qtreewidget.h>
#include <qlabel.h>
#include <qaction.h>
#include <qgraphicsview.h>
#include <QtGui>
#include <qdialog.h>
#include <nlohmann/json.hpp>
#include <cmath>
#include <filesystem>
namespace fs = std::filesystem;
using json = nlohmann::json;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QImage chertej;
    void resizeEvent(QResizeEvent* event);
    void set_chert();
    int variant = 1;
    int nut_isp = 1;
    int puckind = 0;

    bool do_ass = true;
    bool do_nes = true;
    bool do_nut = true;
    bool do_puc = true;

    void get_perem(double* perem, std::string det, std::string pname, json peremsDoc);
    void load_perems();
    void postroit_zikkurat();
    double Asd = 10;
    double Asd1 = 8;
    double Asd2 = 4.5;
    double AsMb = 16;
    double AsMa = 1;
    double AsD = 21.9;
    double AsD1 = 34;
    double AsL = 32;
    double AsB = 37;
    double AsB1 = 42;
    double AsSh1 = 8;
    double AsSh2 = 14;
    double Ned = 8;
    double Ned1 = 4.5;
    double Ned2 = 8;
    double NeMb = 16;
    double NeMa = 1;
    double NeD = 20;
    double NeD1 = 34;
    double NeD2 = 46;
    double NeB1 = 42;
    double Nel = 18;
    double Nud = 10;
    double NuMb = 16;
    double NuMa = 1;
    double NuD = 21.9;
    double Nus = 19;
    double Nul = 17;
    double Pud = 8;
    double PuD = 14;
    double Pus = 1.5;

 public slots:
     void on_pushButton_clicked();
     void on_treeWidget_itemClicked(QTreeWidgetItem* item, int column);

     void on_treeWidget_itemDoubleClicked(QTreeWidgetItem* item, int column);

     void on_action_triggered(bool checked = false);
     void on_action_2_triggered(bool checked = false);
     void on_action_3_triggered(bool checked = false);
     void on_action_4_triggered(bool checked = false);
     void on_action_5_triggered(bool checked = false);

private:
    Ui::MainWindowClass ui;
};


