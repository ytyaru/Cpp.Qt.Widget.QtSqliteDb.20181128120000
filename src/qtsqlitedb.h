#ifndef QTSQLITEDB_H
#define QTSQLITEDB_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <string>

class QtSqliteDb
{
public:
    QtSqliteDb(QString dbName="MyDb", QString dirPath="./", QString ext="sqlite3");
    ~QtSqliteDb();
    void Connect(QString dbName="MyDb", QString dirPath="./", QString ext="sqlite3");
    void Disconnect();
    QSqlQuery Query(QString query);
private:
    QString dbName;
};

#endif // QTSQLITEDB_H
