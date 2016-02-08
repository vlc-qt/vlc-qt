#ifndef VLC_TRACK_MODEL_H
#define VLC_TRACK_MODEL_H

#include <QAbstractListModel>

class VlcTrackModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitleRole
    };

    explicit VlcTrackModel(QObject *parent = 0);
    explicit VlcTrackModel(const QMap<int, QString> &tracks, QObject *parent = 0);
    explicit VlcTrackModel(const VlcTrackModel &other);

    int rowCount(const QModelIndex &parent) const;
    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant data(const int row, int role) const;

    void clear();
    void load(const QMap<int, QString> &data);
    void insert(const int id, const QString &title);
    int count() const;
private:
    QMap<int, QString> _tracks;
signals:
    void countChanged();
};
Q_DECLARE_METATYPE(VlcTrackModel)
#endif // VLC_TRACK_MODEL_H
