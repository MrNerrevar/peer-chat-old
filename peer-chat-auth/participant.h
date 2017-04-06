#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QObject>

class Participant
{
public:
    Participant();

    QString Name;
    QString Host;
    qint16 Port;
    int Status;

    const int NameKnown = 1;
    const int HostKnown = 2;

    static QString UnidentifiedName;
    static QString UnidentifiedHost;
    static qint16 UnidentifiedPort;

    bool isEmpty();
    bool setHost(QString, qint16);
    bool setName(QString);
    bool isWellKnown();
};

#endif // PARTICIPANT_H
