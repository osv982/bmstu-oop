#include "timed.hpp"

void Timed::setSpeed(int speed)
{
    m_speed = speed;
}

void Timed::delay(QObject *recv, const char *slot)
{
    // Одноразовый режим
    m_timer.setSingleShot(true);

    // И по расписанию
    sched(recv, slot);
}

void Timed::clock(QObject *recv, const char *slot)
{
    // Многоразовый режим
    m_timer.setSingleShot(false);

    // И по расписанию
    sched(recv, slot);
}

void Timed::reset()
{
    // Становимся
    m_timer.stop();

    // Отключаем слот
    m_timer.disconnect();
}

void Timed::sched(QObject *recv, const char *slot)
{
    // Сброс
    reset();

    // Подключаем новый слот
    connect(&m_timer, SIGNAL(timeout()), recv, slot);

    // Запускаем хронометр
    m_timer.start(1000 / m_speed);
}