#include "participantmanager.h"
#include "participant.h"
#include <algorithm>

std::vector<Participant*> ParticipantManager::Participants;

bool ParticipantManager::isParticipantRegistered(QString s)
{
    return std::any_of(Participants.begin(), Participants.end(), [s](Participant* p){ return p->Name == s; });
}

Participant* ParticipantManager::getParticipant(QString s)
{
    auto f = std::find_if(Participants.begin(), Participants.end(), [s](Participant* p) { return p->Name == s; });
    if(f != Participants.end())
        return Participants[std::distance(Participants.begin(), f)];
    auto p = new Participant(s, "", 0);
    Participants.push_back(p);
    return p;
}

void ParticipantManager::addParticipant(Participant* p)
{
    Participants.push_back(p);
}
