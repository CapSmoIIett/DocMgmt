
#include "encrypter.h"

Encrypter::Encrypter() //:
    //QObject(nullptr)
{
    v_algorithms.push_back(new Vernam());

}


EncryptionAlgorithm& Encrypter::operator() (const alg& type)
{
    qDebug();
    qDebug() << "Vernam::operator()";

    return *v_algorithms[type];
}



Vernam::Vernam ()
{
    //SetKey("hi") ;
    key = "hello";
}


QString Vernam::operator() (const QString& data)
{
    qDebug();
    qDebug() << "Vernam::operator()";
    qDebug() << data;

    int it = 0;
    QString result = "";

    for ( int i = 0; i < data.length(); i++)
    {
        result.append(QString(QChar(QChar(data[i]).unicode()^QChar(key[keyIndex(i)]).unicode())));
    }

    return result;
}

QString Vernam::Decrypt (const QString& data)
{
    qDebug();
    qDebug() << "Vernam::Decrypt";
    qDebug() << data;

    int it = 0;
    QString result = "";

    for ( int i = 0; i < data.length(); i++)
    {
        //qDebug() << QChar(QChar(data[i]).unicode()^QChar(key[keyIndex(i)]).unicode());
        result.append(QChar(QChar(data[i]).unicode()^QChar(key[keyIndex(i)]).unicode()));
    }

    return result;

}

int Vernam::keyIndex(int index)
{
    /*int len = key.size();
    int multiple = index / len;
    if ( index >=  len ) {
        return index - (len * multiple);
    }
    return index;
*/
    return index % key.size();
}
