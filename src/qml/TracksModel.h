#ifndef TRACKS_MODEL_H
#define TRACKS_MODEL_H

#include <QAbstractListModel>

class TracksModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitleRole
    };

    explicit TracksModel(QObject *parent = 0);
    explicit TracksModel(const QMap<int, QString> &tracks, QObject *parent = 0);
    explicit TracksModel(const TracksModel &other);

    int rowCount(const QModelIndex &parent) const;
    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;

    void clear();
    void load(const QMap<int, QString> &data);
    void insert(const int id, const QString &title);
    int count() const;
private:
    QMap<int, QString> _tracks;
signals:
    void countChanged();
};
Q_DECLARE_METATYPE(TracksModel)
#endif // TRACKS_MODEL_H
