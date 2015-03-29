#include "bighandle.h"

BigHandle::BigHandle(QObject *parent) :
    QObject(parent)
{
    m_h=0;
    m_qw=0;
}

void BigHandle::setHandle(HANDLE h)
{
    m_h=h;
}

HANDLE BigHandle::getHandle()
{
    return m_h;
}

void BigHandle::sendSignal(QByteArray mes)
{
    emit needAdd(mes);
}

void BigHandle::setWidget(QWidget* qw)
{
    m_qw=qw;
}

QWidget* BigHandle::getWidget()
{
    return m_qw;
}
