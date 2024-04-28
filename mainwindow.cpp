#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GameEngine.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "StrategyFactory.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QFormLayout>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow()),
    gameEngine(nullptr),
    roundCount(0),
    labelComputerPrediction(nullptr),
    labelComputerPredictionResult(nullptr),
    groupBoxStatistics(nullptr),
    labelHumanWins(nullptr),
    labelHumanWinsResult(nullptr),
    labelComputerWins(nullptr),
    labelComputerWinsResult(nullptr),
    labelTies(nullptr),
    labelTiesResult(nullptr)
    {
    ui->setupUi(this);
        HumanPlayer *humanPlayer = new HumanPlayer();
        gameEngine = new GameEngine(humanPlayer);
    ComputerPlayer *computerPlayer = new ComputerPlayer(StrategyFactory::createStrategy(1));  // Default to RandomStrategy
    gameEngine = new GameEngine( computerPlayer);
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Strategy combo box
    strategyComboBox = new QComboBox(centralWidget);
    strategyComboBox->addItem("Smart Strategy");
    strategyComboBox->addItem("Random Strategy");
    layout->addWidget(strategyComboBox);

    // Line edit for number of rounds
    lineEditNumberOfRounds = new QLineEdit(centralWidget);
    lineEditNumberOfRounds->setPlaceholderText("Enter number of rounds");
    layout->addWidget(lineEditNumberOfRounds);

    // Start button
    pushButtonStart = new QPushButton("Start", centralWidget);
    layout->addWidget(pushButtonStart);

    // Label for displaying the current round
    labelRound = new QLabel("Round: 0", centralWidget);
    labelRound->setAlignment(Qt::AlignCenter);
    layout->addWidget(labelRound);

    // Group box for rock, paper, scissors choices
    groupBoxChoices = new QGroupBox("Choose Your Move", centralWidget);
    QHBoxLayout *choicesLayout = new QHBoxLayout(groupBoxChoices);
    pushButtonRock = new QPushButton("Rock", groupBoxChoices);
    pushButtonPaper = new QPushButton("Paper", groupBoxChoices);
    pushButtonScissors = new QPushButton("Scissors", groupBoxChoices);
    choicesLayout->addWidget(pushButtonRock);
    choicesLayout->addWidget(pushButtonPaper);
    choicesLayout->addWidget(pushButtonScissors);
    groupBoxChoices->setLayout(choicesLayout);
    layout->addWidget(groupBoxChoices);

    // Group box for results
    groupBoxResults = new QGroupBox("Results", centralWidget);
    QFormLayout *resultsLayout = new QFormLayout(groupBoxResults);
    labelHumanChoice = new QLabel("Human chooses:", groupBoxResults);
    labelHumanChoiceResult = new QLabel(groupBoxResults);
    labelComputerChoice = new QLabel("Computer chooses:", groupBoxResults);
    labelComputerChoiceResult = new QLabel(groupBoxResults);
    labelWinner = new QLabel("The winner:", groupBoxResults);
    labelWinnerResult = new QLabel(groupBoxResults);
    resultsLayout->addRow(labelHumanChoice, labelHumanChoiceResult);
    resultsLayout->addRow(labelComputerChoice, labelComputerChoiceResult);
    resultsLayout->addRow(labelWinner, labelWinnerResult);
    groupBoxResults->setLayout(resultsLayout);
    layout->addWidget(groupBoxResults);

    // Initialize and configure the computer prediction labels
    labelComputerPrediction = new QLabel("Computer predicts:", centralWidget);
    labelComputerPredictionResult = new QLabel(centralWidget);

    // Add the computer prediction labels to the layout
    layout->addWidget(labelComputerPrediction);
    layout->addWidget(labelComputerPredictionResult);

    // Initialize and configure the statistics group box
    groupBoxStatistics = new QGroupBox("Statistics", centralWidget);
    QFormLayout *statisticsLayout = new QFormLayout(groupBoxStatistics);

    labelHumanWins = new QLabel("Human wins:", groupBoxStatistics);
    labelHumanWinsResult = new QLabel("0", groupBoxStatistics);  // Initialize with default value
    labelComputerWins = new QLabel("Computer wins:", groupBoxStatistics);
    labelComputerWinsResult = new QLabel("0", groupBoxStatistics);  // Initialize with default value
    labelTies = new QLabel("Ties:", groupBoxStatistics);
    labelTiesResult = new QLabel("0", groupBoxStatistics);  // Initialize with default value

    statisticsLayout->addRow(labelHumanWins, labelHumanWinsResult);
    statisticsLayout->addRow(labelComputerWins, labelComputerWinsResult);
    statisticsLayout->addRow(labelTies, labelTiesResult);

    groupBoxStatistics->setLayout(statisticsLayout);
    layout->addWidget(groupBoxStatistics);

    // Set central widget and layout
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Connect signals and slots
    connect(pushButtonStart, &QPushButton::clicked, this, &MainWindow::on_pushButtonStart_clicked);
    connect(strategyComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_strategyComboBox_currentIndexChanged);
    connect(pushButtonRock, &QPushButton::clicked, this, &MainWindow::on_pushButtonRock_clicked);
    connect(pushButtonPaper, &QPushButton::clicked, this, &MainWindow::on_pushButtonPaper_clicked);
    connect(pushButtonScissors, &QPushButton::clicked, this, &MainWindow::on_pushButtonScissors_clicked);
}


