/**
 * \title ButtonController
 * \brief This class provides access to information about the pressed fractal type selection button
 * \authors Tomiks
 * \version 0.1
*/

#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include <QObject>

class ButtonController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int fractalType READ fractalType WRITE setFractalType NOTIFY fractalTypeChanged FINAL)
public:
    explicit ButtonController(QObject *parent = nullptr);

    int fractalType() const;
    void setFractalType(int newFractalType);

signals:
    void fractalTypeChanged();
private:
    int m_fractalType;
};

#endif // BUTTONCONTROLLER_H
