#include "myTree.h"
#include <iostream>

myTreeScroll::myTreeScroll(QWidget *parent) :
                        QWidget(parent)
{
}

myTree::myTree(QWidget *parent) :
                        QTreeView(parent)
{
}


myTreeWidget::myTreeWidget(QWidget *parent) :
                        QScrollArea(parent)
{
    setAcceptDrops(true);
    setMinimumSize(1, 400);
    setWidget(central);
    setWidgetResizable(true);
    central->setAccessibleName("treeWidget1");
}


void myTreeWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void myTreeWidget::dropEvent(QDropEvent *event)
{
    QString filePath = event->mimeData()->urls()[0].toLocalFile();
    QFileInfo info(filePath);

    if (info.isDir()) {
        QTabWidget *tab = new QTabWidget(this);
        myTree* tree = new myTree();
        tab->addTab(tree, filePath);
        tab->setMinimumSize(-1, 150);
        QFileSystemModel* dirmodel = new QFileSystemModel();

        dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
        dirmodel->setRootPath(filePath);
        tree->setModel(dirmodel);
        tree->setRootIndex(dirmodel->index(filePath));
        tree->setHeaderHidden(true);
        tree->hideDirModelCols(dirmodel);
        layout->addWidget(tab);
    }
}

void myTreeWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(viewport());
    QPainter p(viewport());
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, viewport());
}

void myTreeScroll::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void myTree::hideDirModelCols(QFileSystemModel* dirmodel) {
    for (int i = 1; i < dirmodel->columnCount(); ++i) {
        hideColumn(i);
    }
}