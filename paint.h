#ifndef PAINT_H
#define PAINT_H
#include <QWidget>
#include <QMainWindow>
#include "canvas.h"

class QPushButton;
class QComboBox;
class QLabel;
class QCheckBox;
class QRadioButton;
class QButtonGroup;
class QGroupBox;
class Canvas;
class QSpinBox;


class Paint : public QWidget
{
	Q_OBJECT

public:
	Paint(QWidget *parent = 0);
	~Paint();

private slots:
	void clearBtnPressed();
    void deleteBtnPressed();
    void colorBtnPressed();
    void primModeChanged(int index);
    void showOutlineOnly(bool);
    void setInteractionMode(int index);
    void backgroundColorBtnPressed();
    void lineTypeChanged(int index);
    void lineSizeChanged(int size);

private:
	Canvas *viewport;

	QPushButton *btnClearCanvas;
	QComboBox *cobPrimModes;
	QLabel *lblPrimModes;
    QPushButton *btnDeleteObj;
    QPushButton *btnChangeCol;
    QCheckBox *cbOutline;

    QRadioButton *createRadioButton;
    QRadioButton *deleteRadioButton;
    QRadioButton *colorRadioButton;
    QRadioButton *transformRadioButton;
    QButtonGroup *interactionModeGroup;
    QGroupBox *createGroupBox;

    //change background color
    QPushButton *btnChangeBGCol;

    //change line type and size
    QComboBox *cobLineTypes;
    QLabel *lblLineTypes;
    QSpinBox *sbLineSize;
    QLabel *lblLineSize;

};

#endif // PAINT_H
