#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "GameEngine.h"
#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonStart_clicked();  // Slot for the start button
    void on_strategyComboBox_currentIndexChanged(int index);  // Slot for combo box changes
    void on_pushButtonRock_clicked();
    void on_pushButtonPaper_clicked();
    void on_pushButtonScissors_clicked();
    void updateUI(const QString &humanChoice, const QString &computerChoice, const QString &computerPrediction, const QString &winner);
    void updateRound();
    void updateStats();
    void resetGame();
    void endOfRound();

private:
    Ui::MainWindow *ui;
    GameEngine *gameEngine;
    QLineEdit *lineEditNumberOfRounds;
    QPushButton *pushButtonStart;
    QComboBox *strategyComboBox;
    QLabel *labelRound;  // Declare the round label
    QGroupBox *groupBoxChoices;
    QPushButton *pushButtonRock;
    QPushButton *pushButtonPaper;
    QPushButton *pushButtonScissors;
    QGroupBox *groupBoxResults;
    QLabel *labelHumanChoice;
    QLabel *labelHumanChoiceResult;
    QLabel *labelComputerChoice;
    QLabel *labelComputerChoiceResult;
    QLabel *labelWinner;
    QLabel *labelWinnerResult;
    QLabel *labelComputerPrediction;
    QLabel *labelComputerPredictionResult;

    QGroupBox *groupBoxStatistics;
    QLabel *labelHumanWins;
    QLabel *labelHumanWinsResult;
    QLabel *labelComputerWins;
    QLabel *labelComputerWinsResult;
    QLabel *labelTies;
    QLabel *labelTiesResult;
    int roundCount;

    void setupChoiceButtons(QVBoxLayout *layout);  // Add this line

};

#endif // MAINWINDOW_H
