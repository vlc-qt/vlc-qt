#ifndef QVLC_H_
#define QVLC_H_

#include <QString>
#include <QThread>	// not needed here, but resolves msleep conflict

#include <vlc/plugins/vlc_common.h>    /* VLC_COMMON_MEMBERS for vlc_interface.h */
#if VLCQT_EXTERN_ENABLE_SEEKPOINTS
# include <vlc_interface.h> /* intf_thread_t */
#else
# include <vlc/plugins/vlc_mtime.h>
#endif
#include <vlc/plugins/vlc_playlist.h>  /* playlist_t */

enum {
    DialogEventTypeOffset = 0,
    IMEventTypeOffset     = 100,
    PLEventTypeOffset     = 200,
    MsgEventTypeOffset    = 300,
};

class QVLCApp;
class MainInterface;
class QSettings;
class PLModel;

struct intf_sys_t
{
    vlc_thread_t thread;

    QVLCApp *p_app;          /* Main Qt Application */

    MainInterface *p_mi;     /* Main Interface, NULL if DialogProvider Mode */

    QSettings *mainSettings; /* Qt State settings not messing main VLC ones */

    PLModel *pl_model;

    QString filepath;        /* Last path used in dialogs */

    unsigned voutWindowType; /* Type of vout_window_t provided */
    bool b_isDialogProvider; /* Qt mode or Skins mode */
    playlist_t *p_playlist;  /* playlist */
#ifdef _WIN32
    bool disable_volume_keys;
#endif
};

#define THEPL p_intf->p_sys->p_playlist

#define qfu( i ) QString::fromUtf8( i )
#define qfue( i ) QString::fromUtf8( i ).replace( "&", "&&" ) /* for actions/buttons */
#define qtr( i ) QString::fromUtf8( vlc_gettext(i) )
#define qtu( i ) ((i).toUtf8().constData())

#define CONNECT( a, b, c, d ) \
        connect( a, SIGNAL(b), c, SLOT(d) )
#define DCONNECT( a, b, c, d ) \
        connect( a, SIGNAL(b), c, SLOT(d), Qt::DirectConnection )

#endif
