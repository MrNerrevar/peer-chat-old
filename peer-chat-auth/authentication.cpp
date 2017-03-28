#include "authentication.h"
#include "peer.h"
#include "message.h"
#include "participantmanager.h"
#include "dbmanager.h"
#include <QObject>
#include <QString>

Authentication::Authentication()
{
    qDebug() << "Starting auth";
    this->peer = new Peer();
    connect(peer, SIGNAL(readMessage(Message*)), this, SLOT(checkUser(Message*)));

    this ->dbmanager = new DbManager();
    connect(dbmanager, SIGNAL(authenticatedUser(QString)), this, SLOT(sendAuthenticate(QString)));

    //dbmanager->buildDB();
    this->initParticipants();
}

void Authentication::initParticipants()
{
    qDebug() << "Initialising Participants";
    auto p = ParticipantManager::newParticipant("Auth", "localhost", 1023);
    peer->setParticipant(p);

    dbmanager->buildDB();
    //dbmanager->addUser("Jake", "pass", "192.168.0.10");
}

void Authentication::checkUser(Message* m)
{
    qDebug() << "Checking user";
    if(m == NULL || m->isEmpty())
    {
        qDebug() << "Message is null or empty";
        return;
    }

    qDebug() << "assigning message details";
    QString user = m->Sender->Name;
    QString pass = m->Data;
    QString ip = peer->getAddress(m->Sender);

    qDebug() << user << pass << ip;
    qDebug() << "about to authenticate";
    dbmanager->authenticateUser(user, pass);
}

void Authentication::sendAuthenticate(QString user)
{
    auto m = new Message();
    m->setData("authenticated");
    m->Receiver = ParticipantManager::getParticipant(user);

    if(!m->Receiver->isWellKnown())
        return;

    if(!peer->connectTo(ParticipantManager::getParticipant(user)))
        peer->connectTo(ParticipantManager::getParticipant(user));

    if(peer->writeMessage(m))
    {
        qDebug() << "Sending auth message";
        //appendMessage(m);
        //chatbackup->writeToFile(m);
    }
}
