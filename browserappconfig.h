/*  This file is part of KDevelop
    Copyright 2009 Andreas Pakulat <apaku@gmx.de>
    Copyright 2009 Niko Sams <niko.sams@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef BROWSERAPPCONFIGTYPE_H
#define BROWSERAPPCONFIGTYPE_H

#include <QUrl>
#include <QIcon>

#include <interfaces/launchconfigurationtype.h>
#include <interfaces/launchconfigurationpage.h>
#include <interfaces/ilauncher.h>
#include <interfaces/ilaunchmode.h>

#include "ui_browserappconfig.h"

class BrowserAppConfigPage : public KDevelop::LaunchConfigurationPage, Ui::BrowserAppPage
{
    Q_OBJECT
public:
    BrowserAppConfigPage( QWidget* parent );

    void loadFromConfiguration( const KConfigGroup& cfg, KDevelop::IProject* project = nullptr ) override;
    void saveToConfiguration( KConfigGroup cfg, KDevelop::IProject* project = nullptr ) const override;
    QString title() const override;
    QIcon icon() const override;
};

class BrowserAppLauncher : public KDevelop::ILauncher
{
public:
    BrowserAppLauncher();

    QList< KDevelop::LaunchConfigurationPageFactory* > configPages() const override;
    QString description() const override;
    QString id() override;
    QString name() const override;
    KJob* start(const QString& launchMode, KDevelop::ILaunchConfiguration* cfg) override;
    QStringList supportedModes() const override;
};

class BrowserAppPageFactory : public KDevelop::LaunchConfigurationPageFactory
{
public:
    BrowserAppPageFactory();

    KDevelop::LaunchConfigurationPage* createWidget(QWidget* parent) override;
};

/**
 * A specific configuration to start a launchable, this could be a native
 * compiled application, or some script file or byte-compiled file or something else
 * Provides access to the various configured informations, as well as its type and a name
 */
class BrowserAppConfigType : public KDevelop::LaunchConfigurationType
{
public:
    BrowserAppConfigType();

    QString id() const override;
    QString name() const override;
    QList<KDevelop::LaunchConfigurationPageFactory*> configPages() const override;
    QIcon icon() const override;
    bool canLaunch( const QUrl& file ) const override;
    bool canLaunch(KDevelop::ProjectBaseItem* item) const override;
    void configureLaunchFromItem(KConfigGroup config, KDevelop::ProjectBaseItem* item) const override;
    void configureLaunchFromCmdLineArguments(KConfigGroup config, const QStringList& args) const override;

private:
    QList<KDevelop::LaunchConfigurationPageFactory*> factoryList;
};
#endif

