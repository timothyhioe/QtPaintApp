#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QColorDialog>
#include <QGridLayout>
#include <QCheckBox>
#include <QDebug>
#include "paint.h"
#include "canvas.h"

#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QSpinBox>


/** c'tor */
Paint::Paint(QWidget *parent)
    : QWidget(parent)
{
    // instantiate Canvas along with buttons and stuff
    viewport = new Canvas();

    btnClearCanvas = new QPushButton("&Clear Canvas");

    cobPrimModes = new QComboBox();
    cobPrimModes->addItem(tr("None"),      Canvas::NONE);
    cobPrimModes->addItem(tr("Line"),      Canvas::LINE);
    cobPrimModes->addItem(tr("Freehand"),  Canvas::FREE_HAND);
    cobPrimModes->addItem(tr("Circle"),    Canvas::CIRCLE);
    cobPrimModes->addItem(tr("Rectangle"), Canvas::RECTANGLE);
    cobPrimModes->addItem(tr("Triangle"),  Canvas::TRIANGLE);
    cobPrimModes->addItem(tr("Polygon"),   Canvas::POLYGON);

    lblPrimModes = new QLabel("Primitive Mode");
    lblPrimModes->setBuddy(cobPrimModes);

    btnDeleteObj = new QPushButton("&Delete Selected");

    btnChangeCol = new QPushButton("C&hange Color");
    cbOutline = new QCheckBox("Show Only &Outline");

    btnChangeBGCol = new QPushButton("Change Background Color");


    //create radio buttons for interaction modes
    createRadioButton = new QRadioButton(tr("Create"));
    deleteRadioButton = new QRadioButton(tr("Delete"));
    colorRadioButton = new QRadioButton(tr("Change color"));
    transformRadioButton = new QRadioButton(tr("Transform"));

    //Group the radio buttons
    interactionModeGroup = new QButtonGroup(this);
    interactionModeGroup->addButton(createRadioButton, Canvas::CREATE);
    interactionModeGroup->addButton(deleteRadioButton, Canvas::DEL);
    interactionModeGroup->addButton(colorRadioButton, Canvas::COL);
    interactionModeGroup->addButton(transformRadioButton, Canvas::TRAFO);


    //create group box for the radio buttons
    createGroupBox = new QGroupBox(tr("Selection Mode"));
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(createRadioButton);
    vbox->addWidget(deleteRadioButton);
    vbox->addWidget(colorRadioButton);
    vbox->addWidget(transformRadioButton);
    createGroupBox->setLayout(vbox);

    //combo box for line types
    cobLineTypes = new QComboBox();
    cobLineTypes->addItem(tr("Solid"), static_cast<int>(Qt::SolidLine));
    cobLineTypes->addItem(tr("Dash"), static_cast<int>(Qt::DashLine));
    cobLineTypes->addItem(tr("Dot"), static_cast<int>(Qt::DotLine));
    cobLineTypes->addItem(tr("Dash Dot"), static_cast<int>(Qt::DashDotLine));
    cobLineTypes->addItem(tr("Dash Dot Dot"), static_cast<int>(Qt::DashDotDotLine));

    lblLineTypes = new QLabel("Line Type");
    lblLineTypes->setBuddy(cobLineTypes);

    // spinbox for line size
    sbLineSize = new QSpinBox();
    sbLineSize->setRange(1, 10);
    sbLineSize->setValue(2);

    lblLineSize = new QLabel("Line Size");
    lblLineSize->setBuddy(sbLineSize);

    // create layout and add gui elements to it
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(viewport,       0, 0, 1, 4);
    mainLayout->addWidget(btnChangeCol,   1, 0);
    mainLayout->addWidget(cbOutline,      1, 1, Qt::AlignLeft);
    mainLayout->addWidget(lblPrimModes,   1, 2, Qt::AlignRight);
    mainLayout->addWidget(cobPrimModes,   1, 3);
    mainLayout->addWidget(btnDeleteObj,   2, 0);
    mainLayout->addWidget(btnClearCanvas, 2, 3);
    mainLayout->addWidget(createGroupBox, 3, 0, 1, 2);
    mainLayout->addWidget(btnChangeBGCol, 3, 3);
    mainLayout->addWidget(lblLineSize, 4, 2, Qt::AlignRight);
    mainLayout->addWidget(sbLineSize, 4, 3);
    mainLayout->addWidget(lblLineTypes, 5, 2, Qt::AlignRight);
    mainLayout->addWidget(cobLineTypes, 5 ,3);


    // add layout to this widget instance
    setLayout(mainLayout);

    // connect button click event to clear canvas handler
    connect(btnClearCanvas, SIGNAL(clicked()),
            this, SLOT(clearBtnPressed()));
    // connect button click event to delete selected object handler
    connect(btnDeleteObj, SIGNAL(clicked()),
            this, SLOT(deleteBtnPressed()));
    // connect button click event to color chooser handler
    connect(btnChangeCol, SIGNAL(clicked()),
            this, SLOT(colorBtnPressed()));
    // connect list-/combobox to primitive changed event handler
    connect(cobPrimModes, SIGNAL(activated(int)),
            this, SLOT(primModeChanged(int)));
    // connect checkbox to toggle outline event handler
    connect(cbOutline, SIGNAL(toggled(bool)),
            this, SLOT(showOutlineOnly(bool)));
    //connect radio buttons to interaction mode
    connect(interactionModeGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, &Paint::setInteractionMode);
    //connect button click event to background color chooser handler
    connect(btnChangeBGCol, SIGNAL(clicked()),
            this, SLOT(backgroundColorBtnPressed()));
    //connect combobox to line type changed event handler
    connect(cobLineTypes, SIGNAL(activated(int)),
            this, SLOT(lineTypeChanged(int)));
    //connect spinbox to line size changed event handler
    connect(sbLineSize, SIGNAL(valueChanged(int)),
            this, SLOT(lineSizeChanged(int)));
}

