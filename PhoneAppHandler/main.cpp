/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * Authors:
 *    Gustavo Pichorim Boiko <gustavo.boiko@canonical.com>
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

#include "phoneapphandler.h"
#include <QCoreApplication>
#include <TelepathyQt/ClientRegistrar>
#include <TelepathyQt/AbstractClient>
#include <TelepathyQt/AccountManager>
#include <TelepathyQt/Contact>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    Tp::registerTypes();

    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    Tp::ClientRegistrarPtr registrar = Tp::ClientRegistrar::create(sessionBus,
                                                                   Tp::AccountFactory::create(sessionBus),
                                                                   Tp::ConnectionFactory::create(sessionBus, Tp::Features()
                                                                                                 << Tp::Connection::FeatureCore
                                                                                                 << Tp::Connection::FeatureSelfContact),
                                                                   Tp::ChannelFactory::create(sessionBus),
                                                                   Tp::ContactFactory::create(Tp::Features()
                                                                                              << Tp::Contact::FeatureAlias
                                                                                              << Tp::Contact::FeatureAvatarData
                                                                                              << Tp::Contact::FeatureAvatarToken));

    // register the handler
    Tp::AbstractClientPtr handler = Tp::AbstractClientPtr::dynamicCast(
          Tp::SharedPtr<PhoneAppHandler>(new PhoneAppHandler()));
    registrar->registerClient(handler, "PhoneAppHandler");

    return app.exec();
}
