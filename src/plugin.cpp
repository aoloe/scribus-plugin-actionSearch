#include "plugin.h"

#include "scribuscore.h"
#include "scribusdoc.h"

#include <QString>

#include "actionsearch.h"
#include "ui/dialog.h"

int actionsearchplugin_getPluginAPIVersion()
{
	return PLUGIN_API_VERSION;
}

ScPlugin* actionsearchplugin_getPlugin()
{
	auto plug = new ScribusPlugin::ActionSearch::Plugin();
	Q_CHECK_PTR(plug);
	return plug;
}

void actionsearchplugin_freePlugin(ScPlugin* plugin)
{
	auto plug = dynamic_cast<ScribusPlugin::ActionSearch::Plugin*>(plugin);
	Q_ASSERT(plug);
	delete plug;
}

namespace ScribusPlugin {
namespace ActionSearch {

Plugin::Plugin() : ScActionPlugin()
{
	m_actionInfo.name = "ActionSearch";
	// Action text for menu, including accel
	m_actionInfo.text = tr("&Action Search");
	m_actionInfo.menu = "Help";
	m_actionInfo.menuAfterName = "helpTooltips";
	m_actionInfo.keySequence = "Ctrl+/";
	m_actionInfo.enabledOnStartup = false;
	m_actionInfo.needsNumObjects = -1;
}

Plugin::~Plugin()
{
	// unregisterAll();
};

void Plugin::languageChange()
{
	m_actionInfo.text = tr("&Action Search");
}

const QString Plugin::fullTrName() const
{
	return QObject::tr("Action Search");
}

const ScActionPlugin::AboutData* Plugin::getAboutData() const
{
	AboutData* about = new AboutData;
	about->authors = "Ale Rimoldi <a.l.e@ideale.ch>";
	about->shortDescription = tr("Search through the Menu actions.");
	about->description = tr("Search through the Menu actions and trigger them.");
	about->license = "MIT";
	Q_CHECK_PTR(about);
	return about;
}

void Plugin::deleteAboutData(const AboutData* about) const
{
	Q_ASSERT(about);
	delete about;
}

/**
 * This method is automatically called by Scribus when the plugin action is activated.
 *
 * If a document is open, check if a text frame is selected, call the style picker and apply the chosen style.
 */
bool Plugin::run(ScribusDoc* doc, const QString& target)
{
	// TODO: one day we will have to find out and document what target is good for...
	Q_ASSERT(target.isNull());
	ActionSearch actionSearch{doc->scMW()->menuBar()};
	actionSearch.update();
	auto dialog = new Dialog{doc->scMW(), actionSearch.getActionNames()};
	connect(dialog, &Dialog::accepted, [&actionSearch, dialog]() {
		actionSearch.execute(dialog->getActionName());
	});
	dialog->setModal(true);
	dialog->exec();
	return true;
}

} // namespaces
}
