#include "egalisignage.h"
#include "ui_egalisignage.h"
#include "qrreaderthread.h"
#include "depthdetectorthread.h"

#include <string>
#include<iostream>
#include<sstream>
#include<QKeyEvent>
#include <QCoreApplication>
#include<QDebug>
#include<QMovie>

using namespace std;

EgaliSignage::EgaliSignage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EgaliSignage)
{
    ui->setupUi(this);
    installEventFilter(this);

    //initialize label objects
    mainLabel = new QLabel(ui->image_main);
    secondaryLabel = new QLabel(ui->image_secondary);
    guidanceLabel = new QLabel(ui->image_guidance);

    // NOTE: this path can be changed
    //currentPath = "/Users/KZRL/Kinect/Egali-Reactive-Digital-Signage/Egali_Reactive_Digital_Signage/images";
    currentPath = "/Users/Lucy-Wang/Developer/Kinect/Egali-Reactive-Digital-Signage/Egali_Reactive_Digital_Signage/images";
    //currentPath = "/Users/karl/Egali-Reactive-Digital-Signage/Egali_Reactive_Digital_Signage/images";

    //set default images
    setReadingPreserence();

    // start scanning qrcodes and detecting depthes in other threads
    qrThread.start();
    QObject::connect(&qrThread, SIGNAL(messageChanged()), this, SLOT(setReadingPreserence()));
    depthThread.start();
    QObject::connect(&depthThread, SIGNAL(depthChanged()), this, SLOT(setReadingPreserence()));

    this->showFullScreen();
}

/* This function load the image */
bool EgaliSignage::loadImage(QString path, QLabel *label) {
    QPixmap jpg_image(path+".jpg");
    //if no jpg image is found, then search for the gif image
    if (jpg_image.isNull()) {
        QMovie *gif_image = new QMovie(path+".gif");
        //set gif image
        label->setMovie(gif_image);
        gif_image->start();
    } else {
        //set jpg image
        label->setMovie(NULL);
        label->setPixmap(jpg_image);
    }
    return true;
}

/* This function scans the qr code and set reading preference */
void EgaliSignage::setReadingPreserence() {
    string tempMessage = qrThread.getMessage();
    string message[3];
    string tempDepth = depthThread.getDepth();
    string depth[3];
    //convert message string to array of string
    int i = 0;
    stringstream ssin_message(tempMessage);
    while (ssin_message.good() && i < 3){
        ssin_message >> message[i];
        ++i;
    }
    //convert depth string to array of string
    i = 0;
    stringstream ssin_depth(tempDepth);
    while (ssin_depth.good() && i < 3){
        ssin_depth >> depth[i];
        ++i;
    }

    //create pathes
    QString mainLabelPath = currentPath + QString::fromStdString("/"+ message[0] + "/" + message[1] + "/" + "main" + "/" + message[2] + "/" + depth[0]);
    QString secondaryLabelPath = currentPath + QString::fromStdString("/"+ message[0] + "/" + message[1] + "/" + "secondary" + "/" + message[2] + "/" + depth[1]);
    QString guidanceLabelPath = currentPath + QString::fromStdString("/"+ message[0] + "/" + message[1] + "/" + "guidance" + "/" + message[2] + "/" + depth[2]);

    //load images
    loadImage(mainLabelPath, mainLabel);
    loadImage(secondaryLabelPath, secondaryLabel);
    loadImage(guidanceLabelPath, guidanceLabel);
}

EgaliSignage::~EgaliSignage()
{
    delete ui;
}
