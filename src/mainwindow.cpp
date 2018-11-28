#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "memodb.h"
#include "qtsqlitedb.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QtSqliteDb db("Memo", QApplication::applicationDirPath());
    db.Query(tr("create table Memo(id INTEGER PRIMARY KEY AUTOINCREMENT, Memo TEXT, Created TEXT)"));
    db.Query(tr("insert into Memo(Memo,Created) values('メモ内容', '1999-12-31 23:59:59')"));
    QSqlQuery query = db.Query(tr("select * from Memo"));
    while (query.next()) {
        qDebug() << query.value(0) << "|" << query.value(1) << "|" << query.value(2);
    }

//    MemoDb memoDb(QApplication::applicationDirPath());
//    qDebug() << QApplication::applicationDirPath();
//    if ("/home/pi" == QApplication::applicationDirPath()) { memoDb.Open("/tmp/work"); }
//    else { memoDb.Open(QApplication::applicationDirPath()); }
//    QStringList record;
//    record.append("ABCDEFG");
//    record.append("2000-01-01 00:00:00.000");
//    memoDb.Write(record);
//    memoDb.Close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
