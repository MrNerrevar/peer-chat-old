#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDateTime>
#include "participant.h"

class Message
{
public:
    Participant* Sender;
    Participant* Receiver;
    QDateTime Time;
    QString Data;

    Message();
    Message(Participant*, QString);

    void setData(QString d);

    QString toRawString();
    QByteArray toByteArray();
    bool isEmpty();

    Message fromRawString(QString);

    static QString MessageRegex;
    static QString HeaderRegex;
    static QString TrailerRegex;
    static QString NameAndDateRegex;
    static QString NameLastIndexRegex;
    static QString DateLastIndexRegex;
    static QString HeaderIndexRegex;

    static QString JoinMessage;
    static QString JoinFailMessage;
    static QString JoinRespondMessage;
    static QString ChatMessage;
    static QString Terminator;
};

#endif // MESSAGE_H
