#ifndef ACTIONSEARCHDIALOG_H
#define ACTIONSEARCHDIALOG_H

#include <QDialog>
class QMainWindow;
#include <QList>
class QString;
class QEvent;
class QKeyEvent;

namespace Ui {
class ActionSearchDialog;
}

namespace ScribusPlugin {
namespace ActionSearch {

class Dialog : public QDialog
{
	Q_OBJECT

	public:
		explicit Dialog(QMainWindow *parent, QList<QString> actionNames);
		~Dialog();
		QString getActionName();
	protected:
		bool eventFilter(QObject *obj, QEvent *ev);

	private slots:
		void updateList();

	signals:
		void keyArrowUpPressed();
		void keyArrowDownPressed();

	private slots:
		void moveSelectionUp();
		void moveSelectionDown();
        
	private:
		Ui::ActionSearchDialog *ui;
		QList<QString> actionNames;
		bool filterLineEditKeyPress(QKeyEvent * event);
};

} // namespaces
}

#endif
