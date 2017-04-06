#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <vector>
#include <QtCore>

class Chat;
class Message;
class Participant;
class Peer;
class ChatManager : public QObject
{
    Q_OBJECT
public:
    explicit ChatManager(QObject *parent = 0);

    QHash<Chat*, std::vector<Participant*>> Chats;
    Participant* Owner;
    Peer* peer;

    Chat* CreateChat(Participant*);
    Chat* getChatWithParticipant(Participant*);
signals:
    void readMessage(Message*);
public slots:
    bool Join(Message*);
    bool ManageMessage(Message*);

    bool sendMessage(Message*, Chat*);
private:
    bool doesChatExist(qint64 i);
    Chat* getChat(qint64 i);
    bool addParticipant(Chat*, Message*, QString);
    qint64 generateId();
    //Chat* getChatWithParticipant(Participant*);

    Message* createJoinMessage(Participant*);
};

#endif // CHATMANAGER_H
