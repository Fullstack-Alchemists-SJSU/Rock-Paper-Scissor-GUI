#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameEngine.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonRock_clicked();
    void on_pushButtonPaper_clicked();
    void on_pushButtonScissors_clicked();
    void updateUI(const QString &humanChoice, const QString &computerChoice, const QString &winner);
    void updateRound();
    void updateStats();
    void resetGame();
    void endOfRound();
    void on_strategyComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    GameEngine *gameEngine;
    HumanPlayer *humanPlayer;
    ComputerPlayer *computerPlayer;
    int chanceCount = 0;
    int roundCount = 1;
    const int maxChances = 5;  // Maximum chances per round

};

#endif // MAINWINDOW_H
