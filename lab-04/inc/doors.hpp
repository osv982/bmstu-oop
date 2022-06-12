#pragma once

#include "timed.hpp"

class Doors : public Timed
{
    Q_OBJECT

public:

    enum class State
    {
        Staying,
        Opening,
        Waiting,
        Closing,
    };

    //! Двери лифта
    Doors() = default;

public slots:

    void setStaying();
    void setOpening();
    void setWaiting();
    void setClosing();

signals:

    void staying();
    void opening();
    void waiting();
    void closing();

private:

    //! Состояние
    State m_state = State::Staying;
};