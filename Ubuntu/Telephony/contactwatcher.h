/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * Authors:
 *  Tiago Salem Herrmann <tiago.herrmann@canonical.com>
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

#ifndef CONTACTWATCHER_H
#define CONTACTWATCHER_H

#include <QObject>
#include <QContactManager>
#include <QContactAbstractRequest>
#include <QContactFetchRequest>
#include <QQmlParserStatus>

QTCONTACTS_USE_NAMESPACE

class ContactWatcher : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QString contactId READ contactId NOTIFY contactIdChanged)
    Q_PROPERTY(QString avatar READ avatar NOTIFY avatarChanged)
    Q_PROPERTY(QString alias READ alias NOTIFY aliasChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QList<int> phoneNumberSubTypes READ phoneNumberSubTypes NOTIFY phoneNumberSubTypesChanged)
    Q_PROPERTY(QList<int> phoneNumberContexts READ phoneNumberContexts NOTIFY phoneNumberContextsChanged)
    Q_PROPERTY(bool isUnknown READ isUnknown NOTIFY isUnknownChanged)
    Q_PROPERTY(bool interactive READ interactive NOTIFY interactiveChanged)
public:
    explicit ContactWatcher(QObject *parent = 0);
    ~ContactWatcher();

    QString contactId() const;
    QString avatar() const;
    QString alias() const;
    QString phoneNumber() const;
    void setPhoneNumber(const QString &phoneNumber);
    QList<int> phoneNumberSubTypes() const;
    QList<int> phoneNumberContexts() const;
    bool isUnknown() const;
    bool interactive() const;


    void classBegin();
    void componentComplete();
    // Test function
    void markAsComplete();

Q_SIGNALS:
    void contactIdChanged();
    void avatarChanged();
    void aliasChanged();
    void phoneNumberChanged();
    void phoneNumberSubTypesChanged();
    void phoneNumberContextsChanged();
    void isUnknownChanged();
    void interactiveChanged();

protected Q_SLOTS:
    void onContactsAdded(QList<QContactId> ids);
    void onContactsChanged(QList<QContactId> ids);
    void onContactsRemoved(QList<QContactId> ids);
    void resultsAvailable();
    void onRequestStateChanged(QContactAbstractRequest::State state);
    void searchByPhoneNumberIdle(const QString &phoneNumber);

private:
    void searchByPhoneNumber(const QString &phoneNumber);

    QContactFetchRequest *mRequest;
    QContactId mContactId;
    QString mAvatar;
    QString mAlias;
    QString mPhoneNumber;
    QList<int> mPhoneNumberSubTypes;
    QList<int> mPhoneNumberContexts;
    bool mInteractive;
    bool mCompleted;

};

#endif // CONTACTWATCHER_H
