#ifndef LINEDITOR_H
#define LINEDITOR_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QColor>
#include <QColorDialog>
#include <QFontDialog>
#include <QPalette>
#include <QImageReader>
#include <QTextBlockFormat>


QT_BEGIN_NAMESPACE
namespace Ui
{
class lineditor;
}

QT_END_NAMESPACE

class lineditor : public QMainWindow
{
    Q_OBJECT

public:
    lineditor(QWidget *parent = nullptr);
    ~lineditor();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();

    void on_actionHTML_triggered();

    void on_actionText_triggered();

    void on_actionPDF_triggered();

    void on_actionPrint_triggered();

    void on_actionUndo_triggered();

    void on_actionExit_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionDelete_triggered();

    void on_actionSelect_All_triggered();

    void on_actionFind_triggered();

    void on_actionBold_triggered();

    void on_actionItalic_triggered();

    void on_actionUnderline_triggered();

    void on_actionDate_triggered();

    void on_actionBullet_List_triggered();

    void on_actionNumbered_List_triggered();

    void on_actionCheck_Box_triggered();

    void on_actionImage_triggered();

    void on_actionText_from_File_triggered();

    void on_actionTable_triggered();

    void on_actionContents_triggered();

    void on_actionAbout_triggered();

    void on_actionFAQ_triggered();

    void on_actionAlign_Left_triggered();

    void on_actionAlign_Right_triggered();

    void on_actionCentered_triggered();

    void on_actionJustified_triggered();

    void on_actionBackground_triggered();

    void on_actionText_Color_triggered();

    void on_actionHighlight_triggered();

    void on_actionFont_triggered();

private:
    Ui::lineditor *ui;
    QString currentFile = "";
};
#endif // LINEDITOR_H
