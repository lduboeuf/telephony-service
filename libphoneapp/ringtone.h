/*
 * Copyright (C) 2012 Canonical, Ltd.
 *
 * Authors:
 *  Gustavo Pichorim Boiko <gustavo.boiko@canonical.com>
 *
 * This file is part of phone-app.
 *
 * phone-app is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * phone-app is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RINGTONE_H
#define RINGTONE_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFile>

class Ringtone : public QObject
{
    Q_OBJECT
public:
    static Ringtone *instance();

public Q_SLOTS:
    void playIncomingCallSound();
    void stopIncomingCallSound();

    void playIncomingMessageSound();
    void stopIncomingMessageSound();

private:
    explicit Ringtone(QObject *parent = 0);

    QMediaPlayer mCallAudioPlayer;
    QMediaPlaylist mCallAudioPlaylist;

    QMediaPlayer mMessageAudioPlayer;
};

#endif // RINGTONE_H