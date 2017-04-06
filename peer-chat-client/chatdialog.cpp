#include <QtWidgets>

#include "chatdialog.h"
#include "peer.h"
#include "message.h"
#include "participantmanager.h"
#include "chatbackup.h"
#include "chatmanager.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    lineEdit->setFocusPolicy(Qt::StrongFocus);
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setReadOnly(true);
    listWidget->setFocusPolicy(Qt::NoFocus);

    this->peer = new Peer();
    //this->chatbackup = new chatBackup();

    this->initParticipants();
    this->initManagers();

    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    //connect(peer, SIGNAL(readMessage(Message*)), this, SLOT(appendMessage(Message*)));
    connect(peer, SIGNAL(readMessage(Message*)), manager, SLOT(ManageMessage(Message*)));
    connect(peer, SIGNAL(readMessage(Message*)), manager, SLOT(Join(Message*)));
    connect(manager, SIGNAL(readMessage(Message*)), this, SLOT(appendMessage(Message*)));

    tableFormat.setBorder(0);

    this->initConnections();
}

void ChatDialog::initParticipants()
{
    auto p = ParticipantManager::newParticipant("Jake", "localhost", 1024);
    peer->setParticipant(p);
    newParticipant(p->Name);

    p = ParticipantManager::newParticipant("Jarrod", "192.168.0.10-", 1024);
    newParticipant(p->Name);    
}

void ChatDialog::initManagers()
{
    this->manager = new ChatManager(this);
    this->manager->peer = this->peer;
    this->manager->Owner = this->peer->getParticipant();
}

void ChatDialog::initConnections()
{
    //Try for 60 Seconds
    qDebug() << "Waiting to Connect";
    QTime dieTime= QTime::currentTime().addSecs(15);
    while(QTime::currentTime() < dieTime || !peer->connectTo(ParticipantManager::getParticipant("Jarrod")))
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    this->activeChat = manager->CreateChat(ParticipantManager::getParticipant("Jarrod"));
}

void ChatDialog::appendMessage(Message* m)
{
    if (m->Sender == NULL || m->Sender->isEmpty())
        return;

    if (m->Sender->Name == NULL || m->Sender->Name.isEmpty())
        return;

    if (m == NULL || m->isEmpty())
        return;

    QTextCursor cursor(textEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + m->Sender->Name + "> ");
    table->cellAt(0, 1).firstCursorPosition().insertText(m->Data);
    QScrollBar *bar = textEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void ChatDialog::returnPressed()
{
    QString text = lineEdit->text();
    if (text.isEmpty())
        return;

    this->activeChat = manager->getChatWithParticipant(ParticipantManager::getParticipant("Jarrod"));

    auto m = new Message();
    m->setData(text);
    //m->Receiver = ParticipantManager::getParticipant("Auth");

    //if(!m->Receiver->isWellKnown())
    //    return;

    //if(!peer->connectTo(ParticipantManager::getParticipant("Auth")))
    //    peer->connectTo(ParticipantManager::getParticipant("Auth"));

    if(this->activeChat == NULL)
        return;

    if(manager->sendMessage(m, this->activeChat))
        appendMessage(m);

    lineEdit->clear();
}

void ChatDialog::newParticipant(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QColor color = textEdit->textColor();
    textEdit->setTextColor(Qt::gray);
    textEdit->append(tr("* %1 has joined").arg(nick));
    textEdit->setTextColor(color);
    listWidget->addItem(nick);
}

void ChatDialog::participantLeft(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QList<QListWidgetItem *> items = listWidget->findItems(nick,
                                                           Qt::MatchExactly);
    if (items.isEmpty())
        return;

    delete items.at(0);
    QColor color = textEdit->textColor();
    textEdit->setTextColor(Qt::gray);
    textEdit->append(tr("* %1 has left").arg(nick));
    textEdit->setTextColor(color);
}
