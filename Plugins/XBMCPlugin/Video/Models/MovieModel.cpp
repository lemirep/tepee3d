#include "MovieModel.h"

MovieModel::MovieModel(QObject *parent, int movieId) : PlayableItemModel(parent)
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
    case genre:
        return this->getGenre();
    case mood:
        return this->getMood();
    case studio:
        return this->getStudio();
    case plot:
        return this->getPlot();
    case year:
        return this->getYear();
    default:
        return PlayableItemModel::data(role);
    }
}

QHash<int, QByteArray> MovieModel::roleNames() const
{
    QHash<int, QByteArray> roleNames = PlayableItemModel::roleNames();

    roleNames[movieId] = "movieId";
    roleNames[genre] = "genre";
    roleNames[mood] = "mood";
    roleNames[studio] = "studio";
    roleNames[plot] = "plot";
    roleNames[year] = "year";
    return roleNames;
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
