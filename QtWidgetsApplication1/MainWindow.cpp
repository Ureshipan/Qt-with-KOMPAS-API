#include "MainWindow.h"
#include "PermDialog.h"
#include "locale.h"
#include <vector>
#include <cmath>
#include "math.h"
#include <atlsafe.h>
#include "D:\Programms\KOMPAS\SDK\Include\ksConstants.h" //"C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\ksConstants.h"
#include "D:\Programms\KOMPAS\SDK\Include\ksConstants3D.h"//"C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\ksConstants3D.h"
#import "D:\Programms\KOMPAS\SDK\lib\kAPI5.tlb"//"C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\lib\kAPI5.tlb"
#pragma execution_character_set("utf-8")
#define PI 4*atan(1)
using json = nlohmann::json;

#pragma once

using namespace std;
using namespace Kompas6API5;

KompasObjectPtr pKompasApp5;
ksPartPtr pPart;// = PartDoc->GetTopPart();
ksDocument3DPtr pDoc;


QModelIndex selectedIndex;


int progress = 0;
QString choosed = "Assembling";

QImage ass_image("blueprints/assembling.png");
QImage nes_image("blueprints/nest.png");
QImage nut_image("blueprints/nut bolt.png");
QImage puc_image("blueprints/puck.png");


void MainWindow::set_chert()
{
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(chertej));
    scene->setSceneRect(0, 0, chertej.width(), chertej.height());
    ui.graphicsView->setScene(scene);
    ui.graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    ui.setupUi(this);
    chertej = ass_image;
    set_chert();
}

MainWindow::~MainWindow()
{}







std::string read_json_main()
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


//int get_isp_from_perem(string det, string perem, double mean)
//{
//    if (det == std::string("Assembling"))
//    {
//
//    }
//    else if (det == std::string("Nest"))
//    {
//
//    }
//    else if (det == std::string("Nut bolt"))
//    {
//
//    }
//    else if (det == std::string("Puck"))
//    {
//
//    }
//}


void MainWindow::get_perem(double* perem, std::string det, std::string pname, json peremsDoc)
{
    if (det == "Nut bolt")
    {
        *perem = peremsDoc[det][std::to_string(nut_isp)][std::to_string(variant)][pname][0].get<double>();
    }
    else if ((det == "Assembling" && pname == "Sd") || (det == "Puck" && pname == "d"))
    {
        *perem = peremsDoc[det][std::to_string(variant)][pname][puckind].get<double>();
    }
    else
    {
        *perem = peremsDoc[det][std::to_string(variant)][pname][0].get<double>();
    }
}

void MainWindow::load_perems()
{
    std::fstream myfile;
    myfile.open("peredacha.txt", std::ios_base::in);
    myfile >> variant >> nut_isp >> puckind;
    myfile.close();

    json peremsDoc{ json::parse(read_json_main()) };

    // Load for Assembling
    get_perem(&Asd, "Assembling", "d", peremsDoc);
    get_perem(&Asd1, "Assembling", "d1", peremsDoc);
    get_perem(&Asd2, "Assembling", "d2", peremsDoc);
    get_perem(&AsMb, "Assembling", "Mb", peremsDoc);
    get_perem(&AsMa, "Assembling", "Ma", peremsDoc);
    get_perem(&AsD, "Assembling", "D", peremsDoc);
    get_perem(&AsD1, "Assembling", "D1", peremsDoc);
    get_perem(&AsL, "Assembling", "L", peremsDoc);
    get_perem(&AsB, "Assembling", "B", peremsDoc);
    get_perem(&AsB1, "Assembling", "B1", peremsDoc);
    get_perem(&AsSh1, "Assembling", "Sd", peremsDoc);
    get_perem(&AsSh2, "Assembling", "SD", peremsDoc);
    // Load for Nest
    get_perem(&Ned, "Nest", "d", peremsDoc);
    get_perem(&Ned1, "Nest", "d1", peremsDoc);
    get_perem(&Ned2, "Nest", "d2", peremsDoc);
    get_perem(&NeMb, "Nest", "Mb", peremsDoc);
    get_perem(&NeMa, "Nest", "Ma", peremsDoc);
    get_perem(&NeD, "Nest", "D", peremsDoc);
    get_perem(&NeD1, "Nest", "D1", peremsDoc);
    get_perem(&NeD2, "Nest", "D2", peremsDoc);
    get_perem(&NeB1, "Nest", "B1", peremsDoc);
    get_perem(&Nel, "Nest", "l", peremsDoc);
    // Load foor Nut bolt
    get_perem(&Nud, "Nut bolt", "d", peremsDoc);
    get_perem(&NuMb, "Nut bolt", "Mb", peremsDoc);
    get_perem(&NuMa, "Nut bolt", "Ma", peremsDoc);
    get_perem(&NuD, "Nut bolt", "D", peremsDoc);
    get_perem(&Nus, "Nut bolt", "s", peremsDoc);
    get_perem(&Nul, "Nut bolt", "l", peremsDoc);
    // Load for Puck
    get_perem(&Pud, "Puck", "d", peremsDoc);
    get_perem(&PuD, "Puck", "D", peremsDoc);
    get_perem(&Pus, "Puck", "s", peremsDoc);
}