/** d'tor */
Paint::~Paint()
{
}

/** method for handling button clicked event */
void Paint::clearBtnPressed()
{
    viewport->clearCanvas();

    // force redraw
    update();
    qDebug() << "Clear image called";
}

void Paint::deleteBtnPressed()
{
    // Implementation requires inside test for all objects for selection
    qDebug() << "Next action: delete selected item (NYI)";
}

void Paint::colorBtnPressed()
{
    QColor color = QColorDialog::getColor(Qt::blue, this);
    if (color.isValid()) {
        qDebug() << "Color choosen : " << color.name();
        viewport->setObjColor(color);
    }
}

void Paint::showOutlineOnly(bool outline)
{
    qDebug() << "Only show outline: " << outline;
    viewport->setFillMode(!outline);
}

void Paint::primModeChanged(int index)
{
    int mode = cobPrimModes->itemData(index).toInt();
    viewport->setPrimitiveMode(mode);
    qDebug() << "Primitive Mode changed to " << mode;
}


void Paint::setInteractionMode(int mode)
{
    qDebug() << "Interaction Mode changed to " << mode;
    viewport->setInteractionMode(mode);
}

void Paint::backgroundColorBtnPressed()
{
    QColor BgColor = QColorDialog::getColor(Qt::white, this);
    if(BgColor.isValid()){
        qDebug() << "Color choosen for Background: " << BgColor.name();
        viewport->setBackgroundColor(BgColor);
    }
}

void Paint::lineTypeChanged(int index)
{
    int type = cobLineTypes->itemData(index).toInt();
    viewport->setLineType(type);
    qDebug() << "Line Type changed to " << type;
}

void Paint::lineSizeChanged(int size)
{
    viewport->setLineSize(size);
    qDebug() << "Line Size changed to " << size;
}

