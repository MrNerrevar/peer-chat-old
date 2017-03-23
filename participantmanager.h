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
    static Participant* getParticipant(QString s);
    static void addParticipant(Participant*);
};

#endif // PARTICIPANTMANAGER_H
