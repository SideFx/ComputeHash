//-------------------------------------------------------------------------------------
// (w) 2025 by Jan Buchholz
// Example how to link a static Go library to a C++ main file
// Build libsha512.a: "go build -buildmode=c-archive -o libsha512.a libsha512.go"
// This will also generate the corresponding libsha512.h C++ header file
//-------------------------------------------------------------------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void ComputeSha(std::vector<uint8_t> stream);
    Ui::MainWindow *ui;

private slots:
    void OnOpenTriggered();
};
#endif // MAINWINDOW_H
