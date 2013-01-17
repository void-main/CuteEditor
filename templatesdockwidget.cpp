#include "templatesdockwidget.h"
#include "ui_templatesdockwidget.h"

#include <QListView>

TemplatesDockWidget::TemplatesDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TemplatesDockWidget)
{
    ui->setupUi(this);
}

TemplatesDockWidget::~TemplatesDockWidget()
{
    delete ui;
}

QListView* TemplatesDockWidget::getListView()
{
    return ui->listView;
}
