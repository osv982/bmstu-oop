#include "cabin.hpp"

void Cabin::setStaying()
{
    if (m_state == State::Running)
    {
        qDebug() << "Cabin: staying";

        // Меняем состояние
        m_state = State::Staying;

        reset();

        // Сообщаем
        emit staying();
    }
}

void Cabin::setStarted()
{
    if (m_state == State::Staying)
    {
        qDebug() << "Cabin: started";

        // Меняем состояние
        m_state = State::Started;

        // Откладываем переход
        clock(this, SLOT(setRunning()));

        // Сообщаем
        emit started();
    }
}

void Cabin::setRunning()
{
    if (m_state == State::Started || m_state == State::Running)
    {
        qDebug() << "Cabin: running";

        // Меняем состояние
        m_state = State::Running;

        // Сообщаем
        emit running();
    }
}