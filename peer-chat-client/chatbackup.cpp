/*#include "chatbackup.h"

chatBackup::chatBackup()
{

}

void chatBackup::writeToFile(Message* msg)
{
    if (msg->isEmpty())
            return;

    QString chatFile="/home/chat.txt";
    QFile file(chatFile);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream(&file);
        stream << msg->Time.toString
               << msg->Sender->Name.toString
               << msg->Data.toString;
    }
}
*/
