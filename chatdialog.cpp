#include <QtWidgets>

#include "chatdialog.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    lineEdit->setFocusPolicy(Qt::StrongFocus);
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setReadOnly(true);
    listWidget->setFocusPolicy(Qt::NoFocus);

    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));

    client.setParticipant(new Participant("Jake", "localhost"));

    myNickName = client.getParticipant()->getName();
    newParticipant(myNickName);

    //client.connectToHost("192.168.0.52");
    //client.writeData(myNickName, myIP);
    tableFormat.setBorder(0);
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
    QTextTable *table = cursor.insertTable(1, 3, tableFormat);
    table->cellAt(0,0).firstCursorPosition().insertText(('[' + m->Time.toString(Qt::SystemLocaleShortDate) + ']'));
    table->cellAt(0, 1).firstCursorPosition().insertText('<' + m->Sender.getName() + "> ");
    table->cellAt(0, 2).firstCursorPosition().insertText(m->Data);
    QScrollBar *bar = textEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void ChatDialog::returnPressed()
{
    QString text = lineEdit->text();
    if (text.isEmpty())
        return;

    client.connectToHost("localhost");

    auto m = new Message();
    m->setData(text);

    client.writeMessage(m);
    appendMessage(m);

    writeToFile(myNickName, text);

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
