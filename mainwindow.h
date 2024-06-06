#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void connectUI();

    QString currentWord;
    QStringList words;
    QLabel *wordLabel, *statusLabel, *attemptsLabel, *nrLettersLabel;
    QLineEdit *letterInput;
    QPushButton *btnNewGame, *btnGuess;
    QListWidget *wrongList;
    QString displayedWord;
    QSet<QChar> guessedLetters;
    int attempts, nrLetters;


    void startNewGame();

private slots:
    void sendGuess();
    void buttonNewGame();

};

#endif // MAINWINDOW_H
