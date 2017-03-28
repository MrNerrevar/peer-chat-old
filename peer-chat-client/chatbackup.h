/*#ifndef CHATBACKUP_H
#define CHATBACKUP_H

#include <QObject>
#include "message.h"
#include "peer.h"

class chatBackup
{

public:
    chatBackup();
    enum SaveFormat {Json, Binary};

    void writeToFile(Message* msg);

    void writeBackup();
    void readBackup();
};

#endif // CHATBACKUP_H
*/
