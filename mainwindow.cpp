#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QTime>
#include <cstdlib>
#include <QString>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent){
    this->setupUI();

    words<<"calculator"<<"Vietnam"<<"gaysex"<<"lingura";

    startNewGame();
}

void MainWindow::setupUI(){
    this->setWindowTitle("Thuhang yourself");
    this->resize(300,500);
    QWidget* centralWidget = new QWidget{this};
    QVBoxLayout* mainLayout = new QVBoxLayout{centralWidget};

    nrLettersLabel = new QLabel{this};
    wordLabel = new QLabel{this};
    mainLayout->addWidget(nrLettersLabel);
    mainLayout->addWidget(wordLabel);

    QHBoxLayout* inputLayout = new QHBoxLayout{};
    letterInput = new QLineEdit{this};
    btnGuess = new QPushButton{"Guess", this};

    inputLayout->addWidget(letterInput);
    inputLayout->addWidget(btnGuess);
    mainLayout->addLayout(inputLayout);

    attemptsLabel = new QLabel{this};
    mainLayout->addWidget(attemptsLabel);

    wrongList = new QListWidget{this};
    mainLayout->addWidget(wrongList);

    statusLabel = new QLabel{this};
    mainLayout->addWidget(statusLabel);

    btnNewGame = new QPushButton{"New Game", this};
    mainLayout->addWidget(btnNewGame);


    setCentralWidget(centralWidget);

    connect(btnGuess, &QPushButton::clicked,this,&MainWindow::sendGuess);
    connect(btnNewGame, &QPushButton::clicked, this, &MainWindow::buttonNewGame);
}

void MainWindow::startNewGame(){

    currentWord = words[rand()%words.size()];
    displayedWord = QString(currentWord.size(),'_');
    QChar letter = currentWord[0];
    for(int i=0; i<currentWord.size(); i++)
    {
        if(currentWord[i] == letter)
            displayedWord[i] = letter;
    }
    attempts = 7;
    nrLettersLabel->setText("Letters: " + QString::number(currentWord.size()));
    wordLabel->setText(displayedWord);
    attemptsLabel->setText("Remaining <3: " + QString::number(attempts));
    statusLabel->clear();
    wrongList->clear();
}

void MainWindow::sendGuess()
{
    QString guess = letterInput->text().trimmed();
    if(guess.size()!=1)
    {
        statusLabel->setText("Plese enter a valid value");
    }

    QChar ch = guess[0];

        if(guessedLetters.contains(ch))
        {
            statusLabel->setText("Already guessed");
            attempts--;
            attemptsLabel->setText("Remaining <3: " + QString::number(attempts));
        }
        else if(currentWord.contains(ch))
        {
            for(int i=0; i<currentWord.size(); i++)
            {
                if(currentWord[i] == ch)
                    displayedWord[i] = ch;
            }
            wordLabel->setText(displayedWord);
            guessedLetters.insert(ch);
            if(displayedWord == currentWord)
                statusLabel->setText("You won");
        }
        else{
            wrongList->addItem(ch);
            attempts--;
            attemptsLabel->setText("Remaining <3: " + QString::number(attempts));
            if (attempts == 0) {
                statusLabel->setText("You lost! The word was: " + currentWord);
             }
        }

}

void MainWindow::buttonNewGame(){
    startNewGame();
}

MainWindow::~MainWindow()
{

}