void MainWindow::postroit_zikkurat()
{

    std::string nest_pth = fs::current_path().string() + "\\Output detals\\Nest.m3d";
    std::string nut_pth = fs::current_path().string() + "\\Output detals\\Nut bolt.m3d";
    std::string puck_pth = fs::current_path().string() + "\\Output detals\\Puck.m3d";
    std::string assembling_pth = fs::current_path().string() + "\\Output detals\\assembling.a3d";

    CComPtr<IUnknown> pKompasAppUnk = nullptr;
    if (!pKompasApp5)
    {
        // Получаем CLSID для Компас
        CLSID InvAppClsid;
        HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
        if (FAILED(hRes)) {
            pKompasApp5 = nullptr;
            return;
        }

        // Проверяем есть ли запущенный экземпляр Компас
        //если есть получаем IUnknown
        hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
        if (FAILED(hRes)) {
            // Приходится запускать Компас самим так как работающего нет
            // Также получаем IUnknown для только что запущенного приложения Компас
            hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
            if (FAILED(hRes)) {
                pKompasApp5 = nullptr;
                return;
            }
        }

        // Получаем интерфейс приложения Компас
        hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
        if (FAILED(hRes)) {
            return;
        }
    }


    pKompasApp5->Visible = true;


    ksEntityPtr pSketch;
    ksSketchDefinitionPtr pSketchDef;
    ksDocument2DPtr p2DDoc;
    ksEntityPtr pRotate;
    ksBossRotatedDefinitionPtr pRotDef;
    ksEntityPtr pSketch2; 
    ksEntityPtr pExtrude1;
    ksCutExtrusionDefinitionPtr pExDef1;
    ksEntityPtr pSketch1;
    ksEntityPtr pExtrude;
    ksCutRotatedDefinitionPtr pRotDef1;
    ksEntityPtr pCircCopy;
    ksCircularCopyDefinitionPtr pCircDef;
    ksEntityCollectionPtr fl;
    ksCutExtrusionDefinitionPtr pExDef2;
    ksEntityCollectionPtr flFaces;
    ksEntityPtr face;
    ksEdgeDefinitionPtr thredge;
    ksFaceDefinitionPtr def;
    ksEdgeCollectionPtr col;
    ksVertexDefinitionPtr p1;
    ksVertexDefinitionPtr p2;
    double h, r;
    ksEntityPtr thrPtr;
    ksThreadDefinitionPtr thrDef; 
    ksEntityCollectionPtr entcol;


    if (do_nes)
    {
        pDoc = pKompasApp5->Document3D();
        pDoc->Create(false, true);
        pPart = pDoc->GetPart(pTop_Part);

        pSketch = pPart->NewEntity(o3d_sketch);
        pSketchDef = pSketch->GetDefinition();
        pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
        pSketch->Create();
        p2DDoc = pSketchDef->BeginEdit();


        double point[9][2];
        point[0][0] = Nel;
        point[0][1] = NeMb / 2;
        point[1][0] = Nel;
        point[1][1] = NeD / 2;
        point[2][0] = 3;
        point[2][1] = NeD / 2;
        point[3][0] = 3;
        point[3][1] = NeD2 / 2;
        point[4][0] = 0;
        point[4][1] = NeD2 / 2;
        point[5][0] = 0;
        point[5][1] = Ned / 2 + 1;
        point[6][0] = 1;
        point[6][1] = Ned / 2;
        point[7][0] = 3;
        point[7][1] = Ned / 2;
        point[8][0] = 3;
        point[8][1] = NeMb / 2;

        p2DDoc->ksLineSeg(point[0][0], point[0][1], point[1][0], point[1][1], 1);
        p2DDoc->ksLineSeg(point[1][0], point[1][1], point[2][0], point[2][1], 1);
        p2DDoc->ksLineSeg(point[2][0], point[2][1], point[3][0], point[3][1], 1);
        p2DDoc->ksLineSeg(point[3][0], point[3][1], point[4][0], point[4][1], 1);
        p2DDoc->ksLineSeg(point[4][0], point[4][1], point[5][0], point[5][1], 1);
        p2DDoc->ksLineSeg(point[5][0], point[5][1], point[6][0], point[6][1], 1);
        p2DDoc->ksLineSeg(point[6][0], point[6][1], point[7][0], point[7][1], 1);
        p2DDoc->ksLineSeg(point[7][0], point[7][1], point[8][0], point[8][1], 1);
        p2DDoc->ksLineSeg(point[8][0], point[8][1], point[0][0], point[0][1], 1);

        p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);


        pSketchDef->EndEdit();

        pRotate = pPart->NewEntity(o3d_bossRotated);

        pRotDef = pRotate->GetDefinition();
        pRotDef->SetSketch(pSketch);
        pRotDef->SetSideParam(TRUE, 360);


        pRotate->Create();


        pSketch2 = pPart->NewEntity(o3d_sketch);
        pSketchDef = pSketch2->GetDefinition();
        pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
        pSketch2->Create();
        p2DDoc = pSketchDef->BeginEdit();
        p2DDoc->ksCircle(0, 0, 100, 1);

        double point1[6][2];
        point1[0][0] = sin(asin(NeB1 / NeD2) - PI / 3) * NeD2 / 2;
        point1[0][1] = cos(asin(NeB1 / NeD2) - PI / 3) * NeD2 / 2;
        point1[1][0] = NeB1 / 2;
        point1[1][1] = -cos(asin(NeB1 / NeD2)) * NeD2 / 2;
        point1[2][0] = sin((PI / 3 - (asin(NeB1 / NeD2) - PI / 3))) * NeD2 / 2;
        point1[2][1] = -cos((PI / 3 - (asin(NeB1 / NeD2) - PI / 3))) * NeD2 / 2;
        point1[3][0] = -sin((PI / 3 - (asin(NeB1 / NeD2) - PI / 3))) * NeD2 / 2;
        point1[3][1] = -cos((PI / 3 - (asin(NeB1 / NeD2) - PI / 3))) * NeD2 / 2;
        point1[4][0] = -NeB1 / 2;
        point1[4][1] = -cos(asin(NeB1 / NeD2)) * NeD2 / 2;
        point1[5][0] = -sin(asin(NeB1 / NeD2) - PI / 3) * NeD2 / 2;
        point1[5][1] = cos(asin(NeB1 / NeD2) - PI / 3) * NeD2 / 2;

        p2DDoc->ksLineSeg(point1[0][0], point1[0][1], point1[1][0], point1[1][1], 1);
        p2DDoc->ksLineSeg(point1[1][0], point1[1][1], point1[2][0], point1[2][1], 1);
        p2DDoc->ksLineSeg(point1[2][0], point1[2][1], point1[3][0], point1[3][1], 1);
        p2DDoc->ksLineSeg(point1[3][0], point1[3][1], point1[4][0], point1[4][1], 1);
        p2DDoc->ksLineSeg(point1[4][0], point1[4][1], point1[5][0], point1[5][1], 1);
        p2DDoc->ksLineSeg(point1[5][0], point1[5][1], point1[0][0], point1[0][1], 1);

        pSketchDef->EndEdit();



        pExtrude1 = pPart->NewEntity(o3d_cutExtrusion);

        pExDef1 = pExtrude1->GetDefinition();
        pExDef1->directionType = dtNormal;

        pExDef1->SetSketch(pSketch2);
        pExDef1->SetSideParam(true, etThroughAll, 0, 0, false);

        pExtrude1->Create();



        pSketch1 = pPart->NewEntity(o3d_sketch);
        pSketchDef = pSketch1->GetDefinition();
        pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
        pSketch1->Create();
        p2DDoc = pSketchDef->BeginEdit();

        double point2[9][2];
        point2[0][0] = 0;
        point2[0][1] = -NeD1 / 2;
        point2[1][0] = 0;
        point2[1][1] = -NeD1 / 2 - Ned1 / 2;
        point2[2][0] = 3 - Ned2 / 2 + Ned1 / 2;
        point2[2][1] = -NeD1 / 2 - Ned1 / 2;
        point2[3][0] = 3;
        point2[3][1] = -NeD1 / 2 - Ned2 / 2;
        point2[4][0] = 3;
        point2[4][1] = -NeD1 / 2;

        p2DDoc->ksLineSeg(point2[0][0], point2[0][1], point2[1][0], point2[1][1], 1);
        p2DDoc->ksLineSeg(point2[1][0], point2[1][1], point2[2][0], point2[2][1], 1);
        p2DDoc->ksLineSeg(point2[2][0], point2[2][1], point2[3][0], point2[3][1], 1);
        p2DDoc->ksLineSeg(point2[3][0], point2[3][1], point2[4][0], point2[4][1], 1);
        p2DDoc->ksLineSeg(point2[4][0], point2[4][1], point2[0][0], point2[0][1], 1);

        p2DDoc->ksLineSeg(-10, -NeD1 / 2, 10, -NeD1 / 2, 3);
        pSketchDef->EndEdit();

        pExtrude = pPart->NewEntity(o3d_cutRotated);

        pRotDef1 = pExtrude->GetDefinition();
        pRotDef1->SetSketch(pSketch1);
        pRotDef1->SetSideParam(TRUE, 360);

        pExtrude->Create();


        pCircCopy = pPart->NewEntity(o3d_circularCopy);
        pCircDef = pCircCopy->GetDefinition();
        pCircDef->Putcount2(3);
        pCircDef->SetAxis(pPart->GetDefaultEntity(o3d_axisOX));
        fl = pCircDef->GetOperationArray();
        fl->Clear();
        fl->Add(pExtrude);
        pCircCopy->Create();

        flFaces = pPart->EntityCollection(o3d_face);
        for (int i = 0; i < flFaces->GetCount(); i++)
        {
            face = flFaces->GetByIndex(i);
            def = face->GetDefinition();

            if (def->GetOwnerEntity() == pRotate)
            {
                if (def->IsCylinder())
                {
                    def->GetCylinderParam(&h, &r);

                    if (r == NeMb / 2.f)
                    {
                        col = def->EdgeCollection();
                        thredge = col->GetByIndex(0);
                        face->Putname("NestCilind");
                        qDebug() << "NestCilind";
                        face->Update();
                    }

                }
                else if (def->IsPlanar())
                {
                    col = def->EdgeCollection();
                    for (int k = 0; k < col->GetCount(); k++)
                    {
                        ksEdgeDefinitionPtr d = col->GetByIndex(k);

                        if (d->IsPeriodic())
                        {
                            p1 = d->GetVertex(true);
                            p2 = d->GetVertex(false);
                            double x1, y1, z1;

                            p1->GetPoint(&x1, &y1, &z1);
                            if (x1 == 0)
                            {
                                face->Putname("NestConnect");
                                qDebug() << "NestConnect";
                                face->Update();
                                break;
                            }
                        }
                    }
                }
            }
        }



        thrPtr = pPart->NewEntity(o3d_thread);
        thrDef = thrPtr->GetDefinition();
        thrDef->SetBaseObject(thredge);
        thrDef->PutautoDefinDr(false);
        thrDef->dr = NeMb;
        thrDef->PutfaceValue(true);
        thrDef->Putp(NeMa);
        thrDef->length = Nul - Nul / 5;
        qDebug() << thrPtr->Create();

        pDoc->SaveAs(nest_pth.c_str());
    }
    //*******************************************************************************************************************************************

    progress = 25;
    ui.progressBar->setValue(progress);


    if (do_nut)
    {
        pDoc = pKompasApp5->Document3D();
        pDoc->Create(false, true);
        pPart = pDoc->GetPart(pTop_Part);

        if (nut_isp == 1)
        {
            pSketch = pPart->NewEntity(o3d_sketch);
            pSketchDef = pSketch->GetDefinition();
            pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
            pSketch->Create();
            p2DDoc = pSketchDef->BeginEdit();

            double nutpointrot[10][2];
            nutpointrot[0][1] = NuD / 2;
            nutpointrot[0][0] = 0;
            nutpointrot[1][1] = NuD / 2;
            nutpointrot[1][0] = -Nul / 5;
            nutpointrot[2][1] = (Nud + (NuMb - Nud) / 2) / 2;
            nutpointrot[2][0] = -Nul / 5;
            nutpointrot[3][1] = (Nud + (NuMb - Nud) / 2) / 2;
            nutpointrot[3][0] = -Nul / 5 - Nul / 9;
            nutpointrot[4][1] = NuMb / 2;
            nutpointrot[4][0] = -Nul / 5 - Nul / 9;
            nutpointrot[5][1] = NuMb / 2;
            nutpointrot[5][0] = -Nul + (NuMb / 2 - nutpointrot[2][1]);
            nutpointrot[6][1] = nutpointrot[2][1];
            nutpointrot[6][0] = -Nul;
            nutpointrot[7][1] = Nud / 2;
            nutpointrot[7][0] = -Nul;
            nutpointrot[8][1] = Nud / 2;
            nutpointrot[8][0] = -Nul / 7.5;
            nutpointrot[9][1] = Nud / 2 + Nul / 7.5;
            nutpointrot[9][0] = 0;

            for (int i = 0; i < 9; i++)
            {
                p2DDoc->ksLineSeg(nutpointrot[i][0], nutpointrot[i][1], nutpointrot[i + 1][0], nutpointrot[i + 1][1], 1);
            }
            p2DDoc->ksLineSeg(nutpointrot[9][0], nutpointrot[9][1], nutpointrot[0][0], nutpointrot[0][1], 1);

            p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);


            pSketchDef->EndEdit();

            pRotate = pPart->NewEntity(o3d_bossRotated);

            pRotDef = pRotate->GetDefinition();
            pRotDef->SetSketch(pSketch);
            pRotDef->SetSideParam(TRUE, 360);

            pRotate->Create();


            pSketch = pPart->NewEntity(o3d_sketch);
            pSketchDef = pSketch->GetDefinition();
            pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
            pSketch->Create();
            p2DDoc = pSketchDef->BeginEdit();
            p2DDoc->ksCircle(0, 0, 100, 1);

            double nutpointshest[6][2];
            nutpointshest[0][0] = 0;
            nutpointshest[0][1] = NuD / 2;
            nutpointshest[1][0] = cos(PI / 6) * NuD / 2;
            nutpointshest[1][1] = sin(PI / 6) * NuD / 2;
            nutpointshest[2][0] = cos(PI / 6) * NuD / 2;
            nutpointshest[2][1] = -sin(PI / 6) * NuD / 2;
            nutpointshest[3][0] = 0;
            nutpointshest[3][1] = -NuD / 2;
            nutpointshest[4][0] = -cos(PI / 6) * NuD / 2;
            nutpointshest[4][1] = -sin(PI / 6) * NuD / 2;
            nutpointshest[5][0] = -cos(PI / 6) * NuD / 2;
            nutpointshest[5][1] = sin(PI / 6) * NuD / 2;

            for (int i = 0; i < 5; i++)
            {
                p2DDoc->ksLineSeg(nutpointshest[i][0], nutpointshest[i][1], nutpointshest[i + 1][0], nutpointshest[i + 1][1], 1);
            }
            p2DDoc->ksLineSeg(nutpointshest[5][0], nutpointshest[5][1], nutpointshest[0][0], nutpointshest[0][1], 1);


            pSketchDef->EndEdit();

            pExtrude = pPart->NewEntity(o3d_cutExtrusion);

            pExDef1 = pExtrude->GetDefinition();
            pExDef1->directionType = dtReverse;

            pExDef1->SetSketch(pSketch);
            pExDef1->SetSideParam(true, etThroughAll, 100, 0, false);

            pExtrude->Create();
        }
        else
        {
            pSketch = pPart->NewEntity(o3d_sketch);
            pSketchDef = pSketch->GetDefinition();
            pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
            pSketch->Create();
            p2DDoc = pSketchDef->BeginEdit();

            double nutpointrot[8][2];
            nutpointrot[0][1] = NuD / 2;
            nutpointrot[0][0] = 0;
            nutpointrot[1][1] = NuD / 2;
            nutpointrot[1][0] = -Nul / 2.5;
            nutpointrot[2][1] = NuMb / 2;
            nutpointrot[2][0] = -Nul / 2.5;
            nutpointrot[3][1] = NuMb / 2;
            nutpointrot[3][0] = -Nul + (NuMb / 2 - (Nud + (NuMb - Nud) / 2) / 2);
            nutpointrot[4][1] = (Nud + (NuMb - Nud) / 2) / 2;
            nutpointrot[4][0] = -Nul;
            nutpointrot[5][1] = Nud / 2;
            nutpointrot[5][0] = -Nul;
            nutpointrot[6][1] = Nud / 2;
            nutpointrot[6][0] = -Nul / 7.5;
            nutpointrot[7][1] = Nud / 2 + Nul / 7.5;
            nutpointrot[7][0] = 0;

            for (int i = 0; i < 7; i++)
            {
                p2DDoc->ksLineSeg(nutpointrot[i][0], nutpointrot[i][1], nutpointrot[i + 1][0], nutpointrot[i + 1][1], 1);
            }
            p2DDoc->ksLineSeg(nutpointrot[7][0], nutpointrot[7][1], nutpointrot[0][0], nutpointrot[0][1], 1);

            p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);


            pSketchDef->EndEdit();

            pRotate = pPart->NewEntity(o3d_bossRotated);

            pRotDef = pRotate->GetDefinition();
            pRotDef->SetSketch(pSketch);
            pRotDef->SetSideParam(TRUE, 360);

            pRotate->Create();


            pSketch = pPart->NewEntity(o3d_sketch);
            pSketchDef = pSketch->GetDefinition();
            pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
            pSketch->Create();
            p2DDoc = pSketchDef->BeginEdit();
            p2DDoc->ksCircle(0, 0, 100, 1);

            double nutpointshest[6][2];
            nutpointshest[0][0] = 0;
            nutpointshest[0][1] = NuD / 2;
            nutpointshest[1][0] = cos(PI / 6) * NuD / 2;
            nutpointshest[1][1] = sin(PI / 6) * NuD / 2;
            nutpointshest[2][0] = cos(PI / 6) * NuD / 2;
            nutpointshest[2][1] = -sin(PI / 6) * NuD / 2;
            nutpointshest[3][0] = 0;
            nutpointshest[3][1] = -NuD / 2;
            nutpointshest[4][0] = -cos(PI / 6) * NuD / 2;
            nutpointshest[4][1] = -sin(PI / 6) * NuD / 2;
            nutpointshest[5][0] = -cos(PI / 6) * NuD / 2;
            nutpointshest[5][1] = sin(PI / 6) * NuD / 2;

            for (int i = 0; i < 5; i++)
            {
                p2DDoc->ksLineSeg(nutpointshest[i][0], nutpointshest[i][1], nutpointshest[i + 1][0], nutpointshest[i + 1][1], 1);
            }
            p2DDoc->ksLineSeg(nutpointshest[5][0], nutpointshest[5][1], nutpointshest[0][0], nutpointshest[0][1], 1);


            pSketchDef->EndEdit();

            pExtrude1 = pPart->NewEntity(o3d_cutExtrusion);

            pExDef2 = pExtrude1->GetDefinition();
            pExDef2->directionType = dtBoth;

            pExDef2->SetSketch(pSketch);
            qDebug() << pExDef2->SetSideParam(false, etBlind, Nul / 2.5 - 2, 0, false);

            pExtrude1->Create();
        }

        flFaces = pPart->EntityCollection(o3d_face);
        for (int i = 0; i < flFaces->GetCount(); i++)
        {
            face = flFaces->GetByIndex(i);
            def = face->GetDefinition();

            if (def->GetOwnerEntity() == pRotate)
            {
                if (def->IsCylinder())
                {
                    def->GetCylinderParam(&h, &r);

                    if (r == NuMb / 2.f)
                    {
                        col = def->EdgeCollection();
                        thredge = col->GetByIndex(1);
                        face->Putname("NutCilind");
                        qDebug() << "NutCilind";
                        face->Update();
                    }

                }
                else if (def->IsPlanar())
                {
                    col = def->EdgeCollection();
                    for (int k = 0; k < col->GetCount(); k++)
                    {
                        ksEdgeDefinitionPtr d = col->GetByIndex(k);

                        if (d->IsPeriodic())
                        {
                            p1 = d->GetVertex(true);
                            p2 = d->GetVertex(false);
                            double x1, y1, z1;

                            p1->GetPoint(&x1, &y1, &z1);
                            if (x1 == 0)
                            {
                                face->Putname("NutConnect");
                                qDebug() << "NutConnect";
                                face->Update();
                                break;
                            }
                        }
                    }
                }
            }

        }
        thrPtr = pPart->NewEntity(o3d_thread);
        thrDef = thrPtr->GetDefinition();
        thrDef->SetBaseObject(thredge);
        thrDef->PutautoDefinDr(true);
        thrDef->PutfaceValue(true);
        thrDef->Putp(NuMa);
        thrDef->length = Nul - Nul / 5 - Nul / 9 - (NuMb / 2 - (Nud + (NuMb - Nud) / 2) / 2);
        qDebug() << thrPtr->Create();

        pDoc->SaveAs(nut_pth.c_str());
    }
    //***************************************************************************************************************************************

    progress = 50;
    ui.progressBar->setValue(progress);


    if (do_puc)

    {
        pDoc = pKompasApp5->Document3D();
        pDoc->Create(false, true);
        pPart = pDoc->GetPart(pTop_Part);

        pSketch = pPart->NewEntity(o3d_sketch);
        pSketchDef = pSketch->GetDefinition();
        pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
        pSketch->Create();
        p2DDoc = pSketchDef->BeginEdit();

        double puckpoint[4][2];
        puckpoint[0][0] = 0;
        puckpoint[0][1] = PuD / 2;
        puckpoint[1][0] = -Pus;
        puckpoint[1][1] = PuD / 2;
        puckpoint[2][0] = -Pus;
        puckpoint[2][1] = Pud / 2;
        puckpoint[3][0] = 0;
        puckpoint[3][1] = Pud / 2;

        for (int i = 0; i < 3; i++)
        {
            p2DDoc->ksLineSeg(puckpoint[i][0], puckpoint[i][1], puckpoint[i + 1][0], puckpoint[i + 1][1], 1);
        }
        p2DDoc->ksLineSeg(puckpoint[3][0], puckpoint[3][1], puckpoint[0][0], puckpoint[0][1], 1);

        p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);


        pSketchDef->EndEdit();

        pRotate = pPart->NewEntity(o3d_bossRotated);

        pRotDef = pRotate->GetDefinition();
        pRotDef->SetSketch(pSketch);
        pRotDef->SetSideParam(TRUE, 360);

        pRotate->Create();


        flFaces = pPart->EntityCollection(o3d_face);
        for (int i = 0; i < flFaces->GetCount(); i++)
        {
            face = flFaces->GetByIndex(i);
            def = face->GetDefinition();

            if (def->GetOwnerEntity() == pRotate)
            {
                if (def->IsCylinder())
                {
                    def->GetCylinderParam(&h, &r);

                    if (r == PuD / 2.f)
                    {
                        face->Putname("PuckCilind");
                        qDebug() << "PuckCilind";
                        face->Update();
                    }

                }
                else if (def->IsPlanar())
                {
                    col = def->EdgeCollection();
                    for (int k = 0; k < col->GetCount(); k++)
                    {
                        ksEdgeDefinitionPtr d = col->GetByIndex(k);

                        if (d->IsCircle())
                        {
                            p1 = d->GetVertex(true);
                            p2 = d->GetVertex(false);
                            double x1, y1, z1;

                            p1->GetPoint(&x1, &y1, &z1);
                            if (x1 == 0)
                            {
                                face->Putname("PuckConnect");
                                qDebug() << "PuckConnect";
                                face->Update();
                                break;
                            }
                        }
                    }
                }
            }

        }


        pDoc->SaveAs(puck_pth.c_str());
    }
    //***************************************************************************************************************************************

    progress = 75;
    ui.progressBar->setValue(progress);

    if (do_ass)
    {
        pDoc = pKompasApp5->Document3D();

        pDoc->Create(false, false);

        pPart = pDoc->GetPart(pTop_Part);

        ksPartPtr pNest, pNut, pPuck;
        pDoc->SetPartFromFile(nest_pth.c_str(), pPart, true);
        pDoc->SetPartFromFile(nut_pth.c_str(), pPart, true);
        pDoc->SetPartFromFile(puck_pth.c_str(), pPart, true);

        pNest = pDoc->GetPart(0);
        pNut = pDoc->GetPart(1);
        pPuck = pDoc->GetPart(2);


        entcol = pNest->EntityCollection(o3d_face);

        ksEntityPtr NestCilind = entcol->GetByName("NestCilind", true, true);
        ksEntityPtr NestConnect = entcol->GetByName("NestConnect", true, true);

        entcol = pNut->EntityCollection(o3d_face);

        ksEntityPtr NutCilind = entcol->GetByName("NutCilind", true, true);
        ksEntityPtr NutConnect = entcol->GetByName("NutConnect", true, true);

        entcol = pPuck->EntityCollection(o3d_face);

        ksEntityPtr PuckCilind = entcol->GetByName("PuckCilind", true, true);
        ksEntityPtr PuckConnect = entcol->GetByName("PuckConnect", true, true);

        pDoc->AddMateConstraint(mc_Concentric, NestCilind, NutCilind, -1, 1, 0);
        pDoc->AddMateConstraint(mc_Concentric, NestCilind, PuckCilind, 1, 1, 0);

        pDoc->AddMateConstraint(mc_Distance, NestConnect, PuckConnect, 1, 1, -3);
        pDoc->AddMateConstraint(mc_Distance, NestConnect, NutConnect, -1, 1, -AsL);

        pDoc->SaveAs(assembling_pth.c_str());
    }

    progress = 100;
    ui.progressBar->setValue(progress);
}


