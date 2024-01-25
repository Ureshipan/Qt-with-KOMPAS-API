#pragma once
#include <QtWidgets/QMainWindow>
#include <ui_PermDialog.h>
#include <qdialog.h>
#include <qdialog.h>
#include <QtGui>
#include <qdebug.h>
#include <qstring.h>
#include <string>
#include <qtreewidget.h>
#include <qlabel.h>
#include <qaction.h>
#include <qgraphicsview.h>
#include <vector>
#include <nlohmann/json.hpp>
#include <cmath>
#include <iostream>
#include <fstream>

class PermDialog : public QDialog
{
    Q_OBJECT

public:
    PermDialog(QWidget* parent = nullptr);
    ~PermDialog();
    std::vector <QLabel*> labels;
    std::vector <QComboBox*> comboxes;
    std::vector <std::string> varnames;
    std::vector <std::string> labelnames;
    int variant = 1;
    int tmp_var = 1;
    int nut_isp = 1;
    int combo_puckind = 0;
    int puckind = 0;
    void choose_det(QString det);
    void update_combos_to_var(int var, int from, int nui);

public slots:
    void on_comboBox_activated(int index);
    void on_comboBox_2_activated(int index);
    void on_comboBox_3_activated(int index);
    void on_comboBox_4_activated(int index);
    void on_comboBox_5_activated(int index);
    void on_comboBox_6_activated(int index);
    void on_comboBox_7_activated(int index);
    void on_comboBox_8_activated(int index);
    void on_comboBox_9_activated(int index);
    void on_comboBox_10_activated(int index);
    void on_comboBox_11_activated(int index);
    void on_comboBox_12_activated(int index);
    void on_comboBox_13_activated(int index);
    void on_pushButton_clicked();

private:
    Ui::Dialog ui;
};

