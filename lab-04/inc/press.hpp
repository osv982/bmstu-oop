#pragma once

#include "brain.hpp"
#include "timed.hpp"

class Press : Timed
{
    Q_OBJECT

public:

    enum class State
    {

    };

    //! Кнопка лифта
    Press(Brain &, int);

private:

    //! Контроллер
    Brain &m_brain;

    //! Состояние
    State m_state;

    //! Номер этажа
    const int m_floor;
};