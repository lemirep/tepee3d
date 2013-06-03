#include "MovieModel.h"

MovieModel::MovieModel(QObject *parent, int movieId) : Models::ListItem(parent)
{
    this->m_movieId = movieId;
}

int MovieModel::id() const
{
    return this->m_movieId;
}

QVariant MovieModel::data(int role) const
{
    switch (role)
    {
    case movieId:
            return this->id();
    case title:
        return this->getTitle();
    case genre:
        return this->getGenre();
    case mood:
        return this->getMood();
    case studio:
        return this->getStudio();
    case thumbnail:
        return this->getThumbnail();
    case plot:
        return this->getPlot();
    case year:
        return this->getYear();
    case rating:
        return this->getRating();
    case file:
        return this->getFile();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MovieModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[movieId] = "movieId";
    roleNames[title] = "title";
    roleNames[genre] = "genre";
    roleNames[mood] = "mood";
    roleNames[studio] = "studio";
    roleNames[thumbnail] = "thumbnail";
    roleNames[plot] = "plot";
    roleNames[year] = "year";
    roleNames[rating] = "rating";
    roleNames[file] = "file";
    return roleNames;
}

int MovieModel::getRating() const
{
    return this->m_rating;
}

void MovieModel::setRating(int rating)
{
    this->m_rating = rating;
}

int MovieModel::getYear() const
{
    return this->m_year;
}

void MovieModel::setYear(int year)
{
    this->m_year = year;
}

QString MovieModel::getPlot() const
{
    return this->m_plot;
}

void MovieModel::setPlot(const QString &plot)
{
    this->m_plot = plot;
}

QString MovieModel::getThumbnail() const
{
    return this->m_thumbnail;
}

void MovieModel::setThumbnail(const QString &thumbnail)
{
    this->m_thumbnail = QUrl::toPercentEncoding(thumbnail);
}

QString MovieModel::getStudio() const
{
    return this->m_studio;
}

void MovieModel::setStudio(const QString &studio)
{
    this->m_studio = studio;
}

QString MovieModel::getMood() const
{
    return this->m_mood;
}

void MovieModel::setMood(const QString &mood)
{
    this->m_mood = mood;
}

QString MovieModel::getGenre() const
{
    return this->m_genre;
}

void MovieModel::setGenre(const QString &genre)
{
    this->m_genre = genre;
}

QString MovieModel::getTitle() const
{
    return this->m_title;
}

void MovieModel::setTitle(const QString &title)
{
    this->m_title = title;
}

QString MovieModel::getFile() const
{
    return this->m_file;
}

void MovieModel::setFile(const QString &file)
{
    this->m_file = file;
}
