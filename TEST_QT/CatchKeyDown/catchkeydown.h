#ifndef CATCHKEYDOWN_H
#define CATCHKEYDOWN_H

#include <QList>
#include <QString>

#include <iostream>
#include <windows.h>

class CatchKeyDown
{
public:
    CatchKeyDown();
    std::string VirtualKeyCodeToString(UCHAR virtualKey);
    void catchCodeAlltoString();
    QString getContent();
private:
    QList<QString> keyDesc;
    QString total;
};

#endif // CATCHKEYDOWN_H
