#include "chat.h"
#include "message.h"
#include "participant.h"

Chat::Chat(QObject *parent) : QObject(parent)
{
    this->Messages = std::vector<Message*>();
    this->Participants = std::vector<Participant*>();
    this->Id = -1;
}
