#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GameEngine.h"
#include "SmartStrategy.h"

#include <QMessageBox>

#include <QString> // For QString conversions
#include <QDebug> // For console debugging (if needed)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow()),
    gameEngine(new GameEngine(new HumanPlayer())),
    chanceCount(0),
    roundCount(1) {
    ui->setupUi(this);

    connect(ui->pushButtonRock, &QPushButton::clicked, this, &MainWindow::on_pushButtonRock_clicked);
    connect(ui->pushButtonPaper, &QPushButton::clicked, this, &MainWindow::on_pushButtonPaper_clicked);
    connect(ui->pushButtonScissors, &QPushButton::clicked, this, &MainWindow::on_pushButtonScissors_clicked);

    // Connect the strategy combo box signal to the slot
    connect(ui->strategyComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(on_strategyComboBox_currentIndexChanged(int)));

    connect(ui->spinBoxNumberOfRounds, SIGNAL(valueChanged(int)),
            this, SLOT(on_numberOfRoundsValueChanged(int)));




    // Initialize the game engine with a default strategy
    gameEngine->setStrategy(new SmartStrategy());
}

void MainWindow::on_strategyComboBox_currentIndexChanged(int index) {
    // Example: 0 for SmartStrategy, 1 for RandomStrategy
    Strategy* newStrategy = nullptr;
    bool showPredictions = false;

    if (index == 0) {
        newStrategy = new SmartStrategy();
        showPredictions = true;  // Show predictions for SmartStrategy
    } else {
        newStrategy = new RandomStrategy();
        showPredictions = false;  // Hide predictions for RandomStrategy
    }

    gameEngine->setStrategy(newStrategy);

    // Set visibility of prediction labels based on the selected strategy
    ui->labelComputerPrediction->setVisible(showPredictions);
    ui->labelComputerPredictionResult->setVisible(showPredictions);
}

void MainWindow::on_numberOfRoundsValueChanged(int value) {
    gameEngine->setTotalRounds(value);
}


MainWindow::~MainWindow() {
    delete ui;
    delete gameEngine;
    delete humanPlayer;
    delete computerPlayer;
}

void MainWindow::on_pushButtonRock_clicked() {
    gameEngine->humanPlayerMakesChoice('R');
    updateRound();
}

void MainWindow::on_pushButtonPaper_clicked() {
    gameEngine->humanPlayerMakesChoice('P');
    updateRound();
}

void MainWindow::on_pushButtonScissors_clicked() {
    gameEngine->humanPlayerMakesChoice('S');
    updateRound();
}

void MainWindow::updateRound() {
    // Get the computer's prediction before the actual choice is made
    QString computerPrediction = QString(QChar(gameEngine->getComputerPrediction()));

    char result = gameEngine->playNextRound();

    QString humanChoice = QString(QChar(gameEngine->getHumanChoice()));
    QString computerChoice = QString(QChar(gameEngine->getComputerChoice()));
    QString winner;

    if (result == 'H') {
        winner = "Human wins";
    } else if (result == 'C') {
        winner = "Computer wins";
    } else {
        winner = "It's a tie";
    }

    // Increment the round count after each set of chances or a single play
    if (++chanceCount >= maxChances) {
        chanceCount = 0;
        roundCount++;
    }
    if (roundCount >= gameEngine->getTotalRounds()) {
        endOfRound();
       // QString finalMessage = (gameEngine->getHumanScore() > gameEngine->getComputerScore()) ? "You won!" : "Game over. You lost.";
        //QMessageBox::information(this, "Game Over", finalMessage);
        // Optionally, disable game controls here to prevent further play
    }


    // Update the UI with the choices, winner, and the computer's prediction
    updateUI(humanChoice, computerChoice, computerPrediction, winner);
    updateStats();
}


void MainWindow::updateUI(const QString &humanChoice, const QString &computerChoice, const QString &computerPrediction, const QString &winner) {
    ui->labelHumanChoiceResult->setText(humanChoice);
    ui->labelComputerChoiceResult->setText(computerChoice);
    // Assuming you have a QLabel for displaying computer's prediction, e.g., labelComputerPredictionResult
    ui->labelComputerPredictionResult->setText(computerPrediction);
    ui->labelWinnerResult->setText(winner);
    ui->labelRound->setText(QString("Round: %1").arg(roundCount));
}



void MainWindow::endOfRound() {
    QString finalMessage = (gameEngine->getHumanScore() > gameEngine->getComputerScore()) ? "You won!" : "Game over. You lost.";
    QMessageBox::information(this, "Game Over... Restarting", finalMessage);

    // Reset the game state
    gameEngine->resetScores();
    chanceCount = 0;
    roundCount = 1; // Reset to 1 for the new game

    // Update the UI to reflect the reset
    updateStats();
    resetGame();
}

/*
void MainWindow::updateUI(const QString &humanChoice, const QString &computerChoice, const QString &winner) {
    ui->labelHumanChoiceResult->setText(humanChoice);
    ui->labelComputerChoiceResult->setText(computerChoice);
    ui->labelWinnerResult->setText(winner);
    ui->labelRound->setText(QString("Round: %1").arg(roundCount));
}
*/
void MainWindow::updateStats() {
    ui->labelHumanWinsResult->setText(QString::number(gameEngine->getHumanScore()));
    ui->labelComputerWinsResult->setText(QString::number(gameEngine->getComputerScore()));
    ui->labelTiesResult->setText(QString::number(gameEngine->getTieScore()));
    ui->labelRound->setText(QString("Round: %1").arg(roundCount));
}





void MainWindow::resetGame() {
    gameEngine->resetScores();
    updateStats();
    // Optionally, update other parts of the UI as needed, like resetting choices or messages
}
