#ifndef ACTIONSEARCH_H
#define ACTIONSEARCH_H

class QMenuBar;
class QMenu;
#include <QList>
#include <QHash>
class QAction;

namespace ScribusPlugin {
namespace ActionSearch {

class ActionSearch
{
    public:
        ActionSearch(QMenuBar *menuBar)
        : menuBar{menuBar}
        {}
        ~ActionSearch() {}
        void update();
        QList<QString> getActionNames() {return actions.keys();}
        void execute(QString actionName);
    private:
        QMenuBar* menuBar;

        void readMenuActions(QMenu* menu);

        QHash<QString, QAction*> actions{}; // std::unordered_map
};

} // namespaces
}
#endif
