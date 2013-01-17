#include "templatehandler.h"
#include <QListView>
#include <QTextEdit>
#include <QObject>
#include <QModelIndex>
#include <QStringListModel>
#include <QString>

TemplateHandler::TemplateHandler(QListView *view, QTextEdit *textEdit, QObject *parent)
    : QObject(parent), mTextEdit(textEdit)
{
    mModel = new QStringListModel(this);
    QStringList templates;
    templates << "<html>" << "</html>" << "<body>" << "</body>";
    mModel->setStringList(templates);
    view->setModel(mModel);

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(insertText(QModelIndex)));
}

void TemplateHandler::insertText(const QModelIndex &index)
{
    QString text = mModel->data(index, Qt::DisplayRole).toString();
    QTextCursor cursor = mTextEdit->textCursor();
    cursor.insertText(text);
    mTextEdit->setTextCursor(cursor);
}
