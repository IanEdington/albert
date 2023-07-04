// Copyright (c) 2023 Manuel Schneider

#include "albert/albert.h"
#include "albert/extension.h"
#include "albert/extension/pluginprovider/plugininstance.h"
#include <QCoreApplication>
#include <QDir>
#include <QSettings>
using namespace albert;

PluginInstance::~PluginInstance() = default;

void PluginInstance::initialize() {}

std::vector<Extension*> PluginInstance::extensions() { return {}; }

void PluginInstance::finalize() {}

QWidget *PluginInstance::buildConfigWidget() { return nullptr; }

static std::unique_ptr<QDir> make_extension_dir(const QString &location, const QString &id)
{
    auto dir = std::make_unique<QDir>(location);
    if (!dir->exists(id))
        if (!dir->mkdir(id))
            qFatal("Failed to create writable dir at: %s", qPrintable(dir->filePath(id)));

    dir->cd(id);
    return dir;
}

std::unique_ptr<QDir> albert::PluginInstance::cacheDir() const
{ return make_extension_dir(albert::cacheLocation(), id()); }

std::unique_ptr<QDir> albert::PluginInstance::configDir() const
{ return make_extension_dir(albert::configLocation(), id()); }

std::unique_ptr<QDir> albert::PluginInstance::dataDir() const
{ return make_extension_dir(albert::dataLocation(), id()); }

std::unique_ptr<QSettings> albert::PluginInstance::settings() const
{
    auto s = std::make_unique<QSettings>(qApp->applicationName());
    s->beginGroup(id());
    return s;
}
