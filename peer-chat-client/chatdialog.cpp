#include <QtWidgets>

#include "chatdialog.h"
#include "peer.h"
#include "message.h"
#include "participantmanager.h"
#include "chatbackup.h"

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

    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(peer, SIGNAL(readMessage(Message*)), this, SLOT(appendMessage(Message*)));
    this->initParticipants();

    tableFormat.setBorder(0);
}

void ChatDialog::initParticipants()
{
    auto p = ParticipantManager::newParticipant("Jake", "localhost", 1024);
    peer->setParticipant(p);
    newParticipant(p->Name);

    p = ParticipantManager::newParticipant("Auth", "localhost", 1023);
    newParticipant(p->Name);

    //peer->connectTo(p);
}

void ChatDialog::getLocalIP()
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
            qDebug() << address.toString();
        }
    }
}

void ChatDialog::appendMessage(Message* m)
{
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

    auto m = new Message();
    m->setData(text);
    m->Receiver = ParticipantManager::getParticipant("Auth");

    if(!m->Receiver->isWellKnown())
        return;

    if(!peer->connectTo(ParticipantManager::getParticipant("Auth")))
        peer->connectTo(ParticipantManager::getParticipant("Auth"));

    if(peer->writeMessage(m))
    {
        appendMessage(m);
        //chatbackup->writeToFile(m);
    }

    //writeToFile(myNickName, text);

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
