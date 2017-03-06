#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include <QtNetwork>
#include "message.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

public slots:
    bool connectToHost(QString host);
    bool writeData(QByteArray data);

    //bool writeMessage(Message m);

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
