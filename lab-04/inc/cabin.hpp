#pragma once

#include "timed.hpp"

class Cabin : public Timed
{
    Q_OBJECT

public:

    enum class State
    {
        Staying,
        Running,
    };

    //! Кабина лифта
    Cabin() = default;

public slots:

    void setStaying();
    void setRunning();

signals:

    void staying();
    void running();

private:

    //! Состояние
    State m_state = State::Staying;
};