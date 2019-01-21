#include <QDebug>

#include "actionsearch.h"

#include <QMenuBar>
#include <QMenu>
#include <QList>
#include <QAction>

namespace ScribusPlugin {
namespace ActionSearch {

void ActionSearch::update()
{
    for (auto menuAction: menuBar->actions())
    {
        readMenuActions(menuAction->menu());
    }
}

void ActionSearch::execute(QString actionName)
{
    if (actions.contains(actionName)) {
        actions[actionName]->trigger();
    }
}

void ActionSearch::readMenuActions(QMenu* menu)
{
    // TODO: check why menu can be null
    if (menu == NULL)
    {
        return;
    }

    QString menuName = menu->title().replace("&", "");

    for (auto action: menu->actions())
    {
        if (action->menu() != NULL)
        {
            readMenuActions(action->menu());
        }
        else
        {
            QString actionName = action->text().replace("&", "");
            if (actionName != "" && action->isEnabled())
            {
                // TODO: we might want to have a multilevel menuName
                actionName += "\n(" + menuName +")";
                actions.insert(actionName, action);
            }
        }
        
    }
}

} // namespaces
}
