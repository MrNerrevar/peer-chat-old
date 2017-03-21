#include "client.h"
#include "message.h"

static inline QByteArray IntToArray(qint32 source);

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
}

bool Client::connectToHost(QString host)
{
    socket->connectToHost(host, 1024);
    return socket->waitForConnected();
}

bool Client::writeData(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(IntToArray(data.size())); //write size of data
        socket->write(data); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}

bool Client::writeMessage(Message* m)
{
    m->Sender = *(this->me);
    return this->writeData(m->toByteArray());
}

void Client::setParticipant(Participant* p)
{
    this->me = p;
}

Participant* Client::getParticipant()
{
    return this->me;
}

QByteArray Client::readData()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        return socket->readAll();
    return QByteArray();
}

Message* Client::readMessage()
{
    auto bytes = readData();
    auto message = new Message();
    message->fromRawString(QString(bytes));
    return message;
}

QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}


