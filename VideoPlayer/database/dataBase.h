#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDesktopWidget>
#include <QDebug>


class dataBase
{
public:
    dataBase();

    static bool creatConnection();
};

#endif // DATABASE_H
