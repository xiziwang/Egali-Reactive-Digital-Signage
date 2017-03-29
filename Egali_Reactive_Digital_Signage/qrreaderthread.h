#ifndef QRREADER_H
#define QRREADER_H

#include <string>
#include <QThread>

using namespace std;

class QRReaderThread : public QThread
{
    Q_OBJECT

public:
    QRReaderThread() {
        m_message = "english std 0"; //default message
    };
    ~QRReaderThread();
    string getMessage();

signals:
    void messageChanged();

protected:
    void run() override;

private:
    string m_message; // format: "english/russian std/dys/vis 0/1/2..."
};

#endif // QRREADER_H
