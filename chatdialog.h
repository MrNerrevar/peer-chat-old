#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include "ui_chatdialog.h"
#include "client.h"
#include "server.h"

class ChatDialog : public QDialog, private Ui::ChatDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);

public slots:
    void appendMessage(Message*);

private slots:
    void getLocalIP();
    void returnPressed();
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);
    void writeToFile(QString &nick, QString &msg);

private:
    QString myNickName;
    QTextTableFormat tableFormat;
    Client client;
    Server server;
};

#endif
