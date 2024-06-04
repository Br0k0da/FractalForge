#include "fractaltype.h"

FractalType::FractalType(QObject *parent)
    : QObject{parent}
{}

int FractalType::fractalFromList() const
{
    return m_fractalFromList;
}

void FractalType::setFractalFromList(int newFractalFromList)
{
    if (m_fractalFromList == newFractalFromList)
        return;
    m_fractalFromList = newFractalFromList;
    emit fractalFromListChanged();
}
