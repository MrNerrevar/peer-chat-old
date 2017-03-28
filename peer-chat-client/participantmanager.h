#ifndef PARTICIPANTMANAGER_H
#define PARTICIPANTMANAGER_H

#include <vector>
#include <QString>

class Participant;
class ParticipantManager
{
public:
    static std::vector<Participant*> Participants;

    static bool isParticipantRegistered(QString s);

    static Participant* newParticipant(QString n, QString h, qint16 p);
    static Participant* newParticipant(QString n);
    static Participant* newParticipant(QString h, qint16 p);

    static Participant* getParticipant(QString n, QString h, qint16 p);
    static Participant* getParticipant(QString n);
    static Participant* getParticipant(QString h, qint16 p);
};

#endif // PARTICIPANTMANAGER_H
