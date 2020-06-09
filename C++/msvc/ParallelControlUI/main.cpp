#include "ParallelControlUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ParallelControlUI w;
	w.show();

	return a.exec();
}
