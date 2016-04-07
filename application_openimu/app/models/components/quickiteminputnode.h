#ifndef QUICKITEMINPUTNODE_H
#define QUICKITEMINPUTNODE_H

#include "inputnode.h"
#include "abstractinputnode.h"
#include <QQuickItem>
#include <QList>

class QuickItemInputNodeInt: public QQuickItem, public InputNode<int>
{
    Q_OBJECT
    Q_PROPERTY(QList<int> value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString id READ getId WRITE setId)
public:
    QuickItemInputNodeInt(): InputNode<int>() {id = "";}

    void Put(std::vector<int> value){
        this->value = QList<int>::fromVector(QVector<int>::fromStdVector(value));
        emit valueChanged(this->value);
    }


    QString getId(){return id;}
    void setId(QString i){id = i; this->SetStringID(i.toUtf8().constData());}

    QList<int> getValue() const {return value;}

    void setValue(QList<int> v){value = v;}

//private:
    QString id;
    QList<int> value;

signals:
    valueChanged(QList<int>);
};


class QuickItemInputNodeDouble: public QQuickItem, public InputNode<double>
{
    Q_OBJECT
    Q_PROPERTY(QList<double> value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString id READ getId WRITE setId)
public:
    QuickItemInputNodeDouble(): InputNode<double>() {id = "";}

    void Put(std::vector<double> value){
        this->value = QList<double>::fromVector(QVector<double>::fromStdVector(value));
        emit valueChanged(this->value);
    }


    QString getId(){return id;}
    void setId(QString i){id = i; this->SetStringID(i.toUtf8().constData());}

    QList<double> getValue() const {return value;}

    void setValue(QList<double> v){value = v;}

//private:
    QString id;
    QList<double> value;

signals:
    valueChanged(QList<double>);
};



#endif // QUICKITEMINPUTNODE_H
