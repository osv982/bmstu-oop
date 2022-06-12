#pragma once

#include "timed.hpp"

class Doors : Timed
{
    Q_OBJECT

public:

    enum class State
    {

    };

    //! Двери лифта
    Doors() = default;

private:

    State m_state;
};