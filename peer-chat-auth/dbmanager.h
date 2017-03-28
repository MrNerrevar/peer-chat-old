#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtCore>
#include <QtNetwork>
#include <QtSql>
#include <QObject>

class DbManager: public QObject
{
    Q_OBJECT
public:
    DbManager(QObject *parent = 0);

    void buildDB();
    void addUser(QString user, QString pass, QString ip);
    void authenticateUser(QString user, QString pass);

signals:
    void authenticatedUser(QString);

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
