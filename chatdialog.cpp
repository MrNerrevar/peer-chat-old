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

    myNickName = "Jake";
    newParticipant(myNickName);

    //client.connectToHost("192.168.0.10");

    tableFormat.setBorder(0);
}

void ChatDialog::appendMessage(const QString &from, const QString &message)
{
    if (from.isEmpty() || message.isEmpty())
        return;

    QTextCursor cursor(textEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
    table->cellAt(0, 1).firstCursorPosition().insertText(message);
    QScrollBar *bar = textEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void ChatDialog::returnPressed()
{
    QString text = lineEdit->text();
    if (text.isEmpty())
        return;

    if (text.startsWith(QChar('/'))) {
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::red);
        textEdit->append(tr("! Unknown command: %1")
                         .arg(text.left(text.indexOf(' '))));
        textEdit->setTextColor(color);
    } else {
        client.connectToHost("localhost");
        client.writeData(text.toUtf8());
        appendMessage(myNickName, text);

        writeToFile(myNickName, text);
    }

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
