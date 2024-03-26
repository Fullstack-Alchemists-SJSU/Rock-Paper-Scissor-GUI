#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GameEngine.h"
#include "SmartStrategy.h"

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

    // Initialize the game engine with a default strategy
    gameEngine->setStrategy(new SmartStrategy());
}

void MainWindow::on_strategyComboBox_currentIndexChanged(int index) {
    // Example: 0 for SmartStrategy, 1 for RandomStrategy
    Strategy* newStrategy = nullptr;
    if (index == 0) {
        newStrategy = new SmartStrategy();
    } else {
        newStrategy = new RandomStrategy();
    }
    gameEngine->setStrategy(newStrategy);
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

    updateUI(humanChoice, computerChoice, winner);
    updateStats();
}

void MainWindow::updateUI(const QString &humanChoice, const QString &computerChoice, const QString &winner) {
    ui->labelHumanChoiceResult->setText(humanChoice);
    ui->labelComputerChoiceResult->setText(computerChoice);
    ui->labelWinnerResult->setText(winner);
    ui->labelRound->setText(QString("Round: %1").arg(roundCount));
}


void MainWindow::endOfRound() {
    chanceCount = 0;
    roundCount++;
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

