QT += widgets
requires(qtConfig(treeview))

FORMS       = mainwindow.ui
HEADERS     = mainwindow.h \
              foldertask.h \
              treeitem.h \
              treemodel.h
RESOURCES   = editabletreemodel.qrc \
    src.qrc
SOURCES     = mainwindow.cpp \
              foldertask.cpp \
              treeitem.cpp \
              treemodel.cpp \
              main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/editabletreemodel
INSTALLS += target

DISTFILES += \
    sample.txt
