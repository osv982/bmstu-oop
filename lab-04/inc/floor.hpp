#include <QtWidgets>

#include "press.hpp"

class Floor : public QPushButton
{
    Q_OBJECT

public:

    //! Виджет кнопки
    Floor(Press &, QWidget *parent = nullptr);

    //! Кнопка
    Press &press();

public slots:

    void setSelected();
    void setReleased();

private:

    //! Кнопка
    Press &m_press;
};