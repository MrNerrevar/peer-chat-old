#ifndef CHAT_H
#define CHAT_H

#include <vector>
#include <QObject>

class Message;
class Participant;
class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent = 0);
    qint64 Id;
    std::vector<Message*> Messages;
    std::vector<Participant*> Participants;
signals:

public slots:
};

#endif // CHAT_H
