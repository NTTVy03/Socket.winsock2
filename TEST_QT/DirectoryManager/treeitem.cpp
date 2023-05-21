/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
    treeitem.cpp
    tree item = node
    A container for items of data supplied by the simple tree model.
*/

#include "treeitem.h"

#include <QStringList>

//! [0]
// khởi tạo giá trị của node, gồm node cha (parent) và thông tin của node đó (data)
TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
{
    parentItem = parent;
    itemData = data;
}
//! [0]

//! [1]
// giải phóng node
TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}
//! [1]

//! [2]
// tìm con thứ number của node
TreeItem *TreeItem::child(int number)
{
    return childItems.value(number);
    // value --> check out of bound
    // at --> faster, does not check out of bound
}
//! [2]

//! [3]
// đếm số con của node
int TreeItem::childCount() const
{
    return childItems.count();
}
//! [3]

//! [4]
// tìm số thứ tự của node (so với các node cùng cha)
int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
//! [4]

//! [5]
// đếm số trường thông tin của node được hiển thị
// vd: Name - Desc ==> columnCount() = 2
int TreeItem::columnCount() const
{
    return itemData.count();
}
//! [5]

//! [6]
// data trong trường thông tin thứ column của node
QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}
//! [6]

//! [7]
// thêm node con cho node hiện tại, trong đó:
// position: chèn và sau vị trí position
// count: số lượng node con được chèn
// columns: số trường thông tin của các node được chèn
bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        // khởi tạo data với số trường là column = số trường thông tin 1 node
        // vector có columns phần tử, giá trị mặc định "no data"
        QVector<QVariant> data(columns);

        // khởi tạo node con có cha là this, thông tin là data
        TreeItem *item = new TreeItem(data, this);

        childItems.insert(position, item);
    }

    return true;
}
//! [7]

//! [8]
// thêm columns trường thông tin (cột) vào sau position
bool TreeItem::insertColumns(int position, int columns)
{
    // check out of bound
    if (position < 0 || position > itemData.size())
        return false;

    // lần lượt thêm các cột vào sau position
    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    // thêm số cột tương ứng vào mỗi node con
    foreach (TreeItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}
//! [8]

//! [9]
// tìm cha của node hiện tại
TreeItem *TreeItem::parent()
{
    return parentItem;
}
//! [9]

//! [10]
// xóa count node con, tính từ position
bool TreeItem::removeChildren(int position, int count)
{
    // check out of bound
    if (position < 0 || position + count > childItems.size())
        return false;

    // lần lượt xóa các node con tại position
    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
//! [10]

// xóa columns trường thông tin tính từ position
bool TreeItem::removeColumns(int position, int columns)
{
    // check out of bound
    if (position < 0 || position + columns > itemData.size())
        return false;

    // lần lượt xóa trường thông tin ở node hiện tại
    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    // xóa các trường tương ứng ở các node con
    foreach (TreeItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

//! [11]
// cài giá trị cho node hiện tại, cụ thể
// trường thông tin thứ column với giá trị value
bool TreeItem::setData(int column, const QVariant &value)
{
    // check out of bound
    if (column < 0 || column >= itemData.size())
        return false;

    // cài giá trị
    itemData[column] = value;
    return true;
}
//! [11]
