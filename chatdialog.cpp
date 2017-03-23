#include <QtWidgets>

#include "chatdialog.h"
#include "peer.h"
#include "message.h"
#include "participantmanager.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    lineEdit->setFocusPolicy(Qt::StrongFocus);
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setReadOnly(true);
    listWidget->setFocusPolicy(Qt::NoFocus);

    this->peer = new Peer();

    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(peer, SIGNAL(readMessage(Message*)), this, SLOT(appendMessage(Message*)));
    this->initParticipants();

    tableFormat.setBorder(0);
}

void ChatDialog::initParticipants()
{
    auto p = new Participant("Jake", "localhost", 1024);
    ParticipantManager::addParticipant(p);
    peer->setParticipant(p);
    newParticipant(p->Name);

    p = new Participant("George", "localhost", 1024);
    ParticipantManager::addParticipant(p);
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
    if (m->isEmpty())
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
    m->Receiver = ParticipantManager::getParticipant("George");

    if(!peer->connectTo(ParticipantManager::getParticipant("George")))
        peer->connectTo(ParticipantManager::getParticipant("George"));

    if(peer->writeMessage(m))
        appendMessage(m);

    //writeToFile(myNickName, text);

    lineEdit->clear();
}

void ChatDialog::writeToFile(QString &nick, QString &msg)
{
    QString chatFile="/home/jake/Documents/network-chat/chat.txt";
    QFile file(chatFile);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream(&file);
        stream << nick << ": " << msg << endl;
    }
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
