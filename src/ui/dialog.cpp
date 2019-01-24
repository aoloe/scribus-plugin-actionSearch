#include "dialog.h"
#include "ui_actionsearchdialog.h"

#include <QDebug>
#include <QMainWindow>
#include <QString>
#include <QEvent>
#include <QKeyEvent>

namespace ScribusPlugin {
namespace ActionSearch {

Dialog::Dialog(QMainWindow *parent, QList<QString> actionNames) :
	QDialog{parent},
	ui{new Ui::ActionSearchDialog},
	actionNames{actionNames}
{
	ui->setupUi(this);

	ui->filterLineEdit->installEventFilter(this);
	installEventFilter(this);

	connect(ui->filterLineEdit, &QLineEdit::textChanged,
		this, &Dialog::updateList);
	connect(this, &Dialog::keyArrowUpPressed,
		this, &Dialog::moveSelectionUp);
	connect(this, &Dialog::keyArrowDownPressed,
		this, &Dialog::moveSelectionDown);
	connect(ui->actionsListWidget, &QListWidget::itemClicked,
		this, &QDialog::accept);
}

Dialog::~Dialog()
{
	delete ui;
}

QString Dialog::getActionName()
{
	if (ui->actionsListWidget->count() == 0)
	{
		return "";
	}

	return ui->actionsListWidget->currentItem()->text();
}

/**
 * @brief capture return, arrow keys, and tab
 */
bool Dialog::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == ui->filterLineEdit) {
		if (event->type() == QEvent::KeyPress) {
			return filterLineEditKeyPress(static_cast<QKeyEvent*>(event));
		}
	}
	return false;
}

bool Dialog::filterLineEditKeyPress(QKeyEvent * event)
{
	switch (event->key())
	{
		case Qt::Key_Enter:
		case Qt::Key_Return:
			this->accept();
			return true;
		case Qt::Key_Up:
			emit keyArrowUpPressed();
			return true;
		case Qt::Key_Down:
		case Qt::Key_Tab:
			emit keyArrowDownPressed();
			return true;
		default:
			return false;
	}
}

void Dialog::moveSelectionUp()
{
	int i = ui->actionsListWidget->currentRow();
	if (i > 0)
	{
		ui->actionsListWidget->setCurrentRow(i - 1);
	}
}

void Dialog::moveSelectionDown()
{
	int i = ui->actionsListWidget->currentRow();
	if (i < ui->actionsListWidget->count() - 1)
	{
		ui->actionsListWidget->setCurrentRow(i + 1);
	}
}


void Dialog::updateList()
{
	ui->actionsListWidget->clear();
	const auto filter = ui->filterLineEdit->text();
	if (filter == "")
	{
		return;
	}
	for (const auto& name: actionNames)
	{
		if (name.contains(filter, Qt::CaseInsensitive)) {
			ui->actionsListWidget->addItem(name);
		}
	}
	if (ui->actionsListWidget->count() > 0) {
		ui->actionsListWidget->setCurrentRow(0);
	}
}

} // namespaces
}
