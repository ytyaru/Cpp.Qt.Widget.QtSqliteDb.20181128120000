# このソフトウェアについて

　Qt5学習。QtでSQLite3を使うラッパクラスを作ってみた。

## 前回まで

* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Transaction.20181128070000
* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Class.20181127180000
* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Class.20181127170000
* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Class.20181127160000
* https://github.com/ytyaru/Cpp.Qt.Widget.QSql.SQLite3.Class.20181127130000

## コード抜粋

mainwindow.cpp
```cpp
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
}
```

### メリット

* トランザクション処理を書かずに実行できる（だが1トランザクションあたり1Insert文しか渡せないので微妙）
* QSqlDatabaseを一切触らずにDB操作ができる。（だがそのせいでQSqlQueryでクエリ文の作成ができない）

### デメリット

#### 複数のInsertができない

　せっかくトランザクションが使えても意味がない。

QtSqliteDb.cpp
```cpp
QSqlQuery QtSqliteDb::Query(QString query)
{
    QSqlDatabase db = QSqlDatabase::database(this->dbName);
    db.transaction();
    try {
        QSqlQuery q(db);
        q.exec(query);
        db.commit();
        qDebug() << "QSqlDatabase::commit(): " << query;
        return q;
    } catch (...) {
        qDebug() << "QSqlDatabase::rollback(): " << query;
        db.rollback();
    }
}
```

#### QSqlQueryでクエリ文の作成ができない

　以下のようにQSqlQueryでクエリ文の作成ができない。QSqlDatabaseである`db`を隠蔽するため。

```cpp
QSqlQuery query(db);
query.prepare("insert into Memo (Memo, DateTime) values (?, ?)");
for (int i = 0; i < record.size(); i++) {
    query.bindValue(i, record[i]);
}
query.exec();
```

　これが使えてもマッパーには程遠いが。

## Qt要素

* http://doc.qt.io/qt-5/qsql.html
    * http://doc.qt.io/qt-5/qsqldatabase.html
    * http://doc.qt.io/qt-5/qsqlquery.html

# 課題

* マッパーを作りたい

## create table

Db.Model.Memo.cpp
```cpp
class Memo
{
public:
    Memo();
    QVariant Id;
    QVariant Memo;
    QVariant Created;
};
```

```sql
create table Memo(id INTEGER PRIMARY KEY AUTOINCREMENT, Memo TEXT, Created TEXT)
```

* 型や制約をどうやって指定するか
* 外部キー制約はどうするか

## insert

```cpp
data = {Id = 0, Memo = "メモ内容", Create = "2000-01-01 00:00:00.000"};
Memo memo;
memo.Insert(data);
memo.Delete(data);
memo.Update(data);
memo.Select(data);
```

　インタフェースが思いつかない。

# 開発環境

* [Raspberry Pi](https://ja.wikipedia.org/wiki/Raspberry_Pi) 3 Model B+
    * [Raspbian](https://www.raspberrypi.org/downloads/raspbian/) GNU/Linux 9.0 (stretch) 2018-06-27
        * Qt 5.7.1

## 環境構築

* [Raspbian stretch で Qt5.7 インストールしたもの一覧](http://ytyaru.hatenablog.com/entry/2019/12/17/000000)

# ライセンス

　このソフトウェアはCC0ライセンスである。

[![CC0](http://i.creativecommons.org/p/zero/1.0/88x31.png "CC0")](http://creativecommons.org/publicdomain/zero/1.0/deed.ja)

## 利用ライブラリ

ライブラリ|ライセンス|ソースコード
----------|----------|------------
[Qt](http://doc.qt.io/)|[LGPL](http://doc.qt.io/qt-5/licensing.html)|[GitHub](https://github.com/qt)

* [参考1](https://www3.sra.co.jp/qt/licence/index.html)
* [参考2](http://kou-lowenergy.hatenablog.com/entry/2017/02/17/154720)
* [参考3](https://qiita.com/ynuma/items/e8749233677821a81fcc)
