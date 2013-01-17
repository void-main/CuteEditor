#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void setupActions();
    void setupStatusBar();

    bool mayDiscardDocument();
    void setupFile(const QString&);

protected slots:
    void newFile();
    void loadFile();
    void saveFile();
    void saveFile(const QString&);
    void saveFileAs();
    void undo();
    void redo();
    void copy();
    void about();

    void updateStatus();

private:
    QString mFilePath;
    QLabel* mStatLabel;
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
