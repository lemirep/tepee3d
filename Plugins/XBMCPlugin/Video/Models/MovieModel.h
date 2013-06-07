#ifndef MOVIEMODEL_H
#define MOVIEMODEL_H

#include <ListItem.h>
#include <QUrl>

class MovieModel : public Models::ListItem
{
    Q_OBJECT
public:

    enum MovieModelItemRoles
    {
        movieId = Qt::UserRole + 1,
        title,
        genre,
        mood, //UNUSED
        studio,
        thumbnail,
        plot,
        year,
        rating,
        file
    };

    explicit MovieModel(QObject *parent = 0, int movieId = -1);
    int id() const;
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    QString getTitle() const;
    QString getGenre() const;
    QString getMood() const;
    QString getStudio() const;
    QString getThumbnail() const;
    QString getPlot() const;
    QString getFile() const;
    int getYear() const;
    int getRating() const;

    void setTitle(const QString &title);
    void setGenre(const QString &genre);
    void setMood(const QString &mood);
    void setStudio(const QString &studio);
    void setThumbnail(const QString &thumbnail);
    void setPlot(const QString &plot);
    void setYear(int year);
    void setRating(int rating);
    void setFile(const QString &file);


private:
    QString m_title;
    QString m_genre;
    QString m_mood;
    QString m_studio;
    QString m_thumbnail;
    QString m_plot;
    QString m_file;
    int m_year;
    int m_rating;
    int m_movieId;
};

#endif // MOVIEMODEL_H
