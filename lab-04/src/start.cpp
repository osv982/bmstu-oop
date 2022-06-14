#include <QtWidgets>

#include "brain.hpp"
#include "cabin.hpp"
#include "doors.hpp"
#include "press.hpp"

#include "floor.hpp"

class Start : public QWidget
{

public:

    explicit Start(int count, QWidget *parent = nullptr) : QWidget(parent)
    {
        m_cabin = new Cabin;
        m_doors = new Doors;

        m_brain = new Brain(*m_cabin, *m_doors, count);

        m_press = QVector<Press *>(count);
        m_floor = QVector<Floor *>(count);

        auto layout = new QVBoxLayout();

        for (int i = count; i > 0; i--)
        {
            m_press[i - 1] = new Press(*m_brain, i);
            m_floor[i - 1] = new Floor(*m_press[i - 1]);

            layout->addWidget(m_floor[i - 1]);
        }

        setLayout(layout);
    }

private:

    Brain *m_brain;

    Cabin *m_cabin;
    Doors *m_doors;

    QVector<Press *> m_press;
    QVector<Floor *> m_floor;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Start start(15);
    start.show();

    return app.exec();
}