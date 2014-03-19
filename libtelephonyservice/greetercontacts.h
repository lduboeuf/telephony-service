/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * Authors:
 *  Michael Terry <michael.terry@canonical.com>
 *
 * This file is part of telephony-service.
 *
 * telephony-service is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * telephony-service is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GREETERCONTACTS_H
#define GREETERCONTACTS_H

#include <QContact>
#include <QContactFilter>
#include <QDBusMessage>
#include <QObject>

class QDBusPendingCallWatcher;

/**
 * When running under the greeter, we don't have our own contacts database.
 * Instead, we query AccountsService for the information.
 */
class GreeterContacts : public QObject
{
    Q_OBJECT

public:
    static GreeterContacts *instance();
    ~GreeterContacts();

    void setContactFilter(const QtContacts::QContactFilter &filter);

    bool silentMode();
    QString incomingCallSound();
    QString incomingMessageSound();

    static bool isGreeterMode();

    // Records contact info for currently-logged-in user
    static void emitContact(const QtContacts::QContact &contact);

    // These are really implementation details, but are public for ease of unit testing
    static QVariantMap contactToMap(const QtContacts::QContact &contact);
    static QtContacts::QContact mapToContact(const QVariantMap &map);

Q_SIGNALS:
    void contactUpdated(const QtContacts::QContact &contact);

private Q_SLOTS:
    void greeterPropertiesChanged(const QString &interface, const QVariantMap &changed, const QStringList &invalidated);
    void accountsPropertiesChanged(const QString &interface, const QVariantMap &changed, const QStringList &invalidated, const QDBusMessage &message);

    void greeterGetEntryReply(QDBusPendingCallWatcher *watcher);
    void accountsGetUsersReply(QDBusPendingCallWatcher *watcher);
    void accountsGetContactReply(QDBusPendingCallWatcher *watcher);

private:
    GreeterContacts(QObject *parent = 0);

    void queryEntry();
    void queryContact(const QString &user);
    void updateActiveUser(const QString &username);
    QtContacts::QContact lookupContact();
    void signalIfNeeded();

    void checkUpdatedValue(const QVariantMap &changed, const QStringList &invalidated, const QString &propName, QVariant &propValue);
    QVariant getUserValue(const QString &interface, const QString &propName);

    QString mActiveUser;
    QVariant mSilentMode;
    QVariant mIncomingCallSound;
    QVariant mIncomingMessageSound;

    QtContacts::QContactFilter mFilter;
    QMap<QString, QVariantMap> mContacts;

    static GreeterContacts *mInstance;
};

#endif // GREETERCONTACTS_H
