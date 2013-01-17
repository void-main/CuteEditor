#ifndef TEMPLATESDOCKWIDGET_H
#define TEMPLATESDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class TemplatesDockWidget;
}

class QListView;

class TemplatesDockWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TemplatesDockWidget(QWidget *parent = 0);
    ~TemplatesDockWidget();

    QListView* getListView();
    
private:
    Ui::TemplatesDockWidget *ui;
};

#endif // TEMPLATESDOCKWIDGET_H
