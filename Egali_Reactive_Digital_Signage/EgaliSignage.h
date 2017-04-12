#ifndef EGALISIGNAGE_H
#define EGALISIGNAGE_H

#include <QMainWindow>
#include <QLabel>
#include <string>
#include "qrreaderthread.h"
#include "depthdetectorthread.h"

using namespace std;

namespace Ui {
class EgaliSignage;
}

class EgaliSignage : public QMainWindow
{
    Q_OBJECT

public:
    explicit EgaliSignage(QWidget *parent = 0);
    ~EgaliSignage();
    bool loadImage(QString, QLabel *);
    void setDpeth(string[]);

private slots:
    void setReadingPreserence();

signals:
    void dpethChanged(string[]);

private:
    Ui::EgaliSignage *ui;
    string m_depth[3];

    QRReaderThread qrThread;
    DepthDetectorThread depthThread;

    QString currentPath;
    //declear label objects
    QLabel *mainLabel;
    QLabel *secondaryLabel;
    QLabel *guidanceLabel;

};

#endif // EGALISIGNAGE_H
