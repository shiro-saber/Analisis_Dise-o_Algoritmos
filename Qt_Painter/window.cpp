#include "window.h"

#include <qmath.h>
#include <QComboBox>
#include <QGridLayout>

Window::Window()
{
    //double ls2 = ls.trasX();
    originalRenderArea = new RenderArea();

    shapeComboBox = new QComboBox;
    shapeComboBox->addItem(tr("Reloj"));
    shapeComboBox->addItem(tr("Casa"));
    shapeComboBox->addItem(tr("Hola"));
    shapeComboBox->addItem(tr("Camion"));
    shapeComboBox->addItem(tr("Estrella"));
    shapeComboBox->addItem(tr("Overlaped"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(originalRenderArea, 0, 0);
    layout->addWidget(shapeComboBox, 1, 0);

    for (int i = 0; i < NumTransformedAreas; ++i) {
        transformedRenderAreas[i] = new RenderArea;

        operationComboBoxes[i] = new QComboBox;
        operationComboBoxes[i]->addItem(tr("No transformation"));
        operationComboBoxes[i]->addItem(tr("Rotar"));
        operationComboBoxes[i]->addItem(tr("Zoom In"));
        operationComboBoxes[i]->addItem(tr("Zoom Out"));
        operationComboBoxes[i]->addItem(tr("Transladar"));
        operationComboBoxes[i]->addItem(tr("Refleccion X"));
        operationComboBoxes[i]->addItem(tr("Refleccion Y"));
        operationComboBoxes[i]->addItem(tr("Refleccion XY"));

        connect(operationComboBoxes[i], SIGNAL(activated(int)),
                this, SLOT(operationChanged()));

        layout->addWidget(transformedRenderAreas[i], 0, i + 1);
        layout->addWidget(operationComboBoxes[i], 1, i + 1);
    }

    setLayout(layout);
    setupShapes();
    shapeSelected(0);

    setWindowTitle("Transformaciones");
}

void Window::setupShapes()
{
    const float Pi = 3.14159;
    QPainterPath truck;
    truck.setFillRule(Qt::WindingFill);
    truck.moveTo(0.0, 87.0);
    truck.lineTo(0.0, 60.0);
    truck.lineTo(10.0, 60.0);
    truck.lineTo(35.0, 35.0);
    truck.lineTo(100.0, 35.0);
    truck.lineTo(100.0, 87.0);
    truck.lineTo(0.0, 87.0);
    truck.moveTo(17.0, 60.0);
    truck.lineTo(55.0, 60.0);
    truck.lineTo(55.0, 40.0);
    truck.lineTo(37.0, 40.0);
    truck.lineTo(17.0, 60.0);
    truck.addEllipse(17.0, 75.0, 25.0, 25.0);
    truck.addEllipse(63.0, 75.0, 25.0, 25.0);

    QPainterPath clock;
    clock.addEllipse(-50.0, -50.0, 100.0, 100.0);
    clock.addEllipse(-48.0, -48.0, 96.0, 96.0);
    clock.moveTo(0.0, 0.0);
    clock.lineTo(-2.0, -2.0);
    clock.lineTo(0.0, -42.0);
    clock.lineTo(2.0, -2.0);
    clock.lineTo(0.0, 0.0);
    clock.moveTo(0.0, 0.0);
    clock.lineTo(2.732, -0.732);
    clock.lineTo(24.495, 14.142);
    clock.lineTo(0.732, 2.732);
    clock.lineTo(0.0, 0.0);

    QPainterPath house;
    house.moveTo(-45.0, -20.0);
    house.lineTo(0.0, -45.0);
    house.lineTo(45.0, -20.0);
    house.lineTo(45.0, 45.0);
    house.lineTo(-45.0, 45.0);
    house.lineTo(-45.0, -20.0);
    house.addRect(15.0, 5.0, 20.0, 35.0);
    house.addRect(-35.0, -15.0, 25.0, 25.0);

    QPainterPath text;
    QFont font;
    font.setPixelSize(40);
    QRect fontBoundingRect = QFontMetrics(font).boundingRect(tr("Hello"));
    text.addText(-QPointF(fontBoundingRect.center()), font, tr("Hello"));

    QPainterPath algo;
    algo.moveTo(1.0, 1.0);
    algo.moveTo(90, 50);
    for (int i = 1; i < 5; ++i)
        algo.lineTo(50 + 40 * cos(0.8 * i * Pi), 50 + 40 * sin(0.8 * i * Pi));

    QPainterPath otro_algo;
    otro_algo.moveTo(0.0, 0.0);
    otro_algo.arcTo(20.0, 20.0, 40.0, 40.0, 0.0, 360.0);
    otro_algo.moveTo(40.0, 40.0);
    otro_algo.lineTo(40.0, 80.0);
    otro_algo.lineTo(80.0, 80.0);
    otro_algo.lineTo(80.0, 40.0);

    shapes.append(clock);
    shapes.append(house);
    shapes.append(text);
    shapes.append(truck);
    shapes.append(algo);
    shapes.append(otro_algo);

    connect(shapeComboBox, SIGNAL(activated(int)), this, SLOT(shapeSelected(int)));
}

void Window::operationChanged()
{
    static const Operation operationTable[] = {
        NoTransformation, Rotate, ZoomIn, ZoomOut, Translate, ReflectionX, ReflectionY, Reflection
    };

    QList<Operation> operations;
    for (int i = 0; i < NumTransformedAreas; ++i) {
        int index = operationComboBoxes[i]->currentIndex();
        operations.append(operationTable[index]);
        transformedRenderAreas[i]->setOperations(operations);
    }
}

void Window::shapeSelected(int index)
{
    QPainterPath shape = shapes[index];
    originalRenderArea->setShape(shape);
    for (int i = 0; i < NumTransformedAreas; ++i)
        transformedRenderAreas[i]->setShape(shape);
}
