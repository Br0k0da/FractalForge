#ifndef FRACTALTYPE_H
#define FRACTALTYPE_H

#include <QObject>

class FractalType : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int fractalFromList READ fractalFromList WRITE setFractalFromList NOTIFY fractalFromListChanged FINAL)
public:
    explicit FractalType(QObject *parent = nullptr);

    int fractalFromList() const;
    void setFractalFromList(int newFractalFromList);

signals:
    void fractalFromListChanged();
private:
    int m_fractalFromList = 0;
};

#endif // FRACTALTYPE_H
