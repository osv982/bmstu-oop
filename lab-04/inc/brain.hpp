#pragma once

#include "cabin.hpp"
#include "doors.hpp"
#include "timed.hpp"

class Brain : public Timed
{
    Q_OBJECT

public:

    enum class State
    {
        Staying,
        Opening,
        Closing,
        Solving,
        Running,
    };

    //! Контроллер лифта
    Brain(Cabin &, Doors &, int count);

    //! Номер этажа
    int floor() const;

public slots:

    void setSelected(int);

    void setStaying();
    void setOpening();
    void setClosing();
    void setSolving();
    void setRunning();

signals:

    void staying();
    void opening();
    void closing();
    void solving();
    void running();

private:

    //! Решение
    int solve();

    //! Поиск вверх
    int lookUp() const;

    //! Поиск вниз
    int lookDn() const;

    //! Кабина
    Cabin &m_cabin;

    //! Двери
    Doors &m_doors;

    //! Состояние
    State m_state = State::Staying;

    //! Номер этажа
    int m_floor = 1;

    //! Направление
    bool m_climb = true;

    //! Этажи
    QVector<bool> m_asked;
};