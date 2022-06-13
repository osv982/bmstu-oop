#include "brain.hpp"

Brain::Brain(Cabin &cabin, Doors &doors)
    : m_cabin(cabin), m_doors(doors)
{
    connect(this, &Brain::opening, &m_cabin, &Cabin::setStaying);
    connect(this, &Brain::running, &m_cabin, &Cabin::setStarted);

    connect(&m_cabin, &Cabin::running, this, &Brain::setSolving);

    connect(&m_cabin, &Cabin::staying, &m_doors, &Doors::setOpening);

    connect(&m_doors, &Doors::closing, this, &Brain::setClosing);
    connect(&m_doors, &Doors::staying, this, &Brain::setSolving);
}

int Brain::floor() const
{
    return m_floor;
}

void Brain::setSelected(int floor)
{
    qDebug() << "Brain: selected -" << floor;

    m_asked[floor - 1] = true;

    if (m_state == State::Staying)
        setSolving();
}

void Brain::setStaying()
{
    if (m_state == State::Solving)
    {
        qDebug() << "Brain: staying";

        // Меняем состояние
        m_state = State::Staying;

        // Сообщаем
        emit staying();
    }
}

void Brain::setOpening()
{
    if (m_state == State::Staying || m_state == State::Closing || m_state == State::Solving)
    {
        qDebug() << "Brain: opening";

        // Меняем состояние
        m_state = State::Opening;

        // Сбрасываем запрос
        m_asked[m_floor - 1] = false;

        // Сообщаем
        emit opening();
    }
}

void Brain::setClosing()
{
    if (m_state == State::Opening)
    {
        qDebug() << "Brain: closing";

        // Меняем состояние
        m_state = State::Closing;

        // Сообщаем
        emit closing();
    }
}

void Brain::setSolving()
{
    if (m_state == State::Staying || m_state == State::Closing || m_state == State::Running)
    {
        qDebug() << "Brain: solving";

        // Меняем состояние
        m_state = State::Solving;

        if (m_asked[m_floor - 1])
            setOpening();

        else
        {
            int floor = solve();

            if (!floor)
                setStaying();

            setRunning();
        }

        // Сообщаем
        emit solving();
    }
}

void Brain::setRunning()
{
    if (m_state == State::Solving)
    {
        qDebug() << "Brain: running";

        // Меняем состояние
        m_state = State::Running;

        if (m_climb)
            m_floor++;

        else
            m_floor--;

        // Сообщаем
        emit running();
    }
}

int Brain::solve()
{
    int floor = 0;

    for (int i = 0; !floor && i < 2; i++)
    {
        floor = m_climb?
            lookUp():
            lookDn();

        if (!floor)
            m_climb = !m_climb;
    }

    return floor;
}

int Brain::lookUp() const
{
    for (int i = m_floor; i < 14; i++)
        if (m_asked[i - 1])
            return i;

    return 0;
}

int Brain::lookDn() const
{
    for (int i = m_floor; i > 0; i--)
        if (m_asked[i - 1])
            return i;

    return 0;
}