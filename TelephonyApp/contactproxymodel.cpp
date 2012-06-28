/*
 * Copyright (C) 2012 Canonical, Ltd.
 *
 * Authors:
 *  Gustavo Pichorim Boiko <gustavo.boiko@canonical.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "contactproxymodel.h"
#include "contactentry.h"
#include "contactmodel.h"
#include <QDebug>

ContactProxyModel::ContactProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    updateSorting();
}

QObject *ContactProxyModel::model() const
{
    return sourceModel();
}

void ContactProxyModel::setModel(QObject *value)
{
    ContactModel *model = qobject_cast<ContactModel*>(value);
    if (!model) {
        return;
    }

    setSourceModel(model);
    emit modelChanged();
}

QString ContactProxyModel::filterText() const
{
    return mFilterText;
}

void ContactProxyModel::setFilterText(const QString &value)
{
    if (value != mFilterText) {
        mFilterText = value;
        invalidateFilter();
        emit filterTextChanged();
    }
}

bool ContactProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)

    QObject *object = sourceModel()->index(sourceRow, 0).data(ContactModel::ContactRole).value<QObject*>();
    ContactEntry *entry = qobject_cast<ContactEntry*>(object);

    if (!entry) {
        qWarning() << "ContactRole did not return a valid entry!";
        return false;
    }

    if (mFilterText.isEmpty()) {
        return true;
    }

    if (entry->displayLabel().indexOf(mFilterText, 0, Qt::CaseInsensitive) >=0) {
        return true;
    }

    // FIXME: filter by the phonenumber
    return false;
}

void ContactProxyModel::updateSorting()
{
    sort(0, Qt::AscendingOrder);
}
