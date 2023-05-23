
#include "calendar.h"

Calendar::Calendar(AppEngine* engine, QObject *parent) :
    QAbstractTableModel{parent},
    p_AppEngine(engine)
{
    QDate date = QDate::currentDate();
    i_CurMonth = date.month();
    i_CurYear = date.year();

    connect(&engine->GetClient(), &Client::onGetHolidays, this, &Calendar::GetCalendar);
}

int Calendar::GetDayNumber (int day, int month, int  year)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    year -= month < 3;

    int dayNumber = ( year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;

    // we start from mondey
    if (dayNumber == 0)
        return SUNDAY;

    return dayNumber - 1;
}

int Calendar::GetNumbersOfDays (int monthNumber, int year)
{
    if (monthNumber == JANUARY)
        return (31);

    if (monthNumber == FEBRUARY)
    {
        // If the year is leap then February has
        // 29 days
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
            return (29);
        else
            return (28);
    }

    if (monthNumber == MARCH)
        return (31);

    if (monthNumber == APRIL)
        return (30);

    if (monthNumber == MAY)
        return (31);

    if (monthNumber == JUNE)
        return (30);

    if (monthNumber == JULY)
        return (31);

    if (monthNumber == AUGUST)
        return (31);

    if (monthNumber == SEPTEMBER)
        return (30);

    if (monthNumber == OCTOBER)
        return (31);

    if (monthNumber == NOVEMBER)
        return (30);

    if (monthNumber == DECEMBER)
        return (31);

    return 0;
}

QString Calendar::getMonthName (int monthNumber)
{
    if (monthNumber < JANUARY && monthNumber > DECEMBER)
        return "";
    return v_Months[monthNumber - 1];
}


int Calendar::rowCount(const QModelIndex &parent) const
{
    return v_Dates.size();
}

int Calendar::columnCount(const QModelIndex &parent) const
{
    return GetNumbersOfDays(i_CurMonth, i_CurYear);
}

QHash<int, QByteArray> Calendar::roleNames() const
{
    return {{Qt::DisplayRole, "display"}};
}

QVariant Calendar::data(const QModelIndex &index, int role) const
{
    //qDebug();
    if (index.row() >= v_Dates.size())
        return false;

    //qDebug() << "Calendar::data " << index << role;


    if (role == Qt::DisplayRole)
    {
        if (index.row() > v_Dates.size())
            return false;

        auto dateOfUser = v_Dates[index.row()];
        auto it = std::find_if(dateOfUser.begin(), dateOfUser.end(), [this, &index](const QDate& date)
           {
                //return date.year() == i_CurYear && date.month() == (i_CurMonth + 1) && date.day() == index.column();
                return date.day() == index.column() + 1;
           });

        if (it != dateOfUser.end())
        {
            //qDebug() << true;
            return true;
        }
    }

    return false;
}

QVariant Calendar::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant("");

    if (orientation == Qt::Horizontal)
    {
        return section + 1;
    }
    if (orientation == Qt::Vertical)
    {
        //if (section == 0)
        //    return QVariant("");
        return v_Users[section];
    }
    return QVariant("");
}

void Calendar::getCalendar(int month, int year)
{

}

void Calendar::setDate(int month, int year)
{
    i_CurMonth = month;
    i_CurYear = year;
}

void Calendar::dateNext()
{
    qDebug();
    i_CurMonth++;
    if (i_CurMonth > DECEMBER)
    {
        i_CurMonth = JANUARY;
        i_CurYear++;
    }
}

void Calendar::datePrev()
{
    qDebug();
    i_CurMonth--;
    if (i_CurMonth < JANUARY)
    {
        i_CurMonth = DECEMBER;
        i_CurYear--;
    }
}

void Calendar::setHoliday(int day, int row)
{
    //qDebug() << day << " " << row;
    day += 1;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    QDate date(i_CurYear, i_CurMonth, day);

    auto it = std::find_if(v_Dates[row].begin(), v_Dates[row].end(), [this, day](const QDate& date)
        {
            //return date.year() == i_CurYear && date.month() == (i_CurMonth + 1) && date.day() == day;
            return date.day() == day;
        });

    if (it != v_Dates[row].end())
        v_Dates[row].erase(it);
    else
        v_Dates[row].push_back(date);

    p_AppEngine->setHolidayRequest(date, v_Users[row]);

    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Users.size() - 1, GetNumbersOfDays(i_CurMonth, i_CurYear)), {Qt::DisplayRole});
}

int Calendar::month()
{
    return i_CurMonth;
}

void Calendar::setMonth(const int &month)
{
    i_CurMonth = month;
}

int Calendar::year()
{
    qDebug() << i_CurYear;
    return i_CurYear;
}

void Calendar::setYear(const int &year)
{
    i_CurYear = year;
}

void Calendar::GetCalendar(QVector<QString>& users, QVector<QVector<QDate>>& dates)
{
    v_Users = users;
    v_Dates = dates;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    endInsertRows();

    emit dataChanged(index(0, 0), index(v_Users.size() - 1, GetNumbersOfDays(i_CurMonth, i_CurYear)), {Qt::DisplayRole});
}
