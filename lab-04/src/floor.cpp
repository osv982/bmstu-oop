#include "floor.hpp"

Floor::Floor(Press &press, QWidget *parent)
    : QPushButton(parent), m_press(press)
{
    // Связываем виджет кнопки с ней самой
    connect(this, &QPushButton::clicked, &m_press, &Press::setSelected);

    connect(&m_press, &Press::selected, this, &Floor::setSelected);
    connect(&m_press, &Press::released, this, &Floor::setReleased);

    // Устанавливаем текст виджета кнопки
    setText(QString::number(m_press.floor()));

    // Сбрасываем
    setReleased();
}

Press &Floor::press()
{
    return m_press;
}

void Floor::setSelected()
{
    setFlat(false);
}

void Floor::setReleased()
{
    setFlat(true);
}