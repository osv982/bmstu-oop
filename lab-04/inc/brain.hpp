#pragma once

#include "cabin.hpp"
#include "doors.hpp"
#include "timed.hpp"

class Brain : Timed
{
    Q_OBJECT

public:

    enum class State
    {

    };

    //! Контроллер лифта
    Brain(Cabin &, Doors &);

private:

    //! Кабина
    Cabin &m_cabin;

    //! Двери
    Doors &m_doors;

    //! Состояние
    State m_state;

    //! Номер этажа
    int m_floor = 1;

    //! Направление
    bool m_climb = true;
};