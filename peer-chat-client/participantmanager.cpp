#include "participantmanager.h"
#include "participant.h"
#include <algorithm>

std::vector<Participant*> ParticipantManager::Participants;

bool ParticipantManager::isParticipantRegistered(QString s)
{
    return std::any_of(Participants.begin(), Participants.end(), [s](Participant* p){ return p->Name == s; });
}


Participant* ParticipantManager::getParticipant(QString n, QString h, qint16 p)
{
    auto f = std::find_if(Participants.begin(), Participants.end(), [n, h, p](Participant* pa) { return pa->Name == n && pa->Host == h && pa->Port == p; });
    if(f != Participants.end())
        return Participants[std::distance(Participants.begin(), f)];
    return newParticipant(n, h, p);
}

Participant* ParticipantManager::getParticipant(QString n)
{
    auto f = std::find_if(Participants.begin(), Participants.end(), [n](Participant* p) { return p->Name == n; });
    if(f != Participants.end())
        return Participants[std::distance(Participants.begin(), f)];
    return newParticipant(n);
}

Participant* ParticipantManager::getParticipant(QString h, qint16 p)
{
    auto f = std::find_if(Participants.begin(), Participants.end(), [h, p](Participant* pa) { return pa->Host == h && pa->Port == p; });
    if(f != Participants.end())
        return Participants[std::distance(Participants.begin(), f)];
    return newParticipant(h, p);
}

Participant* ParticipantManager::newParticipant(QString n, QString h, qint16 p)
{
    auto f = std::find_if(Participants.begin(), Participants.end(), [n](Participant* p) { return p->Name == n; });
    if(f != Participants.end())
    {
        auto pa = *f;
        if(pa->Host == Participant::UnidentifiedHost)
            pa->setHost(h, p);
        return pa;
    }

    f = std::find_if(Participants.begin(), Participants.end(), [h, p](Participant* pa) { return pa->Host == Participant::LocalHost && pa->Port == p && pa->Host == h; });
    if(f == Participants.end())
    {
        auto pa = new Participant();
        pa->setName(n);
        pa->setHost(h, p);
        Participants.push_back(pa);
        return pa;
    }

    f = std::find_if(Participants.begin(), Participants.end(), [h](Participant* p) { return p->Host == h; });
    if(f != Participants.end())
    {
        auto pa = *f;
        if(pa->Name == Participant::UnidentifiedName)
            pa->setName(n);
        return pa;
    }

    auto pa = new Participant();
    pa->setName(n);
    pa->setHost(h, p);
    Participants.push_back(pa);
    return pa;
}

Participant* ParticipantManager::newParticipant(QString n)
{
    return newParticipant(n, Participant::UnidentifiedHost, Participant::UnidentifiedPort);
}

Participant* ParticipantManager::newParticipant(QString h, qint16 p)
{
    return newParticipant(Participant::UnidentifiedHost, h, p);
}
