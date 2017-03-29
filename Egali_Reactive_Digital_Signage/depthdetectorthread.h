#ifndef DEPTHDETECTOR_H
#define DEPTHDETECTOR_H

#include <XnOpenNI.h>
#include <string>
#include <QThread>

using namespace std;

class DepthDetectorThread : public QThread
{
    Q_OBJECT

public:
    DepthDetectorThread() {
        m_depth = "i i i"; //default message
    };
    ~DepthDetectorThread();
    string getDepth();
    string depthGenerator(XnDepthPixel);

signals:
    void depthChanged();

protected:
    void run() override;

private:
    string m_depth; // format: "i/0/1...(main) i/0/1...(secondary) i/0/1...(guidance)"
};

#endif // DEPTHDETECTOR_H
