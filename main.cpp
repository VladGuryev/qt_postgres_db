#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

//https://habr.com/en/post/168601/
//https://habr.com/en/post/128836/
//https://ru.opensuse.org/QT_%D0%B8_%D0%91%D0%B0%D0%B7%D1%8B_%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D1%85
//https://habr.com/en/post/51650/
//https://habr.com/en/post/128836/   очень неплохо описано

//psql -d test -U postgres -h localhost -p 5433
//conninfo
// \c database;
// \dt
//  QString lCSql2 = QString("SELECT current_database();");
// QString lCSql2 = QString("SELECT * FROM current_catalog;");

using namespace std;

int main(int argc, char *argv[])
{
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
  db.setHostName("localhost");
  db.setPort(5433); //на разных портах разные базы c одинаковым названием, лолчто
  db.setDatabaseName("test");
  db.setUserName("postgres");
  db.setPassword("postgres");
  bool connected = db.open();
  if(connected){
    qDebug() << "Successfull connection to DB" << endl;
  } else{
    qDebug() << db.lastError().text() << endl;
  }
  QSqlQuery query(db);   //DON'T call prepare() with no binding values
  QString query_string = QString("SELECT table_name "
                                 "FROM information_schema.tables "
                                 "WHERE table_schema "
                                 "NOT IN ('information_schema','pg_catalog');");

  query.exec(query_string);

  query_string = QString("SELECT datname FROM pg_database;");
  query_string = QString("SELECT * FROM courses;");
  query.exec(query_string);

  QSqlError error = query.lastError();
  if (error.type() == QSqlError::NoError) {
      while(query.next()) {
       qDebug() << query.value(0).toString();
      }
  } else {
      qDebug() << error.text();
  }

  return 0;
}