MainWindow::~MainWindow()
{
    delete ui; // Ensure that the UI is cleaned up correctly
}

void MainWindow::on_pushButtonStart_clicked()
{

    int totalRounds = lineEditNumberOfRounds->text().toInt();  // Convert the input to an integer
    gameEngine->setTotalRounds(totalRounds);  // Set the total rounds in the GameEngine

    QString message = "Game started with " + lineEditNumberOfRounds->text() + " rounds";
    gameEngine->resetScores(); // Reset scores if needed
    roundCount = 1;  // Start from the first round
    updateStats(); // Update the statistics display
    lineEditNumberOfRounds->setEnabled(false); // Optionally disable changing rounds after start
    strategyComboBox->setEnabled(false); // Optionally disable changing strategy after start
    statusBar()->showMessage(message);
    qDebug() << message; // Log the start message to the debug console
}

void MainWindow::on_strategyComboBox_currentIndexChanged(int index) {
    int strategyType = index + 1; // Adjust index to match your StrategyFactory mappings
    Strategy *newStrategy = StrategyFactory::createStrategy(strategyType);
    gameEngine->setStrategy(newStrategy);
  //labelComputerPrediction->setVisible(showPredictions);
  //  labelComputerPredictionResult->setVisible(showPredictions);
    qDebug() << "\nStrategy changed to:" << strategyComboBox->itemText(index);
    QString strategy = strategyComboBox->itemText(index);
   // qDebug() << "Strategy changed to:" << strategy;
}

void MainWindow::on_pushButtonRock_clicked() {
    qDebug() << "\nRock selected";
    gameEngine->humanPlayerMakesChoice('R');
    updateRound();
}

void MainWindow::on_pushButtonPaper_clicked() {
    qDebug() << "\nPaper selected";
    gameEngine->humanPlayerMakesChoice('P');
    updateRound();
}

void MainWindow::on_pushButtonScissors_clicked() {
    qDebug() << "\nScissors selected";
    gameEngine->humanPlayerMakesChoice('S');
    updateRound();
}


void MainWindow::updateUI(const QString &humanChoice, const QString &computerChoice, const QString &computerPrediction, const QString &winner) {


    labelHumanChoiceResult->setText(humanChoice);
    labelComputerChoiceResult->setText(computerChoice);
    labelWinnerResult->setText(winner);
    labelRound->setText(QString("Round: %1").arg(roundCount));
    labelComputerPredictionResult ->setText(computerPrediction);

    qDebug() << "\nupdateUI() called - UI updated";
}

