//-------------------------------------------------------------------------------------
// (w) 2025 by Jan Buchholz
// Example how to embed a static Go library to a C++ main file
// Build libsha512.a: "go build -buildmode=c-archive -o libsha512.a libsha512.go"
// This will also generate the corresponding libsha512.h C++ header file
//-------------------------------------------------------------------------------------

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <vector>
#include "libsha512.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Berechne SHA512 (Aufruf Go von C++ Beispiel)");
    QObject::connect(ui->btnOpenFile, SIGNAL(clicked()), this, SLOT(OnOpenTriggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ComputeSha(std::vector<uint8_t> stream)
{
    QString const hex[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};
    QString s = "";
    std::vector<char> v_out(GetSHAOutputSize());
    GoSlice go_v_in{
        stream.data(),
        static_cast<GoInt>(stream.size()),
        static_cast<GoInt>(stream.size()),
    };
    GoSlice go_v_out{
        v_out.data(),
        GetSHAOutputSize(),
        GetSHAOutputSize(),
    };
    Compute(go_v_in, go_v_out);
    for (const char &c: v_out) {
        quint8 b = c & 0xff;
        quint8 hi = b >> 4;
        quint8 lo = b & 0x0f;
        s = s + hex[hi] + hex[lo];
    }
    ui->edtSha512->setPlainText(s);
}

void MainWindow::OnOpenTriggered()
{
    ui->edtFilename->clear();
    ui->edtSha512->clear();
    QFileDialog openDialog;
    openDialog.setParent(this, Qt::Dialog|
                               Qt::WindowSystemMenuHint|
                               Qt::WindowCloseButtonHint|
                               Qt::WindowTitleHint|
                               Qt::CustomizeWindowHint);
    openDialog.setDirectory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    openDialog.setAcceptMode(QFileDialog::AcceptOpen);
    openDialog.setFileMode(QFileDialog::ExistingFile);
    openDialog.setNameFilter(tr("Alle Dateien (*.*)"));
    openDialog.setOptions(QFileDialog::ReadOnly);
    openDialog.setViewMode(QFileDialog::Detail);
    if (openDialog.exec() == QDialog::Accepted) {
        QStringList files = openDialog.selectedFiles();
        QString fileName = files.first();
        ui->edtFilename->setText(fileName);
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray blob = file.readAll();
            file.close();
            std::vector<uint8_t> stream(blob.begin(), blob.end());
            ComputeSha(stream);
        };
    }
}
