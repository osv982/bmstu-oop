#pragma once

#include <QtCore>

class Timed : QObject
{
    Q_OBJECT

public slots:

    //! Смена скорости
    void setSpeed(int);

protected:

    //! Отложенный вызов слота
    void delay(QObject *, const char *);

    //! Периодический вызов слота
    void clock(QObject *, const char *);

protected slots:

    //! Сброс
    void reset();

private:

    //! Вызов слота по расписанию
    void sched(QObject *, const char *);

    //! Хронометр
    QTimer m_timer;

    //! Скорость
    int m_speed = 1;
};