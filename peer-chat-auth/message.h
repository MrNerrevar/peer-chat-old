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

    const QString MessageRegex = "(\\[[\\w\\d: \\+\\-]+\\]){2}: [^\\[.\\]]+\\[.\\]";
    const QString HeaderRegex = "(\\[[\\w\\d: \\+\\-]+\\]){2}: ";
    const QString TrailerRegex = "\\[.\\]";
    const QString NameAndDateRegex = "(\\[[\\w\\d: \\+\\-]+\\])";
    const QString NameLastIndexRegex = "\\](\\[[\\w\\d: \\+\\-]+\\]): [^\\[.\\]]+\\[.\\]";
    const QString DateLastIndexRegex = "\\]: [^\\[.\\]]+\\[.\\]";
    const QString HeaderIndexRegex = "[^:\\[.\\]]+\\[.\\]";
};

#endif // MESSAGE_H
