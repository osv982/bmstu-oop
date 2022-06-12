#pragma once

#include "brain.hpp"
#include "timed.hpp"

class Press : public Timed
{
    Q_OBJECT

public:

    enum class State
    {
        Selected,
        Released,
    };

    //! Кнопка лифта
    Press(Brain &, int floor);

    //! Номер этажа
    int floor() const;

public slots:

    void setSelected();
    void setReleased();

signals:

    void selected(int floor);
    void released(int floor);

private:

    //! Контроллер
    Brain &m_brain;

    //! Состояние
    State m_state = State::Released;

    //! Номер этажа
    const int m_floor;
};