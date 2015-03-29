#include "bigtext.h"

BigText::BigText(QObject *parent) :
    QObject(parent)
{
    m_pTextForGui=0;
    m_qw=0;
}

void BigText::setString(QString* pStr)
{
    m_pTextForGui=pStr;
}

QString* BigText::getString()
{
    return m_pTextForGui;
}

void BigText::setWidget(QWidget* qw)
{
    m_qw=qw;
}

QWidget* BigText::getWidget()
{
    return m_qw;
}

void BigText::sendSignal(QByteArray mes)
{
    emit needAdd(mes);
}
