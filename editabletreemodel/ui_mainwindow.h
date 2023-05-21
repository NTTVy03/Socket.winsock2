/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *exitAction;
    QAction *insertRowAction;
    QAction *removeRowAction;
    QAction *insertColumnAction;
    QAction *removeColumnAction;
    QAction *insertChildAction;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QTreeView *view;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *actionsMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(936, 468);
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        insertRowAction = new QAction(MainWindow);
        insertRowAction->setObjectName(QString::fromUtf8("insertRowAction"));
        removeRowAction = new QAction(MainWindow);
        removeRowAction->setObjectName(QString::fromUtf8("removeRowAction"));
        insertColumnAction = new QAction(MainWindow);
        insertColumnAction->setObjectName(QString::fromUtf8("insertColumnAction"));
        removeColumnAction = new QAction(MainWindow);
        removeColumnAction->setObjectName(QString::fromUtf8("removeColumnAction"));
        insertChildAction = new QAction(MainWindow);
        insertChildAction->setObjectName(QString::fromUtf8("insertChildAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setSpacing(0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        view = new QTreeView(centralwidget);
        view->setObjectName(QString::fromUtf8("view"));
        view->setAlternatingRowColors(true);
        view->setSelectionBehavior(QAbstractItemView::SelectItems);
        view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        view->setAnimated(false);
        view->setAllColumnsShowFocus(true);

        vboxLayout->addWidget(view);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 936, 25));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
        actionsMenu = new QMenu(menubar);
        actionsMenu->setObjectName(QString::fromUtf8("actionsMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(actionsMenu->menuAction());
        fileMenu->addAction(exitAction);
        actionsMenu->addAction(insertRowAction);
        actionsMenu->addAction(insertColumnAction);
        actionsMenu->addSeparator();
        actionsMenu->addAction(removeRowAction);
        actionsMenu->addAction(removeColumnAction);
        actionsMenu->addSeparator();
        actionsMenu->addAction(insertChildAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Editable Tree Model", nullptr));
        exitAction->setText(QApplication::translate("MainWindow", "E&xit", nullptr));
#ifndef QT_NO_SHORTCUT
        exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        insertRowAction->setText(QApplication::translate("MainWindow", "Insert Row", nullptr));
#ifndef QT_NO_SHORTCUT
        insertRowAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+I, R", nullptr));
#endif // QT_NO_SHORTCUT
        removeRowAction->setText(QApplication::translate("MainWindow", "Remove Row", nullptr));
#ifndef QT_NO_SHORTCUT
        removeRowAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+R, R", nullptr));
#endif // QT_NO_SHORTCUT
        insertColumnAction->setText(QApplication::translate("MainWindow", "Insert Column", nullptr));
#ifndef QT_NO_SHORTCUT
        insertColumnAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+I, C", nullptr));
#endif // QT_NO_SHORTCUT
        removeColumnAction->setText(QApplication::translate("MainWindow", "Remove Column", nullptr));
#ifndef QT_NO_SHORTCUT
        removeColumnAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+R, C", nullptr));
#endif // QT_NO_SHORTCUT
        insertChildAction->setText(QApplication::translate("MainWindow", "Insert Child", nullptr));
#ifndef QT_NO_SHORTCUT
        insertChildAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        fileMenu->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
        actionsMenu->setTitle(QApplication::translate("MainWindow", "&Actions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
