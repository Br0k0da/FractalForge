#include "buttoncontroller.h"

ButtonController::ButtonController(QObject *parent)
    : QObject{parent}
{}

int ButtonController::fractalType() const
{
    return m_fractalType;
}

void ButtonController::setFractalType(int newFractalType)
{
    if (m_fractalType == newFractalType)
        return;
    m_fractalType = newFractalType;
    emit fractalTypeChanged();
}
