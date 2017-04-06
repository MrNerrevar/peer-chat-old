#include "chatmanager.h"
#include "message.h"
#include "chat.h"
#include "peer.h"
#include <cstdlib>

ChatManager::ChatManager(QObject *parent) : QObject(parent)
{
    Chats = QHash<Chat*, std::vector<Participant*>>();
}

bool ChatManager::Join(Message* m)
{
    if(!m->Data.contains(Message::JoinMessage))
        return false;

    auto dataCopy = QString(m->Data);
    auto chatPhrase = dataCopy.replace(Message::JoinMessage, "");
    bool chatExist = false;

    if(chatPhrase.contains("new"))
        chatExist = false;
    else
    {
        auto indexOf = dataCopy.indexOf(Message::Terminator);
        dataCopy.replace(indexOf, dataCopy.length() - indexOf);
        bool ok;
        auto chatId = chatPhrase.toLong(&ok);
        chatExist = this->doesChatExist(chatId);
    }

    if(chatExist)
    {
        auto indexOf = dataCopy.indexOf(Message::Terminator);
        dataCopy.replace(indexOf, dataCopy.length() - indexOf);
        bool ok;
        auto chatId = chatPhrase.toLong(&ok);
        auto c = this->getChat(chatId);
        if(c != NULL)
            this->addParticipant(c, m, QString::number(chatId));
        return true;
    }
    else
    {
        auto chatId = generateId();
        auto newChat = new Chat();
        newChat->Id = chatId;
        auto ps = std::vector<Participant*>();
        ps.push_back(m->Sender);
        Chats.insert(newChat, ps);
        this->addParticipant(newChat, m, QString::number(chatId));
        return true;
    }
    return false;
}

Message* ChatManager::createJoinMessage(Participant* pa)
{
    auto m = new Message();
    m->setData(Message::JoinMessage + "new" + Message::Terminator);
    m->Sender = peer->getParticipant();
    m->Receiver = pa;
    return m;
}

Chat* ChatManager::CreateChat(Participant* pa)
{
    auto chatId = generateId();
    auto newChat = new Chat();
    newChat->Id = chatId;
    auto ps = std::vector<Participant*>();
    ps.push_back(pa);
    Chats.insert(newChat, ps);
    auto m = createJoinMessage(pa);
    peer->writeMessage(m);
    emit readMessage(m);
    return newChat;
}

bool ChatManager::addParticipant(Chat* c, Message* m, QString s)
{
    Chats[c].push_back(m->Sender);
    auto reply = Message();
    reply.setData(Message::JoinRespondMessage + s + Message::Terminator);
    reply.Sender = peer->getParticipant();
    reply.Receiver = m->Sender;
    peer->writeMessage(&reply);
    emit readMessage(m);
    return true;
}

bool ChatManager::ManageMessage(Message* m)
{
    if(!m->Data.contains(Message::ChatMessage))
        return false;

    auto dataCopy = m->Data;
    dataCopy.replace(Message::ChatMessage, "");
    auto indexOf = dataCopy.indexOf(Message::Terminator);
    dataCopy.replace(indexOf, dataCopy.length() - indexOf);

    bool ok;
    auto chatId = dataCopy.toLong(&ok);
    auto chat = this->getChat(chatId);
    if(chat != NULL)
    {
        chat->Messages.push_back(m);
        emit readMessage(m);
        return true;
    }
    return false;
}

bool ChatManager::sendMessage(Message* m, Chat* c)
{
    if(c == NULL)
        return false;

    for(auto ps : Chats[c])
    {
        m->Receiver = ps;
        peer->writeMessage(m);
    }
    return true;
}

bool ChatManager::doesChatExist(qint64 i)
{
    for(auto c : this->Chats.keys())
    {
        if(c->Id == i)
            return true;
    }
    return false;
}

qint64 ChatManager::generateId()
{
    qint64 newId;
    do
    {
        newId = (static_cast<qint64>(rand()) << (sizeof(qint32) * 8)) | rand();
    }while(this->doesChatExist(newId));
    return newId;
}

Chat* ChatManager::getChat(qint64 i)
{
    for(auto c : this->Chats.keys())
    {
        if(c->Id == i)
            return c;
    }
    return NULL;
}

Chat* ChatManager::getChatWithParticipant(Participant* pa)
{
    for(auto ps : this->Chats.values())
    {
        for(auto p : ps)
        {
            if(p->Name == pa->Name)
                return Chats.key(ps);
        }
    }
    return NULL;
}
