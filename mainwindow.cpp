#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "templatehandler.h"
#include "templatesdockwidget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QListView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupActions();
    setupStatusBar();

    TemplatesDockWidget* templateDocker = new TemplatesDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, templateDocker);

    new TemplateHandler(templateDocker->getListView(), ui->textEdit, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupActions()
{
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(loadFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveFileAs()));

    connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(undoAvailable(bool)), ui->actionUndo, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(redoAvailable(bool)), ui->actionRepeat, SLOT(setEnabled(bool)));

    connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
    connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(ui->actionRepeat, SIGNAL(triggered()), this, SLOT(redo()));

    connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::setupStatusBar()
{
    mStatLabel = new QLabel;
    ui->statusBar->addPermanentWidget(mStatLabel);
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(updateStatus()));
    updateStatus();
}

void MainWindow::updateStatus()
{
    QString text = ui->textEdit->document()->toPlainText();
    int chars = text.length();
    text = text.simplified();
    int words = 0;

    words = text.count(" ");
    if(!text.isEmpty()) words += 1;

    QString output = tr("Characters: %1, Words: %2").arg(chars).arg(words);
    mStatLabel->setText(output);
}

void MainWindow::loadFile()
{
    QString filename = QFileDialog::getOpenFileName(this);
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->textEdit->setPlainText(QString::fromUtf8(file.readAll()));
        mFilePath = filename;
        ui->statusBar->showMessage(tr("File successfully loaded."), 3000);
    }
}

void MainWindow::saveFile()
{
    if(mFilePath.isEmpty()) {
        saveFileAs();
    } else {
        saveFile(mFilePath);
    }
}

void MainWindow::saveFile(const QString& name)
{
    QFile file(name);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(ui->textEdit->toPlainText().toUtf8());
        ui->statusBar->showMessage(tr("File saved successfully."), 3000);
    }
}

void MainWindow::saveFileAs()
{
    mFilePath = QFileDialog::getSaveFileName(this);
    if(mFilePath.isEmpty()) {
        return;
    } else {
        saveFile(mFilePath);
    }
}

bool MainWindow::mayDiscardDocument()
{
    if(ui->textEdit->document()->isModified()) {
        QString filename = mFilePath;
        if(filename.isEmpty()) filename = "Unnamed";
        if(!QMessageBox::question(this, tr("Save Document?"),
                                 tr("You want to create a new document, but the"
                                    "changes in the current document '%1' have not"
                                    "been saved. How do you want to proceed?").arg(filename),
                                 tr("Save Document"), tr("Discard Changes"))) {
            saveFile();
        }
        return true;
    }
    return false;
}

void MainWindow::newFile()
{
    if(!mayDiscardDocument()) {
        return;
    }

    ui->textEdit->setPlainText("");
    mFilePath = "";
}

void MainWindow::undo()
{
    ui->textEdit->document()->undo();
}

void MainWindow::redo()
{
    ui->textEdit->document()->redo();
}

void MainWindow::copy()
{
    ui->textEdit->copy();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About CuteEditor"),
                       tr("CuteEditor 1.0\nA Qt application example.\n"
                          "(c) 2013 Void Main, Open Source Press"));
}
