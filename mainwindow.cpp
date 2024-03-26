#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GameEngine.h"
#include "RandomStrategy.h"

#include <QString> // For QString conversions
#include <QDebug> // For console debugging (if needed)
#include <QFileDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , humanPlayer(new HumanPlayer())
    , computerPlayer(new ComputerPlayer(new RandomStrategy()))
{
    ui->setupUi(this);

    // Connect buttons to slots for individual choices
    connect(ui->pushButtonRock, &QPushButton::clicked, this, &MainWindow::on_pushButtonRock_clicked);
    connect(ui->pushButtonPaper, &QPushButton::clicked, this, &MainWindow::on_pushButtonPaper_clicked);
    connect(ui->pushButtonScissors, &QPushButton::clicked, this, &MainWindow::on_pushButtonScissors_clicked);

    // Connect the button for playing a round of three to the corresponding slot
    connect(ui->pushButtonPlayRound, &QPushButton::clicked, this, &MainWindow::playRoundOfThree);

    gameEngine = new GameEngine(humanPlayer, computerPlayer->getStrategy());
}


MainWindow::~MainWindow()
{
    delete ui;
    delete gameEngine;
    delete humanPlayer;
    delete computerPlayer;
}

void MainWindow::on_pushButtonRock_clicked()
{
    gameEngine->humanPlayerMakesChoice('R');
    updateRound();
}

void MainWindow::on_pushButtonPaper_clicked()
{
    gameEngine->humanPlayerMakesChoice('P');
    updateRound();
}

void MainWindow::on_pushButtonScissors_clicked()
{
    gameEngine->humanPlayerMakesChoice('S');
    updateRound();
}
void MainWindow::updateRound()
{
    char result = gameEngine->playNextRound();
    QString humanChoice(gameEngine->getHumanChoice());
    QString computerChoice(gameEngine->getComputerChoice());
    QString winner;
    switch (result) {
    case 'H': winner = "Human"; break;
    case 'C': winner = "Computer"; break;
    case 'T': winner = "Tie"; break;
    default: winner = "Error"; break;
    }
    updateUI(humanChoice, computerChoice, winner);
    updateStats();  // This call updates the UI with the latest scores
}

void MainWindow::playRoundOfThree() {
    // This method should initiate playing three rounds and then update the UI
    // Assuming GameEngine has a method to play three rounds and update scores
    gameEngine->playRoundOfThree();

    // After playing three rounds, update the UI with the new scores
    updateStats();
}

void MainWindow::updateUI(const QString &humanChoice, const QString &computerChoice, const QString &winner)
{
    ui->labelHumanChoiceResult->setText(humanChoice);
    ui->labelComputerChoiceResult->setText(computerChoice);
    ui->labelWinnerResult->setText(winner);
}

void MainWindow::updateStats()
{
    ui->labelHumanWinsResult->setText(QString::number(gameEngine->getHumanScore()));
    ui->labelComputerWinsResult->setText(QString::number(gameEngine->getComputerScore()));
    ui->labelTiesResult->setText(QString::number(gameEngine->getTieScore()));
}


void MainWindow::resetGame()
{
    gameEngine->resetScores();
    updateStats();
    // Reset other UI components if necessary
}

