#include "dbmanager.h"
#include "authentication.h"

DbManager::DbManager(QObject *parent) : QObject(parent)
{

}

void DbManager::buildDB()
{
    QString path = QDir::currentPath() + "/users.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query;
    query.exec("create table users "
              "(username varchar(20) primary key, "
              "password varchar(20), "
              "address varchar(15))");
    db.close();
}

void DbManager::addUser(QString user, QString pass, QString ip)
{
    QString path = QDir::currentPath() + "/users.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query;
    query.exec("insert into users "
               "(username, password, address) "
               "values ('" + user + "', '" + pass + "', '" + ip + "')");
    db.close();
}

void DbManager::authenticateUser(QString user, QString pass)
{
    qDebug() << "Authenticating";
    QString path = QDir::currentPath() + "/users.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query;
    query.exec("select password from users where username like '" + user + "'");

   while (query.next())
   {
       QString password = query.value(0).toString();
       if (password == pass)
       {
           qDebug() << "User " << user << "authenticated";

           //authUser = user;
           emit authenticatedUser(user);
       }
   }
   db.close();
}
