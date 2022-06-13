#pragma once

#include "timed.hpp"

class Cabin : public Timed
{
    Q_OBJECT

public:

    enum class State
    {
        Staying,
        Started,
        Running,
    };

    //! Кабина лифта
    Cabin() = default;

public slots:

    void setStaying();
    void setStarted();
    void setRunning();

signals:

    void staying();
    void started();
    void running();

private:

    //! Состояние
    State m_state = State::Staying;
};