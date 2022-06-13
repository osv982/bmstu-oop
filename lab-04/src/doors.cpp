#include "doors.hpp"

void Doors::setStaying()
{
    if (m_state == State::Closing)
    {
        qDebug() << "Doors: staying";

        // Меняем состояние
        m_state = State::Staying;

        // Сообщаем
        emit staying();
    }
}

void Doors::setOpening()
{
    if (m_state == State::Staying || m_state == State::Closing)
    {
        qDebug() << "Doors: opening";

        // Меняем состояние
        m_state = State::Opening;

        // Откладываем переход
        delay(this, SLOT(setWaiting()));

        // Сообщаем
        emit opening();
    }
}

void Doors::setWaiting()
{
    if (m_state == State::Opening)
    {
        qDebug() << "Doors: waiting";

        // Меняем состояние
        m_state = State::Waiting;

        // Откладываем переход
        delay(this, SLOT(setClosing()));

        // Сообщаем
        emit waiting();
    }
}

void Doors::setClosing()
{
    if (m_state == State::Waiting)
    {
        qDebug() << "Doors: closing";

        // Меняем состояние
        m_state = State::Closing;

        // Откладываем переход
        delay(this, SLOT(setStaying()));

        // Сообщаем
        emit closing();
    }
}