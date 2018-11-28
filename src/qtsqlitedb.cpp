#include "qtsqlitedb.h"

QtSqliteDb::QtSqliteDb(QString dbName, QString dirPath, QString ext)
{
    this->Connect(dbName, dirPath, ext);
}
QtSqliteDb::~QtSqliteDb()
{
    this->Disconnect();
}
void QtSqliteDb::Connect(QString dbName, QString dirPath, QString ext)
{
    if (!QSqlDatabase::contains(dbName)) {
        this->Disconnect();
        this->dbName = dbName;
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", this->dbName);
        QString dbPath = QDir(dirPath).filePath(this->dbName + "." + ext);
        db.setDatabaseName(dbPath);
        qDebug () << "dbPath:" << dbPath;
    }
}
void QtSqliteDb::Disconnect()
{
    QSqlDatabase::removeDatabase(this->dbName);
}
QSqlQuery QtSqliteDb::Query(QString query)
{
    QSqlDatabase db = QSqlDatabase::database(this->dbName);
    db.transaction();
    try {
        QSqlQuery q(db);
        /*
        query.prepare("insert into Memo (Memo, DateTime) values (?, ?)");
        for (int i = 0; i < record.size(); i++) {
            query.bindValue(i, record[i]);
        }
        query.exec();
//        throw "SomeException";
        */
        q.exec(query);
        db.commit();
        qDebug() << "QSqlDatabase::commit(): " << query;
        return q;
    } catch (...) {
        qDebug() << "QSqlDatabase::rollback(): " << query;
        db.rollback();
    }
}
