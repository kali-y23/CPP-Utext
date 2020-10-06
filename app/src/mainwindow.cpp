#include "mainwindow.h"
#include "../Forms/ui_mainwindow.h"

#include "textArea.h"

MainWindow::MainWindow(QWidget *parent) :
                        QMainWindow(parent),
                        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyWidget *text = new MyWidget;

    ui->horizontalLayout_4->addWidget(text);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);

    QFont newFont = font();
    newFont.setPointSize(newFont.pointSize() + 20);
    setFont(newFont);

    setFocusPolicy(Qt::ClickFocus);
    installEventFilter(this);
}

void MyWidget::paintEvent(QPaintEvent *)
{
    QFontMetrics metrics(font());
    int curPosX = 0;
    int curPosY = metrics.ascent() - metrics.descent();
    int x = 0;
    int y = metrics.ascent() - metrics.descent();

    QPainter painter(this);
    for (int i = 0; i < getSize(); ++i) {
        painter.drawText(x, y,
                         QString(text[i]));
        x += metrics.horizontalAdvance(text[i]);
        if (i < curPos) {
            curPosX += metrics.horizontalAdvance(text[i]);
            if (text[i] == '\n') {
                curPosX = 0;
                curPosY += (metrics.ascent() - metrics.descent());
            }
        }
        if (text[i] == '\n') {
            x = 0;
            y += (metrics.ascent() - metrics.descent());
        }
    }
    painter.drawLine(curPosX, curPosY, curPosX, curPosY - (metrics.ascent() - metrics.descent()));
}

bool MyWidget::eventFilter(QObject* o, QEvent* e) {
	if (e->type() == QEvent::KeyPress) {
		QKeyEvent* k = static_cast<QKeyEvent*>(e);
        int key = k->key();
        QString text = k->text();
		if (key == Qt::Key_Tab) {
            setText("\t", curPos);
            return true;
		}
        else if (key == Qt::Key_Return) {
            setText("\n", curPos);
            return true;
        }
        else if (key == Qt::Key_Backspace) {
            backspace();
            return true;
        }
        else if (key == Qt::Key_Left || key == Qt::Key_Right) {
            if (key == Qt::Key_Left) {
                if (curPos > 0) {
                    --curPos;
                }
            }
            else {
                if (curPos < getSize()) {
                    ++curPos;
                }
            }
            update();
            return true;
        }
        else {
            setText(text, curPos);
            return false;
        }
	}
	return false;
}