void MainWindow::updateRound() {
    qDebug() << "\nupdateRound() called - Start";

    // Get the computer's prediction before the actual choice is made
    char result = gameEngine->playNextRound();
    QString humanChoice = QString(QChar(gameEngine->getHumanChoice()));
    std :: cout << "QString computerChoice = QString(QChar(gameEngine->getComputerChoice()));" << std::endl;
    QString computerChoice = QString(QChar(gameEngine->getComputerChoice()));
    QString winner;

    QString computerPrediction = QString(QChar(gameEngine->getComputerPrediction()));
    qDebug() << "\nComputer Prediction: " << computerPrediction;



    qDebug() << "\nRound played - Result: " << result;

    if (result == 'H') {
        winner = "Human wins";
    } else if (result == 'C') {
        winner = "Computer wins";
    } else {
        winner = "It's a tie";
    }

    //qDebug() << "\nPerson: " << humanChoice << " vs Computer: " << computerChoice;
    qDebug() << "\nWinner: " << winner;

    // Increment the round count after each set of chances or a single play
   /* if (++chanceCount >= maxChances) {
        chanceCount = 0;
        roundCount++;
    }*/
    roundCount++;
    if (roundCount > gameEngine->getTotalRounds()) {
        endOfRound();
    } else {
        //Not predicting for now

        updateUI(humanChoice, computerChoice, computerPrediction, winner);
        updateStats();
    }

    qDebug() << "\nupdateRound() called - End";
}
void MainWindow::setupChoiceButtons(QVBoxLayout *layout) {
    groupBoxChoices = new QGroupBox("Choose Your Move", this);
    QHBoxLayout *choicesLayout = new QHBoxLayout;

    pushButtonRock = new QPushButton("Rock", groupBoxChoices);
    pushButtonPaper = new QPushButton("Paper", groupBoxChoices);
    pushButtonScissors = new QPushButton("Scissors", groupBoxChoices);

    choicesLayout->addWidget(pushButtonRock);
    choicesLayout->addWidget(pushButtonPaper);
    choicesLayout->addWidget(pushButtonScissors);

    groupBoxChoices->setLayout(choicesLayout);
    layout->addWidget(groupBoxChoices);

    connect(pushButtonRock, &QPushButton::clicked, this, &MainWindow::on_pushButtonRock_clicked);
    connect(pushButtonPaper, &QPushButton::clicked, this, &MainWindow::on_pushButtonPaper_clicked);
    connect(pushButtonScissors, &QPushButton::clicked, this, &MainWindow::on_pushButtonScissors_clicked);
}

void MainWindow::endOfRound() {
    QString finalMessage = (gameEngine->getHumanScore() > gameEngine->getComputerScore()) ? "You won!" : "Game over. You lost.";
    QMessageBox::information(this, "Game Over... Restarting", finalMessage);

    // Reset the game state
    gameEngine->resetScores();
    //chanceCount = 0;
    roundCount = 1; // Reset to 1 for the new game

    // Update the UI to reflect the reset
    updateStats();
    resetGame();
}
void MainWindow::updateStats() {
    qDebug() << "\nupdateStats() called ";
    labelHumanWinsResult->setText(QString::number(gameEngine->getHumanScore()));
    labelComputerWinsResult->setText(QString::number(gameEngine->getComputerScore()));
    labelTiesResult->setText(QString::number(gameEngine->getTieScore()));
    labelRound->setText(QString("Round: %1").arg(roundCount));
}
void MainWindow::resetGame() {
    qDebug() << "resetGame() called ";
    gameEngine->resetScores();
    updateStats();
    // Optionally, update other parts of the UI as needed, like resetting choices or messages
}
