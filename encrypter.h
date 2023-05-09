
#ifndef ENCRYPTER_H
#define ENCRYPTER_H


#include <QObject>

#include <QString>
#include <QVector>
#include <QByteArray>

#include <QDebug>

struct EncryptionAlgorithm;

class Encrypter//: public QObject
{
public:
    enum alg {
        VERNAM
    };

    Encrypter();

    EncryptionAlgorithm& operator() (const alg& type);

private:
    QVector<EncryptionAlgorithm*> v_algorithms;
};



struct EncryptionAlgorithm //: public QObject
{
    virtual QString operator() (const QString&) {return "";}
    virtual QString Decrypt (const QString&) {return "";}

    virtual void SetKey(QString key) {this->key = key;}

    //EncryptionAlgorithm () : QObject(nullptr) {}

protected:
    QString key;

};


struct Vernam : public EncryptionAlgorithm
{
    Vernam();

    virtual QString operator() (const QString&)	override;
    virtual QString Decrypt (const QString&) override;

    int keyIndex(int index);
};


#endif // ENCRYPTER_H
