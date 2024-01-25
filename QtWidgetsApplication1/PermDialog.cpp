#include "PermDialog.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using json = nlohmann::json;





PermDialog::PermDialog(QWidget* parent)
    : QDialog(parent)

{
    ui.setupUi(this);
    labels = {
        ui.label,
        ui.label_2,
        ui.label_3,
        ui.label_4,
        ui.label_5,
        ui.label_6,
        ui.label_7,
        ui.label_8,
        ui.label_9,
        ui.label_10,
        ui.label_11,
        ui.label_12,
        ui.label_13
    };

    comboxes = {
        ui.comboBox,
        ui.comboBox_2,
        ui.comboBox_3,
        ui.comboBox_4,
        ui.comboBox_5,
        ui.comboBox_6,
        ui.comboBox_7,
        ui.comboBox_8,
        ui.comboBox_9,
        ui.comboBox_10,
        ui.comboBox_11,
        ui.comboBox_12,
        ui.comboBox_13
    };
}

PermDialog::~PermDialog()
{}



std::string read_json()
{
    std::ifstream inputFile("peremennie.json");


    // Step 3: Read the file content into a string using std::getline
    std::string fileContent;
    std::string line;

    while (std::getline(inputFile, line)) {
        fileContent += line + "\n"; // Append each line to the string
    }

    // Step 4: Close the file
    inputFile.close();
    return fileContent;
}


json peremsDoc{json::parse(read_json())};
std::vector <double> vals;
std::vector <std::string> svals;
int findex = 0;



//
//void get_var_from_val(QString det, QString pname, QString val, QString *nut_isp, int *variant, bool *izm, int* puckind = 0)
//{
//    if (det != "Nut bolt")
//    {
//        if (pname != "tip")
//        {
//            for (int i = 1; i < 5; i++)
//            {
//                vals = peremsDoc[det.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<double>>();
//                auto iter = std::find(vals.begin(), vals.end(), val.toDouble());
//                if (iter != vals.end())
//                {
//                    *variant = i;
//                    *izm = true;
//                    if (pname == "Sh")
//                    { 
//                        *puckind = std::distance(vals.begin(), iter);
//                    }
//                    return ;
//                }
//            }
//        }
//        else
//        {
//            for (int i = 1; i < 5; i++)
//            {
//                svals = peremsDoc[det.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<std::string>>();
//                if (std::find(svals.begin(), svals.end(), val.toStdString()) != svals.end())
//                {
//                    *variant = i;
//                    *izm = true;
//                    return ;
//                }
//            }
//        }
//    }
//    else
//    {
//        if (pname == "isp")
//        {
//            *nut_isp = val;
//            *izm = true;
//        }
//        else
//        {
//            for (int i = 1; i < 5; i++)
//            {
//                vals = peremsDoc[det.toStdString()][nut_isp->toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<double>>();
//                if (std::find(vals.begin(), vals.end(), val.toDouble()) != vals.end())
//                {
//                    *variant = i;
//                    *izm = true;
//                    return;
//                }
//            }
//        }
//
//    }
//}
//
//void get_val_from_var(QString det, QString pname, QString *val, QString nut_isp, int variant, int* puckind = 0)
//{
//    *puckind = 0;
//    if (det != "Nut bolt")
//    {
//        if (pname != "tip")
//        {
//            *val = QString::fromStdString(std::to_string(peremsDoc[det.toStdString()][std::to_string(variant)][pname.toStdString()][0].get<double>()));
//        }
//        else
//        {
//            *val = QString::fromStdString(peremsDoc[det.toStdString()][std::to_string(variant)][pname.toStdString()][0].get<std::string>());
//        }
//    }
//    else
//    {
//        *val = QString::fromStdString(std::to_string(peremsDoc[det.toStdString()][nut_isp.toStdString()][std::to_string(variant)][pname.toStdString()][0].get<double>()));
//    }
//}
//
//double get_val_by_combo_ind(QString det, QString pname, QString *val, QString *variant, QString *puckind = 0, QString nut_isp = "0")
//{
//
//}
//
//
//
//int get_combo_ind_by_val(QString det, QString pname, QString val, QString nut_isp = "0")
//{
//    int ind = 0;
//
//    if (det != "Nut bolt")
//    {
//        if (pname != "tip")
//        {
//            for (int i = 1; i < 5; i++)
//            {
//                vals = peremsDoc[det.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<double>>();
//                auto iter = std::find(vals.begin(), vals.end(), val.toDouble());
//                if (iter != vals.end())
//                {
//                    findex = std::distance(vals.begin(), iter);
//                    return ind + findex;
//                }
//                else
//                {
//                    ind += vals.size();
//                }
//            }
//        }
//        else
//        {
//            for (int i = 1; i < 5; i++)
//            {
//                svals = peremsDoc[det.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<std::string>>();
//                auto iter = std::find(svals.begin(), svals.end(), val.toStdString());
//                if (iter != svals.end())
//                {
//                    findex = std::distance(svals.begin(), iter);
//                    return ind + findex;
//                }
//                else
//                {
//                    ind += svals.size();
//                }
//            }
//        }
//    }
//    else
//    {
//        if (pname == "isp")
//        {
//            return val.toInt() - 1;
//        }
//        else
//        {
//            for (int i = 1; i < 5; i++)
//            {
//                vals = peremsDoc[det.toStdString()][nut_isp.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<double>>();
//                auto iter = std::find(svals.begin(), svals.end(), val.toDouble());
//                if (iter != svals.end())
//                {
//                    findex = std::distance(svals.begin(), iter);
//                    return ind + findex;
//                }
//                else
//                {
//                    ind += svals.size();
//                }
//            }
//        }
//    }
//    return ind;
//}
//
//int get_combo_col(QString det, QString pname)
//{
//
//    int ind = 0;
//
//    if (pname != "tip")
//    {
//        for (int i = 1; i < 5; i++)
//        {
//            vals = peremsDoc[det.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<double>>();
//            ind += vals.size();
//        }
//    }
//    else
//    {
//        for (int i = 1; i < 5; i++)
//        {
//            svals = peremsDoc[det.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<std::string>>();
//            ind += svals.size();
//        }
//    }
//    return ind;
//}

