#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <iostream>

//https://habr.com/en/post/128836/
//https://ru.opensuse.org/QT_%D0%B8_%D0%91%D0%B0%D0%B7%D1%8B_%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D1%85
//https://habr.com/en/post/51650/

using namespace std;

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
//  qDebug() << QSqlDatabase::drivers();

  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
  db.setHostName("localhost");
  db.setDatabaseName("test");
  db.setUserName("postgres");
  db.setPassword("mypass");
  bool connected = db.open();
  if(connected){
    qDebug() << "OK Successfull!" << endl;
  } else{
    qDebug() << db.lastError().text();
    return a.exec();
  }
  QSqlQuery query;
  query.exec("SELECT id, name, salary FROM test WHERE salary>=1000");

  if (!query.isActive())
     qDebug() <<
         "Database Error" +
          query.lastError().text() << endl;


  return a.exec();
}
