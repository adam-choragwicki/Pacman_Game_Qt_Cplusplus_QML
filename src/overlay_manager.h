#pragma once

#include "game_result.h"
#include "qml_helper.h"

class OverlayManager
{
public:
    explicit OverlayManager(QmlHelper& qml_helper);

    void showTextOverlay(const QString& text);
    void hideTextOverlay();

    void showEscapeMenuOverlay();
    void hideEscapeMenuOverlay();

    void showEndGameOverlay(GameResult gameResult, const QString& score);
    void hideEndGameOverlay();

private:
    QmlHelper& qmlHelper_;

    QObject* textOverlay_{};
    QObject* escapeMenuOverlay_{};
    QObject* endGameOverlay_{};
};
