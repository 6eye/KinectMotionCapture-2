#include "kinectmotioncapture.h"
#include <QtWidgets/QApplication>

/**
* Main ex�cutant l'IHM
*/
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	KinectMotionCapture w;
	w.Initialize();
	w.show();
	return a.exec();
}
