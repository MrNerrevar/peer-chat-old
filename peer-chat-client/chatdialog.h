#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include "ui_chatdialog.h"

class Peer;
class Message;
class ChatManager;
class Chat;
class ChatDialog : public QDialog, private Ui::ChatDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = 0);

public slots:
    void appendMessage(Message*);

private slots:
    void returnPressed();
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);

private:
    void initParticipants();
    void initManagers();
    void initConnections();

    QTextTableFormat tableFormat;
    Peer* peer;
    //chatBackup* chatbackup;
    ChatManager* manager;
    Chat* activeChat;
};

#endif
