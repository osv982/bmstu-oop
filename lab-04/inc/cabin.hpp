#pragma once

#include "timed.hpp"

class Cabin : Timed
{
    Q_OBJECT

public:

    enum class State
    {

    };

    //! Кабина лифта
    Cabin() = default;

private:

    //! Состояние
    State m_state;
};