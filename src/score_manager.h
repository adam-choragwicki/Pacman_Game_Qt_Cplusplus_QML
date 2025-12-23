#pragma once

#include <QObject>

class ScoreManager : public QObject
{
    Q_OBJECT

signals:
    void changed();

public:
    ScoreManager() = default;

    void reset()
    {
        score_ = 0;
        emit changed();
    }

    Q_PROPERTY(int score READ getScore NOTIFY changed)
    [[nodiscard]] int getScore() const { return score_; }

    void increaseScoreForEatingStandardPellet()
    {
        score_ += 1;
        emit changed();
    }

    void increaseScoreForEatingPowerPellet()
    {
        score_ += 100;
        emit changed();
    }

    void increaseScoreForEatingGhost()
    {
        score_ += 200;
        emit changed();
    }

    [[nodiscard]] QString getScoreAsString() const { return QString::number(score_); }

private:
    int score_{};
};
