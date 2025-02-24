/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_original;
    QLabel *label_pic;
    QListWidget *functionListWidget;
    QGroupBox *groupBox1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *dims;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QPushButton *GrayscaleButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *ThreshButton;
    QSpinBox *ThreshspinBox;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_5;
    QComboBox *HistogramcomboBox;
    QPushButton *HistogramButton;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_7;
    QComboBox *MorphologicalcomboBox;
    QLabel *label_7;
    QSpinBox *spinBox;
    QLabel *label_8;
    QComboBox *MorphcomboBox;
    QPushButton *MorphologicalButton;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_10;
    QPushButton *FFTButton;
    QPushButton *RestoreImageButton;
    QComboBox *borderComboBox;
    QSpinBox *FFTspinBox;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *smoothingComboBox;
    QLabel *label_6;
    QSpinBox *SmoothingspinBox;
    QLabel *label_freq;
    QDoubleSpinBox *FrequencySpinBox;
    QLabel *label_3;
    QSpinBox *OrderspinBox;
    QPushButton *BlurButton;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout;
    QPushButton *PhaseButton;
    QSpinBox *PhasespinBox;
    QGroupBox *groupBox2;
    QVBoxLayout *verticalLayout_6;
    QComboBox *SavecomboBox;
    QLineEdit *NamelineEdit;
    QPushButton *SaveFButton;
    QPushButton *DeleteFButton;
    QPushButton *ExecuteButton;
    QWidget *layoutWidget7;
    QVBoxLayout *verticalLayout_2;
    QPushButton *FlipVerticalButton;
    QPushButton *FlipHorizontalButton;
    QPushButton *RotateButton;
    QWidget *layoutWidget8;
    QVBoxLayout *verticalLayout_3;
    QComboBox *EdgeDetectionComboBox;
    QLabel *label_4;
    QSpinBox *KernelspinBox;
    QLabel *label_2;
    QSplitter *splitter;
    QSpinBox *EdgespinBox1;
    QSpinBox *EdgespinBox2;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_8;
    QSpinBox *XspinBox;
    QSpinBox *YspinBox;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *EdgeButton;
    QWidget *layoutWidget9;
    QVBoxLayout *verticalLayout_8;
    QPushButton *UndoButton;
    QPushButton *RedoButton;
    QPushButton *ResetButton;
    QWidget *layoutWidget10;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *SaveButton;
    QPushButton *DeleteButton;
    QWidget *layoutWidget11;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *LoadButton;
    QPushButton *captureImageButton;
    QPushButton *helpButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1680, 936);
        MainWindow->setMaximumSize(QSize(1920, 1080));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(18);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("/* Dark mode styles */\n"
"QWidget {\n"
"    background-color: #333; /* Dark background color */\n"
"    color: #ffffff; /* Light text color */\n"
"}\n"
"\n"
"QGroupBox {\n"
"    background-color: transparent; /* Transparent background */\n"
"    border: none; /* No border */\n"
"    margin-top: 10px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 3px;\n"
"}\n"
"\n"
"QGroupBox:focus {\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton,\n"
"QToolButton {\n"
"    background-color: #6495ED; /* Cornflower Blue background color */\n"
"    color: #ffffff; /* White text color */\n"
"    border: none; /* No border */\n"
"    border-radius: 5px;\n"
"    padding: 8px 16px; /* Adjust padding as needed */\n"
"    min-width: 100px;\n"
"    font-size: 12px; /* Adjust font size as needed */\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover,\n"
"QToolButton:hover {\n"
"    background-color: #4169E1; /* Darker blue on hover */\n"
"    cur"
                        "sor: pointer;\n"
"}\n"
"\n"
"QPushButton:pressed,\n"
"QToolButton:pressed {\n"
"    background-color: #1E90FF; /* Darker blue when pressed */\n"
"}\n"
"\n"
"QLineEdit,\n"
"QComboBox {\n"
"    background-color: #666; /* Dark gray background */\n"
"    color: #fff; /* White text color */\n"
"    border: 1px solid #6495ED; /* Blue border */\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    font-size: 12px; /* Adjust font size as needed */\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background: transparent;\n"
"    width: 10px; /* Width of the scrollbar */\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #888; /* Gray scrollbar handle */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #aaa; /* Lighter handle color on hover */\n"
"}"));
        MainWindow->setDocumentMode(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(250, 290, 1191, 471));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(93, 30, 1021, 401));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_original = new QLabel(layoutWidget);
        label_original->setObjectName("label_original");
        label_original->setStyleSheet(QString::fromUtf8("border: 2px solid #6495ED; /* Blue border */\n"
""));

        horizontalLayout_7->addWidget(label_original);

        label_pic = new QLabel(layoutWidget);
        label_pic->setObjectName("label_pic");
        label_pic->setStyleSheet(QString::fromUtf8("QLabel{\n"
"border: 2px solid #6495ED; /* Blue border */\n"
"\n"
"}"));

        horizontalLayout_7->addWidget(label_pic);

        functionListWidget = new QListWidget(centralwidget);
        functionListWidget->setObjectName("functionListWidget");
        functionListWidget->setGeometry(QRect(1460, 220, 141, 211));
        groupBox1 = new QGroupBox(centralwidget);
        groupBox1->setObjectName("groupBox1");
        groupBox1->setGeometry(QRect(1180, 750, 281, 71));
        horizontalLayout_3 = new QHBoxLayout(groupBox1);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(groupBox1);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        dims = new QLabel(groupBox1);
        dims->setObjectName("dims");

        horizontalLayout_3->addWidget(dims);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(30, 140, 197, 80));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        GrayscaleButton = new QPushButton(layoutWidget1);
        GrayscaleButton->setObjectName("GrayscaleButton");

        verticalLayout_4->addWidget(GrayscaleButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        ThreshButton = new QPushButton(layoutWidget1);
        ThreshButton->setObjectName("ThreshButton");

        horizontalLayout->addWidget(ThreshButton);

        ThreshspinBox = new QSpinBox(layoutWidget1);
        ThreshspinBox->setObjectName("ThreshspinBox");
        ThreshspinBox->setMaximum(255);

        horizontalLayout->addWidget(ThreshspinBox);


        verticalLayout_4->addLayout(horizontalLayout);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(690, 120, 175, 76));
        verticalLayout_5 = new QVBoxLayout(layoutWidget2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        HistogramcomboBox = new QComboBox(layoutWidget2);
        HistogramcomboBox->addItem(QString());
        HistogramcomboBox->addItem(QString());
        HistogramcomboBox->setObjectName("HistogramcomboBox");

        verticalLayout_5->addWidget(HistogramcomboBox);

        HistogramButton = new QPushButton(layoutWidget2);
        HistogramButton->setObjectName("HistogramButton");

        verticalLayout_5->addWidget(HistogramButton);

        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(340, 110, 180, 180));
        verticalLayout_7 = new QVBoxLayout(layoutWidget3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        MorphologicalcomboBox = new QComboBox(layoutWidget3);
        MorphologicalcomboBox->addItem(QString());
        MorphologicalcomboBox->addItem(QString());
        MorphologicalcomboBox->addItem(QString());
        MorphologicalcomboBox->addItem(QString());
        MorphologicalcomboBox->setObjectName("MorphologicalcomboBox");

        verticalLayout_7->addWidget(MorphologicalcomboBox);

        label_7 = new QLabel(layoutWidget3);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(label_7);

        spinBox = new QSpinBox(layoutWidget3);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(3);
        spinBox->setMaximum(9);
        spinBox->setSingleStep(2);

        verticalLayout_7->addWidget(spinBox);

        label_8 = new QLabel(layoutWidget3);
        label_8->setObjectName("label_8");
        label_8->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(label_8);

        MorphcomboBox = new QComboBox(layoutWidget3);
        MorphcomboBox->addItem(QString());
        MorphcomboBox->addItem(QString());
        MorphcomboBox->addItem(QString());
        MorphcomboBox->setObjectName("MorphcomboBox");

        verticalLayout_7->addWidget(MorphcomboBox);

        MorphologicalButton = new QPushButton(layoutWidget3);
        MorphologicalButton->setObjectName("MorphologicalButton");

        verticalLayout_7->addWidget(MorphologicalButton);

        layoutWidget4 = new QWidget(centralwidget);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(1460, 10, 172, 151));
        verticalLayout_10 = new QVBoxLayout(layoutWidget4);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        FFTButton = new QPushButton(layoutWidget4);
        FFTButton->setObjectName("FFTButton");

        verticalLayout_10->addWidget(FFTButton);

        RestoreImageButton = new QPushButton(layoutWidget4);
        RestoreImageButton->setObjectName("RestoreImageButton");

        verticalLayout_10->addWidget(RestoreImageButton);

        borderComboBox = new QComboBox(layoutWidget4);
        borderComboBox->addItem(QString());
        borderComboBox->addItem(QString());
        borderComboBox->addItem(QString());
        borderComboBox->addItem(QString());
        borderComboBox->addItem(QString());
        borderComboBox->addItem(QString());
        borderComboBox->setObjectName("borderComboBox");

        verticalLayout_10->addWidget(borderComboBox);

        FFTspinBox = new QSpinBox(layoutWidget4);
        FFTspinBox->setObjectName("FFTspinBox");
        FFTspinBox->setMinimum(2);
        FFTspinBox->setMaximum(4096);
        FFTspinBox->setSingleStep(2);

        verticalLayout_10->addWidget(FFTspinBox);

        layoutWidget5 = new QWidget(centralwidget);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(340, 40, 605, 34));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        smoothingComboBox = new QComboBox(layoutWidget5);
        smoothingComboBox->addItem(QString());
        smoothingComboBox->addItem(QString());
        smoothingComboBox->addItem(QString());
        smoothingComboBox->addItem(QString());
        smoothingComboBox->addItem(QString());
        smoothingComboBox->addItem(QString());
        smoothingComboBox->setObjectName("smoothingComboBox");

        horizontalLayout_2->addWidget(smoothingComboBox);

        label_6 = new QLabel(layoutWidget5);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_6);

        SmoothingspinBox = new QSpinBox(layoutWidget5);
        SmoothingspinBox->setObjectName("SmoothingspinBox");
        SmoothingspinBox->setMinimum(3);
        SmoothingspinBox->setMaximum(9);
        SmoothingspinBox->setSingleStep(2);
        SmoothingspinBox->setValue(3);

        horizontalLayout_2->addWidget(SmoothingspinBox);

        label_freq = new QLabel(layoutWidget5);
        label_freq->setObjectName("label_freq");
        label_freq->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_freq);

        FrequencySpinBox = new QDoubleSpinBox(layoutWidget5);
        FrequencySpinBox->setObjectName("FrequencySpinBox");
        FrequencySpinBox->setMinimum(0.100000000000000);
        FrequencySpinBox->setMaximum(10.000000000000000);
        FrequencySpinBox->setSingleStep(0.010000000000000);

        horizontalLayout_2->addWidget(FrequencySpinBox);

        label_3 = new QLabel(layoutWidget5);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_3);

        OrderspinBox = new QSpinBox(layoutWidget5);
        OrderspinBox->setObjectName("OrderspinBox");
        OrderspinBox->setMinimum(1);
        OrderspinBox->setMaximum(20);

        horizontalLayout_2->addWidget(OrderspinBox);

        BlurButton = new QPushButton(layoutWidget5);
        BlurButton->setObjectName("BlurButton");

        horizontalLayout_2->addWidget(BlurButton);

        layoutWidget6 = new QWidget(centralwidget);
        layoutWidget6->setObjectName("layoutWidget6");
        layoutWidget6->setGeometry(QRect(1300, 30, 134, 67));
        verticalLayout = new QVBoxLayout(layoutWidget6);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        PhaseButton = new QPushButton(layoutWidget6);
        PhaseButton->setObjectName("PhaseButton");

        verticalLayout->addWidget(PhaseButton);

        PhasespinBox = new QSpinBox(layoutWidget6);
        PhasespinBox->setObjectName("PhasespinBox");
        PhasespinBox->setMaximum(360);

        verticalLayout->addWidget(PhasespinBox);

        groupBox2 = new QGroupBox(centralwidget);
        groupBox2->setObjectName("groupBox2");
        groupBox2->setGeometry(QRect(1445, 440, 161, 231));
        verticalLayout_6 = new QVBoxLayout(groupBox2);
        verticalLayout_6->setObjectName("verticalLayout_6");
        SavecomboBox = new QComboBox(groupBox2);
        SavecomboBox->setObjectName("SavecomboBox");

        verticalLayout_6->addWidget(SavecomboBox);

        NamelineEdit = new QLineEdit(groupBox2);
        NamelineEdit->setObjectName("NamelineEdit");

        verticalLayout_6->addWidget(NamelineEdit);

        SaveFButton = new QPushButton(groupBox2);
        SaveFButton->setObjectName("SaveFButton");

        verticalLayout_6->addWidget(SaveFButton);

        DeleteFButton = new QPushButton(groupBox2);
        DeleteFButton->setObjectName("DeleteFButton");

        verticalLayout_6->addWidget(DeleteFButton);

        ExecuteButton = new QPushButton(groupBox2);
        ExecuteButton->setObjectName("ExecuteButton");

        verticalLayout_6->addWidget(ExecuteButton);

        layoutWidget7 = new QWidget(centralwidget);
        layoutWidget7->setObjectName("layoutWidget7");
        layoutWidget7->setGeometry(QRect(70, 290, 134, 123));
        verticalLayout_2 = new QVBoxLayout(layoutWidget7);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        FlipVerticalButton = new QPushButton(layoutWidget7);
        FlipVerticalButton->setObjectName("FlipVerticalButton");

        verticalLayout_2->addWidget(FlipVerticalButton);

        FlipHorizontalButton = new QPushButton(layoutWidget7);
        FlipHorizontalButton->setObjectName("FlipHorizontalButton");

        verticalLayout_2->addWidget(FlipHorizontalButton);

        RotateButton = new QPushButton(layoutWidget7);
        RotateButton->setObjectName("RotateButton");

        verticalLayout_2->addWidget(RotateButton);

        layoutWidget8 = new QWidget(centralwidget);
        layoutWidget8->setObjectName("layoutWidget8");
        layoutWidget8->setGeometry(QRect(1000, 20, 234, 271));
        verticalLayout_3 = new QVBoxLayout(layoutWidget8);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        EdgeDetectionComboBox = new QComboBox(layoutWidget8);
        EdgeDetectionComboBox->addItem(QString());
        EdgeDetectionComboBox->addItem(QString());
        EdgeDetectionComboBox->addItem(QString());
        EdgeDetectionComboBox->setObjectName("EdgeDetectionComboBox");
        EdgeDetectionComboBox->setEditable(false);

        verticalLayout_3->addWidget(EdgeDetectionComboBox);

        label_4 = new QLabel(layoutWidget8);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_4);

        KernelspinBox = new QSpinBox(layoutWidget8);
        KernelspinBox->setObjectName("KernelspinBox");
        KernelspinBox->setMinimum(3);
        KernelspinBox->setMaximum(9);
        KernelspinBox->setSingleStep(2);

        verticalLayout_3->addWidget(KernelspinBox);

        label_2 = new QLabel(layoutWidget8);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        splitter = new QSplitter(layoutWidget8);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        EdgespinBox1 = new QSpinBox(splitter);
        EdgespinBox1->setObjectName("EdgespinBox1");
        EdgespinBox1->setMinimum(0);
        EdgespinBox1->setMaximum(255);
        splitter->addWidget(EdgespinBox1);
        EdgespinBox2 = new QSpinBox(splitter);
        EdgespinBox2->setObjectName("EdgespinBox2");
        EdgespinBox2->setMinimum(0);
        EdgespinBox2->setMaximum(255);
        splitter->addWidget(EdgespinBox2);

        verticalLayout_3->addWidget(splitter);

        label_5 = new QLabel(layoutWidget8);
        label_5->setObjectName("label_5");

        verticalLayout_3->addWidget(label_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        XspinBox = new QSpinBox(layoutWidget8);
        XspinBox->setObjectName("XspinBox");
        XspinBox->setMinimum(-1);
        XspinBox->setMaximum(1);

        horizontalLayout_8->addWidget(XspinBox);

        YspinBox = new QSpinBox(layoutWidget8);
        YspinBox->setObjectName("YspinBox");
        YspinBox->setMinimum(-1);
        YspinBox->setMaximum(1);

        horizontalLayout_8->addWidget(YspinBox);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        EdgeButton = new QPushButton(layoutWidget8);
        EdgeButton->setObjectName("EdgeButton");

        horizontalLayout_6->addWidget(EdgeButton);


        verticalLayout_3->addLayout(horizontalLayout_6);

        layoutWidget9 = new QWidget(centralwidget);
        layoutWidget9->setObjectName("layoutWidget9");
        layoutWidget9->setGeometry(QRect(70, 460, 134, 123));
        verticalLayout_8 = new QVBoxLayout(layoutWidget9);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        UndoButton = new QPushButton(layoutWidget9);
        UndoButton->setObjectName("UndoButton");

        verticalLayout_8->addWidget(UndoButton);

        RedoButton = new QPushButton(layoutWidget9);
        RedoButton->setObjectName("RedoButton");

        verticalLayout_8->addWidget(RedoButton);

        ResetButton = new QPushButton(layoutWidget9);
        ResetButton->setObjectName("ResetButton");

        verticalLayout_8->addWidget(ResetButton);

        layoutWidget10 = new QWidget(centralwidget);
        layoutWidget10->setObjectName("layoutWidget10");
        layoutWidget10->setGeometry(QRect(20, 800, 541, 51));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget10);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        SaveButton = new QPushButton(layoutWidget10);
        SaveButton->setObjectName("SaveButton");

        horizontalLayout_4->addWidget(SaveButton);

        DeleteButton = new QPushButton(layoutWidget10);
        DeleteButton->setObjectName("DeleteButton");

        horizontalLayout_4->addWidget(DeleteButton);

        layoutWidget11 = new QWidget(centralwidget);
        layoutWidget11->setObjectName("layoutWidget11");
        layoutWidget11->setGeometry(QRect(10, 40, 277, 37));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        LoadButton = new QToolButton(layoutWidget11);
        LoadButton->setObjectName("LoadButton");

        horizontalLayout_5->addWidget(LoadButton);

        captureImageButton = new QPushButton(layoutWidget11);
        captureImageButton->setObjectName("captureImageButton");
        captureImageButton->setEnabled(true);
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("camera-photo")));
        captureImageButton->setIcon(icon);

        horizontalLayout_5->addWidget(captureImageButton);

        helpButton = new QPushButton(centralwidget);
        helpButton->setObjectName("helpButton");
        helpButton->setGeometry(QRect(1510, 890, 132, 32));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        HistogramcomboBox->setCurrentIndex(-1);
        MorphologicalcomboBox->setCurrentIndex(-1);
        smoothingComboBox->setCurrentIndex(0);
        EdgeDetectionComboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_original->setText(QString());
        label_pic->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Image Info :", nullptr));
        dims->setText(QCoreApplication::translate("MainWindow", "W:0 H:0", nullptr));
        GrayscaleButton->setText(QCoreApplication::translate("MainWindow", "Grayscale", nullptr));
        ThreshButton->setText(QCoreApplication::translate("MainWindow", "Binary", nullptr));
        HistogramcomboBox->setItemText(0, QCoreApplication::translate("MainWindow", "HistogramEqualization", nullptr));
        HistogramcomboBox->setItemText(1, QCoreApplication::translate("MainWindow", "HistogramStretching", nullptr));

        HistogramButton->setText(QCoreApplication::translate("MainWindow", "HistogramManipulation", nullptr));
        MorphologicalcomboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Erosion", nullptr));
        MorphologicalcomboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Dilate", nullptr));
        MorphologicalcomboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Opening", nullptr));
        MorphologicalcomboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Closing", nullptr));

        label_7->setText(QCoreApplication::translate("MainWindow", "Kernel Size", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Shape", nullptr));
        MorphcomboBox->setItemText(0, QCoreApplication::translate("MainWindow", "MORPH_RECT", nullptr));
        MorphcomboBox->setItemText(1, QCoreApplication::translate("MainWindow", "MORPH_ELLIPSE", nullptr));
        MorphcomboBox->setItemText(2, QCoreApplication::translate("MainWindow", "MORPH_CROSS", nullptr));

        MorphologicalButton->setText(QCoreApplication::translate("MainWindow", "Morphological Operations ", nullptr));
        FFTButton->setText(QCoreApplication::translate("MainWindow", "Fast Fourier Transform", nullptr));
        RestoreImageButton->setText(QCoreApplication::translate("MainWindow", "Restore Image", nullptr));
        borderComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "BORDER_CONSTANT", nullptr));
        borderComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "BORDER_REPLICATE", nullptr));
        borderComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "BORDER_REFLECT", nullptr));
        borderComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "BORDER_TRANSPARENT", nullptr));
        borderComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "BORDER_WRAP", nullptr));
        borderComboBox->setItemText(5, QString());

        smoothingComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "GaussianBlur", nullptr));
        smoothingComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "MeanBlur", nullptr));
        smoothingComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "MedianBlur", nullptr));
        smoothingComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "BilateralFilter", nullptr));
        smoothingComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "ButterworthHighPass", nullptr));
        smoothingComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "ButterworthLowPass", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "Kernel Size", nullptr));
        label_freq->setText(QCoreApplication::translate("MainWindow", "Frequency", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Order", nullptr));
        BlurButton->setText(QCoreApplication::translate("MainWindow", "Smoothing", nullptr));
        PhaseButton->setText(QCoreApplication::translate("MainWindow", "RotatePhase", nullptr));
        SaveFButton->setText(QCoreApplication::translate("MainWindow", "Save  ", nullptr));
        DeleteFButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        ExecuteButton->setText(QCoreApplication::translate("MainWindow", "Execute", nullptr));
        FlipVerticalButton->setText(QCoreApplication::translate("MainWindow", "FlipVertical", nullptr));
        FlipHorizontalButton->setText(QCoreApplication::translate("MainWindow", "FlipHorizontal", nullptr));
        RotateButton->setText(QCoreApplication::translate("MainWindow", "Rotate", nullptr));
        EdgeDetectionComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Canny Edge Detection", nullptr));
        EdgeDetectionComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Sobel Operator", nullptr));
        EdgeDetectionComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Scharr Operator", nullptr));

        EdgeDetectionComboBox->setCurrentText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Kernel Size", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "lowThreshold                    highThreshold", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "   x                                                y", nullptr));
        EdgeButton->setText(QCoreApplication::translate("MainWindow", "EdgeDetection", nullptr));
        UndoButton->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        RedoButton->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        ResetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        SaveButton->setText(QCoreApplication::translate("MainWindow", "Save Image", nullptr));
        DeleteButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        LoadButton->setText(QCoreApplication::translate("MainWindow", "Load An Image", nullptr));
        captureImageButton->setText(QCoreApplication::translate("MainWindow", "Capture Image", nullptr));
        helpButton->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
