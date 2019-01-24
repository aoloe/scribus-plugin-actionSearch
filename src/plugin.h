 /**
 * This is the entry point for the plugin.
 * All the methods defined here are called by Scribus' plugin execution code.
 */

#ifndef ACTIONSEARCHPLUGIN_H
#define ACTIONSEARCHPLUGIN_H

#include "pluginapi.h"
#include "scplugin.h"

#include <QString>

class ScribusDoc;
class ScribusMainWindow;

// #include "ui/dialog.h" // TODO: needed?

namespace ScribusPlugin {
namespace ActionSearch {

/**
 * This is the standard entry point for the plugin and is automatically loaded by Scribus.
 * @brief Standard entry point for the plugin; Attaches itself to the menu, shows the "Settings" dialog and calls `ActionSearch::doInsert()`
 */
class PLUGIN_API Plugin : public ScActionPlugin
{
	Q_OBJECT
	public:

		// Standard plugin implementation
		Plugin();
		virtual ~Plugin();
		/*!
		  \author Ale Rimoldi
		  \brief Run the Apply Style
		  \param filename a file to export to
		  \retval bool true
		 */
		virtual bool run(ScribusDoc* doc, const QString& filename = QString::null) override;
		virtual const QString fullTrName() const override;
		virtual const AboutData* getAboutData() const override;
		virtual void deleteAboutData(const AboutData* about) const override;
		virtual void languageChange() override;
		virtual void addToMainWindowMenu(ScribusMainWindow *) override {};
};

} // namespaces
}

extern "C" PLUGIN_API int actionsearchplugin_getPluginAPIVersion();
extern "C" PLUGIN_API ScPlugin* actionsearchplugin_getPlugin();
extern "C" PLUGIN_API void actionsearchplugin_freePlugin(ScPlugin* plugin);

#endif
