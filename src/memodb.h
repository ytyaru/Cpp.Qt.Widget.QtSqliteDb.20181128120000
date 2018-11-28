#ifndef MEMODB_H
#define MEMODB_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QDebug>
#include <QDir>

class MemoDb
{
public:
    MemoDb(QString path="./");
    ~MemoDb();
    void Open(QString path="./");
    void Close();
    void Write(QStringList record);
private:
    QString dbName;
    QString dbPath;
    bool IsExsistTable();
    void CreateTable();
};

#endif // MEMODB_H
