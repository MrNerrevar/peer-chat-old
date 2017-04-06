#include "peer.h"
#include "message.h"
#include "participantmanager.h"

static inline qint32 ArrayToInt(QByteArray source);
static inline QByteArray IntToArray(qint32 source);

Peer::Peer(QObject *parent) : QObject(parent)
{
    qDebug() << "Setup server peer";
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
    this->server->listen(QHostAddress::Any, 1024);
}

void Peer::allocateSocket(QTcpSocket* socket)
{
    qDebug() << "Allocating socket";
    connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
    auto buffer = new QByteArray();
    auto s = new qint32(0);
    buffers.insert(socket, buffer);
    sizes.insert(socket, s);
}

bool Peer::connectTo(Participant* p)
{
    if (participants.contains(p))
        return true;

    qDebug() << "Connecting to peer";
    auto socket = new QTcpSocket(this);
    socket->connectToHost(p->Host, p->Port);
    auto connected = socket->waitForConnected();
    allocateSocket(socket);
    participants.insert(p, socket);
    return connected;
}

void Peer::newConnection()
{
    qDebug() << "New connection?";
    while (server->hasPendingConnections())
    {
        qDebug() << "Yeah new connection";
        auto socket = server->nextPendingConnection();
        allocateSocket(socket);

        auto p = ParticipantManager::newParticipant(socket->peerAddress().toString(), socket->peerPort());
        participants.insert(p, socket);
    }
}

void Peer::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 *s = sizes.value(socket);
    socket->deleteLater();
    delete buffer;
    delete s;
}

void Peer::setParticipant(Participant* p)
{
    this->me = p;
}

Participant* Peer::getParticipant()
{
    return this->me;
}

bool Peer::writeMessage(Message* m)
{
    if(m == NULL)
        return false;
    auto socket = this->participants.value(m->Receiver);
    if(socket == NULL)
        return false;
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        m->Sender = this->me;
        auto data = m->toByteArray();
        socket->write(IntToArray(data.size()));
        socket->write(data);
        return socket->waitForBytesWritten();
    }
    return false;
}

void Peer::readyRead()
{
    qDebug() << "Received message";
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 *s = sizes.value(socket);
    qint32 size = *s;
    while (socket->bytesAvailable() > 0)
    {
        buffer->append(socket->readAll());
        while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size))
        {
            if (size == 0 && buffer->size() >= 4)
            {
                size = ArrayToInt(buffer->mid(0, 4));
                *s = size;
                buffer->remove(0, 4);
            }
            if (size > 0 && buffer->size() >= size)
            {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);
                size = 0;
                *s = size;
                auto m = new Message();
                m->fromRawString(QString(data));
                qDebug() << "Read Message";
                QString pp = "pp";
                qDebug() << pp;
                qDebug() << m->Data;

                auto p = this->participants.key(socket);
                ParticipantManager::newParticipant(p->Name, p->Host, p->Port);
                emit readMessage(m);
            }
        }
    }
}

//QString Peer::getAddress()
//{
//    return this->server->peerAddress().toString();
//}

QString Peer::getAddress(Participant* p)
{
    return this->participants.value(p)->peerAddress().toString();
}

qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}

QByteArray IntToArray(qint32 source)
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
