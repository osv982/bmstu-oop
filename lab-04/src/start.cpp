#include <QtWidgets>

#include "brain.hpp"
#include "cabin.hpp"
#include "doors.hpp"
#include "press.hpp"

#include "floor.hpp"

class Start : public QWidget
{

public:

    Start(QWidget *parent = nullptr) : QWidget(parent)
    {
        auto m_cabin = new Cabin;
        auto m_doors = new Doors;

        auto m_brain = new Brain(*m_cabin, *m_doors);

        auto vLayout = new QVBoxLayout();

        for (int i = 13; i > 0; i--)
        {
            m_press[i] = new Press(*m_brain, i);
            m_floor[i] = new Floor(*m_press[i]);

            vLayout->addWidget(m_floor[i]);
        }

        setLayout(vLayout);
    }

private:

    Press *m_press[13];
    Floor *m_floor[13];

    Brain *m_brain;

    Cabin *m_cabin;
    Doors *m_doors;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Start start;
    start.show();

    return app.exec();
}