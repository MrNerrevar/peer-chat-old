#ifndef PEER_H
#define PEER_H

#include <QtCore>
#include <QtNetwork>

class Message;
class Participant;
class Peer : public QObject
{
    Q_OBJECT
public:
    explicit Peer(QObject *parent = 0);

    void setParticipant(Participant*);
signals:
    void readMessage(Message*);
public slots:
    bool writeMessage(Message*);
    bool connectTo(Participant*);
private slots:
    void newConnection();
    void disconnected();
    void readyRead();

private:
    void allocateSocket(QTcpSocket*);

    Participant* me;
    QTcpServer* server;
    QHash<QTcpSocket*, QByteArray*> buffers;
    QHash<QTcpSocket*, qint32*> sizes;
    QHash<Participant*, QTcpSocket*> participants;
};

#endif // PEER_H
