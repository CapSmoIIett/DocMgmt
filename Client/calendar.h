
#ifndef CALENDAR_H
#define CALENDAR_H


#include <QAbstractTableModel>
#include <QObject>

#include <appengine.h>


class Calendar : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(int month READ month WRITE setMonth)
    Q_PROPERTY(int year READ year WRITE setYear)

public:
    Calendar(AppEngine* engine, QObject *parent = nullptr);

    static int GetDayNumber (int day, int month, int  year);
    static int GetNumbersOfDays (int monthNumber, int year);
    Q_INVOKABLE QString getMonthName (int monthNumber);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Q_INVOKABLE void getCalendar(int month, int year);
    Q_INVOKABLE void setDate(int month, int year);
    Q_INVOKABLE void dateNext();
    Q_INVOKABLE void datePrev();


    Q_INVOKABLE void setHoliday(int day, int row);

    int month();
    void  setMonth(const int &);

    int year();
    void setYear(const int &);


public slots:
    void GetCalendar(QVector<QString>& users, QVector<QVector<QDate>>& dates);

private:

    int i_CurMonth;
    int i_CurYear;

    AppEngine* p_AppEngine;
    QVector<QVector<QDate>> v_Dates;
    QVector<QString> v_Users;

    const static inline QVector<QString> v_Months =
    {
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };
};

#define JANUARY 	1
#define FEBRUARY	2
#define MARCH		3
#define APRIL		4
#define MAY			5
#define JUNE		6
#define JULY		7
#define AUGUST		8
#define SEPTEMBER	9
#define OCTOBER		10
#define NOVEMBER	11
#define DECEMBER	12

#define MONDAY		0
#define TUESDAY		1
#define WEDNESDAY	2
#define THURSDAY	3
#define FRIDAY		4
#define SATURDAY	5
#define SUNDAY		6

#endif // CALENDAR_H
