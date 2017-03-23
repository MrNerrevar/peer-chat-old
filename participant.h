#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QObject>

enum ParticipantStatus
{
    HostUnknown = 1,
    HostKnown = 0
};

class Participant
{
private:
public:
    Participant();
    Participant(QString, QString, qint16);

    QString Name;
    QString Host;
    qint16 Port;
    ParticipantStatus Status;

    bool isEmpty();
};

#endif // PARTICIPANT_H