std::vector <double> get_all_vals(QString det, QString pname, int nut_isp = 0)
{

    std::vector <double> allvals = {};

    if (pname != "tip")
    {
        for (int i = 1; i < 5; i++)
        {
            //vals = peremsDoc[det.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<double>>();
            if (nut_isp == 0)
            {
                vals = peremsDoc[det.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<double>>();
            }
            else
            {
                vals = peremsDoc[det.toStdString()][std::to_string(nut_isp)][std::to_string(i)][pname.toStdString()].get<std::vector<double>>();
            }
            allvals.insert(allvals.end(), vals.begin(), vals.end());
        }
    }
    return allvals;
}



std::vector <std::string> get_all_string_vals(QString det, QString pname)
{

    std::vector <std::string> allvals = {};

    for (int i = 1; i < 5; i++)
    {
        //vals = peremsDoc[det.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<double>>();
        svals = peremsDoc["Assembling"][std::to_string(i)]["tip"].get<std::vector<std::string>>();
        allvals.insert(allvals.end(), svals.begin(), svals.end());
    }
    return allvals;
}


int get_shaib_var(QString val)
{
    for (int i = 1; i < 5; i++)
    {
        //vals = peremsDoc[det.toStdString()][std::to_string(i)][pname.toStdString()].get<std::vector<double>>();
        vals = peremsDoc["Puck"][std::to_string(i)]["d"].get<std::vector<double>>();
        qDebug() << vals[0] << val.toDouble();
        for (int j = 0; j < vals.size(); j++)
        {
            if (val.toDouble() == vals[j])
            {
                return i;
            }
        }
    }
}


int get_shaib_index(int variant)
{
    int ind = 0;
    for (int i = 1; i < variant; i++)
    {
        vals = peremsDoc["Puck"][std::to_string(i)]["d"].get<std::vector<double>>();
        ind += vals.size();
    }
    return ind;
}

int get_shaib_personal_index(int index)
{
    int ind = 0;
    for (int i = 1; i < 5; i++)
    {
        vals = peremsDoc["Puck"][std::to_string(i)]["d"].get<std::vector<double>>();
        ind += vals.size();
        if (ind > index)
        {
            return vals.size() - (ind - index);
        }
    }
    return ind;
}


void PermDialog::update_combos_to_var(int var, int from, int nui = 0)
{
    std::vector <double> allvals = {};
    for (int i = 0; i < comboxes.size(); i++)
    {
        if (!comboxes[i]->isHidden() && i != from && labels[i]->text() != "Ispolnenie")
        {
            combo_puckind = get_shaib_index(var);
            puckind = get_shaib_personal_index(combo_puckind);
            if (nui == 0)
            {
                if (comboxes[i]->count() == 4)
                {
                    comboxes[i]->setCurrentIndex(var - 1);
                }
                else if (comboxes[i]->count() > 1)
                {
                    comboxes[i]->setCurrentIndex(combo_puckind);
                }
            }
            else
            {
                allvals = get_all_vals(QString::fromStdString("Nut bolt"), QString::fromStdString(varnames[i]), nui);
                qDebug() << allvals.size();
                for (int j = 0; j < allvals.size(); j++)
                {
                    comboxes[i]->setItemText(j, QString::number(allvals[j]));
                    //comboxes[i]->addItem(QString::number(allvals[j]));
                    //comboxes[i]->setItemText(i, QString::fromStdString(std::to_string(allvals[i])));
                }
            }
        }
    }
}


void PermDialog::choose_det(QString det)
{
    std::fstream myfile;
    myfile.open("peredacha.txt", std::ios_base::in);
    myfile >> variant >> nut_isp >> puckind >> combo_puckind;
    tmp_var = variant;
    myfile.close();




    if (det == "Assembling")
    {
        varnames = { "tip", "d", "d1", "d2", "Mb", "Ma", "D", "D1", "L", "B", "Sd", "SD"};
        labelnames = { 
            "The standard size of the oil seal:", 
            "d", 
            "d1", 
            "d2", 
            "Thread diameter",
            "Thread step", 
            "D", 
            "D1", 
            "L", 
            "B",
            "Inner diameter of the washer", 
            "Outer diameter of the washer" 
        };
    }
    else if (det == "Nest")
    {
        varnames = {"d", "d1", "d2", "Mb", "Ma", "D", "D1", "D2", "B1", "l" };
        labelnames = {
             "d",
             "d1",
             "d2",
             "Thread diameter",
             "Thread step",
             "D",
             "D1",
             "D2",
             "B1",
             "l"
        };
    }
    else if (det == "Nut bolt")
    {
        varnames = { "isp", "d", "Mb", "Ma", "D", "s", "l" };
        labelnames = {
            "Ispolnenie",
            "d",
            "Thread diameter",
            "Thread step",
            "D",
            "s",
            "l" 
        };
    }
    else if (det == "Puck")
    {
        varnames = { "d", "D", "s" };
        labelnames = { "Inner diameter of the washer", "Outer diameter of the washer", "s" };
    }

    this->setWindowTitle(det);
    std::vector <double> allvals = {};
    std::vector <std::string> sallvals = {};
    this->setFixedHeight(varnames.size() * 35 + 40);
    for (int i = 0; i < labels.size(); i++)
    {
        if (i < varnames.size())
        {
            labels[i]->setText(QString::fromStdString(labelnames[i]));
            qDebug() << varnames[i];
            if (!(/*varnames[i] == "tip" || varnames[i] == "Sd" ||  */det == "Nut bolt"))
            {
                if (varnames[i] != "tip")
                {
                    allvals = get_all_vals(det, QString::fromStdString(varnames[i]));
                    qDebug() << allvals.size();
                    for (int j = 0; j < allvals.size(); j++)
                    {
                        comboxes[i]->addItem(QString::number(allvals[j]));
                        //comboxes[i]->setItemText(i, QString::fromStdString(std::to_string(allvals[i])));
                    }
                    if (labels[i]->text() == "Inner diameter of the washer")
                    {
                        comboxes[i]->setCurrentIndex(combo_puckind);
                    }
                    else
                    {
                        comboxes[i]->setCurrentIndex(variant - 1);
                    }
                }
                else
                {
                    sallvals = get_all_string_vals(det, QString::fromStdString(varnames[i]));
                    for (int j = 0; j < sallvals.size(); j++)
                    {
                        qDebug() << j << " " << sallvals[j];
                        comboxes[i]->addItem(QString::fromStdString(sallvals[j]));
                        //comboxes[i]->setItemText(i, QString::fromStdString(std::to_string(allvals[i])));
                    }
                    comboxes[i]->setCurrentIndex(variant - 1);
                }
            }
            else
            {
                if (varnames[i] == "isp")
                {
                    comboxes[i]->addItem(QString::fromStdString("1"));
                    comboxes[i]->addItem(QString::fromStdString("2"));
                    comboxes[i]->setCurrentIndex(nut_isp - 1);
                }
                else
                {
                    allvals = get_all_vals(det, QString::fromStdString(varnames[i]), nut_isp);
                    qDebug() << allvals.size();
                    for (int j = 0; j < allvals.size(); j++)
                    {
                        comboxes[i]->addItem(QString::number(allvals[j]));
                        //comboxes[i]->setItemText(i, QString::fromStdString(std::to_string(allvals[i])));
                    }
                    comboxes[i]->setCurrentIndex(variant - 1);
                }
            }
        }
        else
        {
            labels[i]->setVisible(false);
            comboxes[i]->setVisible(false);
        }
    }

}

void PermDialog::on_comboBox_activated(int index)
{
    int ind = 0;
    if (labels[ind]->text() != "Ispolnenie")
        if (labels[ind]->text() != "Inner diameter of the washer")
        {
            //if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
            {
                tmp_var = index + 1;
                update_combos_to_var(index + 1, ind);
            }
        }
        else
        {
            combo_puckind = index;
            puckind = get_shaib_personal_index(combo_puckind);
            tmp_var = get_shaib_var(comboxes[ind]->currentText());
            update_combos_to_var(tmp_var, ind);
        }
    else
    {
        nut_isp = index + 1;
        update_combos_to_var(tmp_var, ind, nut_isp);
    }
}

void PermDialog::on_comboBox_2_activated(int index)
{
    int ind = 1;
    //if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
    {
        tmp_var = index + 1;
        update_combos_to_var(index + 1, ind);
    }
}

void PermDialog::on_comboBox_3_activated(int index)
{
    int ind = 2;
    //if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
    {
        tmp_var = index + 1;
        update_combos_to_var(index + 1, ind);
    }
}

void PermDialog::on_comboBox_4_activated(int index)
{
    int ind = 3;
    //if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
    {
        tmp_var = index + 1;
        update_combos_to_var(index + 1, ind);
    }
}

void PermDialog::on_comboBox_5_activated(int index)
{
    int ind = 4;
    //if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
    {
        tmp_var = index + 1;
        update_combos_to_var(index + 1, ind);
    }
}

void PermDialog::on_comboBox_6_activated(int index)
{
    int ind = 5;
    //if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
    {
        tmp_var = index + 1;
        update_combos_to_var(index + 1, ind);
    }
}

void PermDialog::on_comboBox_7_activated(int index)
{
    int ind = 6;
    //if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
    {
        tmp_var = index + 1;
        update_combos_to_var(index + 1, ind);
    }
}

void PermDialog::on_comboBox_8_activated(int index)
{
    int ind = 7;
   // if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
    {
        tmp_var = index + 1;
        update_combos_to_var(index + 1, ind);
    }
}

void PermDialog::on_comboBox_9_activated(int index)
{
    int ind = 8;
    //if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
    {
        tmp_var = index + 1;
        update_combos_to_var(index + 1, ind);
    }
}

void PermDialog::on_comboBox_10_activated(int index)
{
    int ind = 9;
    //if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
    {
        tmp_var = index + 1;
        update_combos_to_var(index + 1, ind);
    }
}

void PermDialog::on_comboBox_11_activated(int index)
{
    int ind = 10;
    if (labels[ind]->text() != "Inner diameter of the washer")
    {
       // if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
        {
            tmp_var = index + 1;
            update_combos_to_var(index + 1, ind);
        }
    }
    else
    {
        combo_puckind = index;
        puckind = get_shaib_personal_index(combo_puckind);
        tmp_var = get_shaib_var(comboxes[ind]->currentText());
        update_combos_to_var(tmp_var, ind);
    }
}

void PermDialog::on_comboBox_12_activated(int index)
{
    int ind = 11;
    if (labels[ind]->text() != "Inner diameter of the washer")
    {
        // if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
        {
            tmp_var = index + 1;
            update_combos_to_var(index + 1, ind);
        }
    }
    else
    {
        combo_puckind = index;
        puckind = get_shaib_personal_index(combo_puckind);
        tmp_var = get_shaib_var(comboxes[ind]->currentText());
        update_combos_to_var(tmp_var, ind);
    }
}

void PermDialog::on_comboBox_13_activated(int index)
{
    int ind = 12;
    //if (tmp_var != index + 1 && comboxes[ind]->currentText() != comboxes[ind]->itemText(tmp_var - 1))
    //{
        tmp_var = index + 1;
        update_combos_to_var(index + 1, ind);
    //}
}

void PermDialog::on_pushButton_clicked()
{
    int ind = comboxes[1]->currentIndex();
    variant = tmp_var;
    std::ofstream myfile;
    myfile.open("peredacha.txt");
    myfile << variant << " " << nut_isp << " " << puckind << " " << combo_puckind;
    myfile.close();
    this->accept();
}