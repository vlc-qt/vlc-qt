#ifndef EQUALIZERDIALOG_H
#define EQUALIZERDIALOG_H

#include <QDialog>
#include "ui_EqualizerDialog.h"

class VlcMediaPlayer;

class EqualizerDialog : public QDialog, Ui::EqualizerDialog
{
	Q_OBJECT
public:
	explicit EqualizerDialog(QWidget *parent = 0);

	void setMediaPlayer(VlcMediaPlayer *mediaPlayer);

public slots:
	void applyChangesForBand(int value);

	void applySelectedPreset();

	void toggle(bool checked);

private:
	QMap<QSlider*, int> _mapSliders;
	VlcMediaPlayer *_mediaPlayer;
};

#endif // EQUALIZERDIALOG_H
