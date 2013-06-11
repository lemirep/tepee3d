#ifndef MOVIEMODEL_H
#define MOVIEMODEL_H

#include <PlayableItemModel.h>
#include <QUrl>

class MovieModel : public PlayableItemModel
{
    Q_OBJECT
public:

    enum MovieModelItemRoles
    {
        movieId = PlayableItemModel::thumbnail + 1,
        genre,
        mood, //UNUSED
        studio,
        plot,
        year
    };

    explicit MovieModel(QObject *parent = 0, int movieId = -1);
    int id() const;
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    QString getGenre() const;
    QString getMood() const;
    QString getStudio() const;
    QString getPlot() const;
    int getYear() const;

    void setGenre(const QString &genre);
    void setMood(const QString &mood);
    void setStudio(const QString &studio);
    void setPlot(const QString &plot);
    void setYear(int year);


private:
    QString m_genre;
    QString m_mood;
    QString m_studio;
    QString m_plot;
    int m_year;
    int m_movieId;
};

#endif // MOVIEMODEL_H
