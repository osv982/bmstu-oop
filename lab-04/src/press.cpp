#include "press.hpp"

Press::Press(Brain &brain, int floor)
    : m_brain(brain), m_floor(floor)
{
    connect(this, &Press::selected, &m_brain, &Brain::setSelected);

    connect(&m_brain, &Brain::opening, [this]()
    {
        if (m_brain.floor() == m_floor)
            setReleased();
    });
}

int Press::floor() const
{
    return m_floor;
}

void Press::setSelected()
{
    if (m_state == State::Released)
    {
        qDebug() << "Press: selected -" << m_floor;

        // Меняем состояние
        m_state = State::Selected;

        // Сообщаем
        emit selected(m_floor);
    }
}

void Press::setReleased()
{
    if (m_state == State::Selected)
    {
        qDebug() << "Press: released -" << m_floor;

        // Меняем состояние
        m_state = State::Released;

        // Сообщаем
        emit released(m_floor);
    }
}