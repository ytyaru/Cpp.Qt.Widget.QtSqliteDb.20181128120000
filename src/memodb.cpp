#include "memodb.h"

MemoDb::MemoDb(QString path)
{
    this->dbName = QString::fromLocal8Bit("MemoDb");
    this->Open(path);
}

MemoDb::~MemoDb()
{
    this->Close();
}

void MemoDb::Open(QString path)
{
    if (!QSqlDatabase::contains(this->dbName)) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "MemoDb");
        this->dbPath = QDir(path).filePath("memo.sqlite3");
        db.setDatabaseName(this->dbPath);
        qDebug () << "path:" << path;
        qDebug () << "this->dbPath:" << this->dbPath;
        this->CreateTable();
    }
}

void MemoDb::Close()
{
    QSqlDatabase::removeDatabase(this->dbName);
}

bool MemoDb::IsExsistTable()
{
    QSqlDatabase db = QSqlDatabase::database("MemoDb");
    QSqlQuery query(db);
    query.exec("select count(*) from sqlite_master where type='table' and name='Memo'");
    int count = 0;
    while (query.next()) { count = query.value(0).toInt(); }
    if (0 < count) { return true; }
    else { return false; }
}

void MemoDb::CreateTable()
{
    QSqlDatabase db = QSqlDatabase::database(this->dbName);
    if (!this->IsExsistTable()) {
        QSqlQuery query(db);
        query.exec("create table Memo(id INTEGER PRIMARY KEY AUTOINCREMENT, Memo text, DateTime text)");
    }
}

void MemoDb::Write(QStringList record)
{
    QSqlDatabase db = QSqlDatabase::database(this->dbName);
    db.transaction();
    try {
        QSqlQuery query(db);
        query.prepare("insert into Memo (Memo, DateTime) values (?, ?)");
        for (int i = 0; i < record.size(); i++) {
            query.bindValue(i, record[i]);
        }
        query.exec();
//        throw "SomeException";
        db.commit();
        qDebug() << "QSqlDatabase::commit()";
    } catch (...) {
        qDebug() << "QSqlDatabase::rollback()";
        db.rollback();
    }
}