void MainWindow::on_pushButton_clicked()
{
    progress = 0;
    ui.progressBar->setValue(progress);
    load_perems();
    postroit_zikkurat();
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    choosed = item->text(0);
    qDebug() << item->text(0) << " " << choosed << item->checkState(0);
    if (choosed == "Assembling")
    {
        if (item->checkState(0) == Qt::Unchecked)
        {
            do_ass = false;
            do_nes = false;
            do_nut = false;
            do_puc = false;
            for (int i = 0; i < item->childCount(); ++i)
            {
                item->child(i)->setCheckState(0, Qt::Unchecked);
            }
        }
        else
        {
            do_ass = true;
            do_nes = true;
            do_nut = true;
            do_puc = true;
            for (int i = 0; i < item->childCount(); ++i)
            {
                item->child(i)->setCheckState(0, Qt::Checked);
            }
        }
        chertej = ass_image;
        set_chert();
    }
    else if (choosed == "Nest")
    {
        if (item->checkState(0) == Qt::Unchecked)
        {
            do_ass = false;
            do_nes = false;
            item->parent()->setCheckState(0, Qt::Unchecked);
        }
        else
        {
            do_nes = true;
        }
        chertej = nes_image;
        set_chert();
    }
    else if (choosed == "Nut bolt")
    {
        if (item->checkState(0) == Qt::Unchecked)
        {
            do_ass = false;
            do_nut = false;
            item->parent()->setCheckState(0, Qt::Unchecked);
        }
        else
        {
            do_nut = true;
        }
        chertej = nut_image;
        set_chert();
    }
    else if (choosed == "Puck")
    {
        if (item->checkState(0) == Qt::Unchecked)
        {
            do_ass = false;
            do_puc = false;
            item->parent()->setCheckState(0, Qt::Unchecked);
        }
        else
        {
            do_puc = true;
        }
        chertej = puc_image;
        set_chert();
    }
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    choosed = item->text(0);
    qDebug() << item->text(0) << " " << choosed;
    if (choosed == "Assembling")
    {
        chertej = ass_image;
    }
    else if (choosed == "Nest")
    {
        chertej = nes_image;
    }
    else if (choosed == "Nut bolt")
    {
        chertej = nut_image;
    }
    else if (choosed == "Puck")
    {
        chertej = puc_image;
    }
    set_chert();
    PermDialog dlg;
    dlg.choose_det(choosed);
    dlg.show();
    dlg.exec();
}

void MainWindow::on_action_triggered(bool checked)
{
    choosed = "Assembling";
    qDebug() << choosed;
    chertej = ass_image;
    set_chert();
}

void MainWindow::on_action_2_triggered(bool checked)
{
    choosed = "Nest";
    qDebug() << choosed;
    chertej = nes_image;
    set_chert();
}

void MainWindow::on_action_3_triggered(bool checked)
{
    choosed = "Nut bolt";
    qDebug() << choosed;
    chertej = nut_image;
    set_chert();
}

void MainWindow::on_action_4_triggered(bool checked)
{
    choosed = "Puck";
    qDebug() << choosed;
    chertej = puc_image;
    set_chert();
}

void MainWindow::on_action_5_triggered(bool checked)
{
    std::ofstream myfile;
    myfile.open("peredacha.txt");
    myfile << 1 << " " << 1 << " " << 0 << " " << 0;
    myfile.close();
}


void MainWindow::resizeEvent(QResizeEvent* e)
{
    set_chert();
    QMainWindow::resizeEvent(e);
}


