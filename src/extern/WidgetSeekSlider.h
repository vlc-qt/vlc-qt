#ifndef VLCQT_WIDGETSEEKSLIDER_H_
#define VLCQT_WIDGETSEEKSLIDER_H_

#include <QtCore/QPoint>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QWidget>
#else
    #include <QtGui/QWidget>
#endif

#include "SharedExportExtern.h"
#include "util/input_slider.hpp"

class VLCQT_EXTERN_EXPORT VlcWidgetSeekSlider : public SeekSlider
{
public:
	VlcWidgetSeekSlider(Qt::Orientation q, QWidget *_parent = 0, bool _classic = false);
};

#endif // VLCQT_WIDGETSEEKSLIDER_H_
