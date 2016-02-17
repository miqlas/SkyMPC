#include "AboutDialog.h"
#include "ui_AboutDialog.h"
#include "main.h"
#include <QPainter>
#include "version.h"

extern "C" char const source_revision[];

AboutDialog::AboutDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AboutDialog)
{
	ui->setupUi(this);
	auto flags = windowFlags();
	flags &= ~Qt::WindowContextHelpButtonHint;
	setWindowFlags(flags);
	setFixedSize(width(), height());

	setWindowTitle(tr("About SkyMPC"));

	ui->label_title->setText(QString("SkyMPC, v") + SkyMPC_Version + " (" + QString(source_revision) + ")");
	ui->label_copyright->setText(QString("Copyright (C) ") + QString::number(SkyMPC_Year) + " S.Fuchita");
	ui->label_twitter->setText("(@soramimi_jp)");
//	ui->label_qt->setText(QString("Powered by Qt, v") + qVersion());

	pixmap.load(":/image/about.png");
}

AboutDialog::~AboutDialog()
{
	delete ui;
}

void AboutDialog::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, pixmap);
}

void AboutDialog::mouseReleaseEvent(QMouseEvent *)
{
    accept();
}

