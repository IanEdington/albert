// Copyright (c) 2023 Manuel Schneider

#pragma once
#include "albert/export.h"
#include <QString>
#include <memory>
#include <vector>
class QSettings;
class QDir;
class QWidget;
class PluginInstancePrivate;

namespace albert
{
class Extension;
class ExtensionRegistry;

///
/// Abstract plugin instance class.
///
/// This is the interface every plugin has to implement.
///
class ALBERT_EXPORT PluginInstance
{
public:
    PluginInstance();
    virtual ~PluginInstance();

    /// The plugin identifier.
    /// Taken from the metadata.
    QString id() const;

    /// The human readable plugin name.
    /// Taken from the metadata. Override for internationalization.
    virtual QString name() const;

    /// Brief description of the plugin.
    /// Taken from the metadata. Override for internationalization.
    virtual QString description() const;

    virtual void initialize(ExtensionRegistry*);  ///< The initialization function.
    virtual void finalize(ExtensionRegistry*);  ///<  The finalization function.
    virtual std::vector<Extension*> extensions();  ///< The extensions this plugin provides.
    virtual QWidget *buildConfigWidget();  ///< Config widget factory.

    std::unique_ptr<QDir> cacheDir() const;  ///< The recommended cache location.
    std::unique_ptr<QDir> configDir() const;  ///< The recommended config location.
    std::unique_ptr<QDir> dataDir() const;  ///< The recommended data location.
    std::unique_ptr<QSettings> settings() const;  ///< Prepared settings object.

protected:
    const std::unique_ptr<PluginInstancePrivate> d;
};


///
/// Convenience template class for the most common case of a plugin
/// providing exactly one extension.
///
/// Inherits PluginInstance and any given Extension, overrides the virtual
/// functions of Extension using the plugin metadata and returns itself in
/// PluginInstance::extensions.
///
/// @tparam EXTENSION The Extension (subclass) to inherit.
///
template <class EXTENSION>
class ALBERT_EXPORT ExtensionPluginInstance : public PluginInstance, public EXTENSION
{
public:

    /// Override returning PluginInstance::id
    QString id() const override { return PluginInstance::id(); }

    /// Override returning PluginInstance::name
    QString name() const override { return PluginInstance::name(); }

    /// Override returning PluginInstance::description
    QString description() const override { return PluginInstance::description(); }

    /// Override returning `this`
    std::vector<Extension*> extensions() override { return {this}; }
};


}
