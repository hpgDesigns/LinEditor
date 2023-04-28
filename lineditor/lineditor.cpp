#include "lineditor.h"
#include "ui_lineditor.h"

lineditor::lineditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lineditor)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    ui->textEdit->setFontFamily("Tahoma");
    ui->textEdit->setFontPointSize(12);
    ui->textEdit->setLineWidth(100);

    //setup linespacing ....setLineHeight() function
    qreal lineSpacing = 180;
    QTextCursor textCursor = ui->textEdit->textCursor();

    QTextBlockFormat * newFormat = new QTextBlockFormat();
    textCursor.clearSelection();
    textCursor.select(QTextCursor::Document);
    newFormat->setLineHeight(lineSpacing, QTextBlockFormat::ProportionalHeight);
    textCursor.setBlockFormat(*newFormat);

}

lineditor::~lineditor()
{
    delete ui;
}


void lineditor::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setLineWidth(250);
    ui->textEdit->setText(QString());
}


void lineditor::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;//store the file
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for reading text
    QTextStream in(&file);

    // Copy text in the string
    QString text = in.readAll();

    // Put the text in the textEdit widget
    ui->textEdit->setText(text);

    // Close the file
    file.close();

}

void lineditor::on_actionSave_As_triggered()
{
    // Opens a dialog for saving a file
    QString fileName = QFileDialog::getSaveFileName(this, "Save as Markdown file", QString(), "*.md");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".md"); }
    // An object for reading and writing files
    QFile file(fileName);

    // Try to open a file with write only options
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    // Store the currentFile name
    currentFile = fileName;

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for writing text
    QTextStream out(&file);

    // Copy text in the textEdit widget and convert to markdown text
    QString text = ui->textEdit->toMarkdown();

    // Output to file
    out << text;

    // Close the file
    file.close();
}


void lineditor::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save As Plain Text", QString(), "*.txt");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".txt"); }
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void lineditor::on_actionHTML_triggered()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )this, "Export HTML", QString(), "*.html");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".html"); }
    //QString fileName = QFileDialog::getSaveFileName(this, "Save");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toHtml();
    out << text;
    file.close();

}

void lineditor::on_actionText_triggered()
{
    //export file to RichText Document

}


void lineditor::on_actionPDF_triggered()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )this, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toHtml();
    out << text;
    file.close();
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.colorMode();
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(text);
   // doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}


void lineditor::on_actionPrint_triggered()
{
    //print the file to printer or PDF File
    // Allows for interacting with printer
    QPrinter printer;

    // You'll put your printer name here
    printer.setPrinterName("Printer Name");

    // Create the print dialog and pass the name and parent
    QPrintDialog pDialog(&printer, this);

    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Access Printer");
        return;
    }

    // Send the text to the printer
    ui->textEdit->print(&printer);
}


void lineditor::on_actionExit_triggered()
{
    //exit the application
    QApplication::exit();
}

void lineditor::on_actionUndo_triggered()
{
    //undo the last action
    ui->textEdit->undo();
}


void lineditor::on_actionRedo_triggered()
{
    //redo the last action
    ui->textEdit->redo();
}


void lineditor::on_actionCut_triggered()
{
    //cut the selected text to clipboard
    ui->textEdit->cut();
}


void lineditor::on_actionCopy_triggered()
{
    //copy the selected text
    ui->textEdit->copy();
}


void lineditor::on_actionPaste_triggered()
{
    //pastethe text from the clipboard
    ui->textEdit->paste();
}


void lineditor::on_actionDelete_triggered()
{
    //delete everything in file
    ui->textEdit->deleteLater();
}


void lineditor::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}


void lineditor::on_actionFind_triggered()
{
    //searh for word and replace
}


void lineditor::on_actionBold_triggered()
{
    //set text to Bold
    QFont::Bold;
    ui->textEdit->setFontWeight(QFont::Bold);

}

void lineditor::on_actionItalic_triggered()
{
    //set font to Italic
    ui->textEdit->setFontItalic(true);

}

void lineditor::on_actionUnderline_triggered()
{
    //set font to underline
    //QFont::UnderlineResolved;
    ui->textEdit->setFontUnderline(true);
}


void lineditor::on_actionDate_triggered()
{
    //insert Time and Date stamp
}


void lineditor::on_actionBullet_List_triggered()
{
    //insert bullets list

}


void lineditor::on_actionNumbered_List_triggered()
{
    //insert numbered list

}


void lineditor::on_actionCheck_Box_triggered()
{
    //insert Check box
}


void lineditor::on_actionImage_triggered()
{
    //insert graphic
    QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
                                                ".", tr("Bitmap Files (*.bmp)\n"
                                                   "JPEG (*.jpg *jpeg)\n"
                                                   "GIF (*.gif)\n"
                                                   "PNG (*.png)\n"));
    QUrl Uri ( QString ( "file://%1" ).arg ( file ) );
    QImage image = QImageReader ( file ).read();

    QTextDocument * textDocument = ui->textEdit->document();
    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth( image.width() );
    imageFormat.setHeight( image.height() );
    imageFormat.setName( Uri.toString() );
    cursor.insertImage(imageFormat);
}

void lineditor::on_actionText_from_File_triggered()
{
    //insert text from file

}


void lineditor::on_actionTable_triggered()
{
    //insert table from file

}


void lineditor::on_actionContents_triggered()
{
    //display Contents of help file
}


void lineditor::on_actionAbout_triggered()
{
    //display short description of the app
    QString about_text;
    about_text = "Lineditor\n";
    about_text +="created by Hugh Greene(hugar678\n";
    about_text +="using QT";

    QMessageBox::about(this, "About Lineditor", about_text);
}


void lineditor::on_actionFAQ_triggered()
{
    //display Frequent Asked Questions about app

}


void lineditor::on_actionAlign_Left_triggered()
{
    //align text to left
    ui->textEdit->setAlignment(Qt::AlignLeft);
}


void lineditor::on_actionAlign_Right_triggered()
{
    //align text to right
    ui->textEdit->setAlignment(Qt::AlignRight);
}


void lineditor::on_actionCentered_triggered()
{
    //align text to the center
    ui->textEdit->setAlignment(Qt::AlignCenter);
}


void lineditor::on_actionJustified_triggered()
{
    //justify the text
    ui->textEdit->setAlignment(Qt::AlignJustify);
}


void lineditor::on_actionBackground_triggered()
{
    //change the background color of the work area
    QColor color = QColorDialog::getColor(Qt::blue, this, "Choose Color");
    if (color.isValid())
    {
        //setPalette(color); //changes the outer backgroundcolor
        QPalette p = ui->textEdit->palette(); // define pallete for textEdit..
        p.setColor(QPalette::Base, color); // set color "Red" for textedit base
        //p.setColor(QPalette::Text, color); // set text color which is selected from color pallete
        ui->textEdit->setPalette(p); // change textedit palette


    }
}


void lineditor::on_actionText_Color_triggered()
{
    //change the text color
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid())
    {
        ui->textEdit->setTextColor(color);

    }
}


void lineditor::on_actionHighlight_triggered()
{
    //change the selected text background color as a highlight
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid())
    {
        ui->textEdit->setTextBackgroundColor(color);

    }
}


void lineditor::on_actionFont_triggered()
{
    //change the font
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok)
    {
        ui->textEdit->setCurrentFont(font);

    }else return;
}

