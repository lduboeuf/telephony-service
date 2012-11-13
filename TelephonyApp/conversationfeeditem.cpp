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

#include "conversationfeeditem.h"

ConversationFeedItem::ConversationFeedItem(QObject *parent) :
    QObject(parent), mIncoming(false)
{
}

QString ConversationFeedItem::contactId() const
{
    return mContactId;
}

void ConversationFeedItem::setContactId(const QString &value)
{
    mContactId = value;
    Q_EMIT contactIdChanged();
}

QString ConversationFeedItem::contactAlias() const
{
    return mContactAlias;
}

void ConversationFeedItem::setContactAlias(const QString &value)
{
    mContactAlias = value;
    Q_EMIT contactAliasChanged();
}

QUrl ConversationFeedItem::contactAvatar() const
{
    return mContactAvatar;
}

void ConversationFeedItem::setContactAvatar(const QUrl &value)
{
    mContactAvatar = value;
    Q_EMIT contactAvatarChanged();
}

bool ConversationFeedItem::incoming() const
{
    return mIncoming;
}

void ConversationFeedItem::setIncoming(bool value)
{
    mIncoming = value;
    Q_EMIT incomingChanged();
}

QDateTime ConversationFeedItem::timestamp() const
{
    return mTimestamp;
}

void ConversationFeedItem::setTimestamp(const QDateTime &value)
{
    mTimestamp = value;
    Q_EMIT timestampChanged();
}
