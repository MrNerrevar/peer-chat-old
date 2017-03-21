#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include <QtNetwork>
#include "message.h"
#include "participant.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

public slots:
    bool connectToHost(QString host);
    bool writeData(QByteArray data);
    bool writeMessage(Message* m);
    void setParticipant(Participant*);
    Participant* getParticipant();

    QByteArray readData();
    Message* readMessage();

private:
    QTcpSocket *socket;
    Participant* me;
};

#endif // CLIENT_H
