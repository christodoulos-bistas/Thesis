#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include<QMouseEvent>
#include<QLabel>
#include<QEvent>
#include<QObject>
#include<QMap>
#include<QList>
#include<functional>
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#pragma once



using namespace cv;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LoadButton_clicked();
    void on_GrayscaleButton_clicked();
    void on_ResetButton_clicked();


    void on_BlurButton_clicked();

    void on_EdgeButton_clicked();

    void on_HistogramButton_clicked();





    void on_RotateButton_clicked();

    void on_FlipHorizontalButton_clicked();

    void on_FlipVerticalButton_clicked();















    void on_MorphologicalButton_clicked();

    void on_MorphologicalcomboBox_currentIndexChanged(int index);

    void on_smoothingComboBox_currentIndexChanged(int index);

    void on_EdgeDetectionComboBox_currentIndexChanged(int index);

    void on_HistogramcomboBox_currentIndexChanged(int index);





    void on_SaveButton_clicked();



    void on_UndoButton_clicked();

    void on_RedoButton_clicked();



    void on_DeleteButton_clicked();






    void on_ThreshButton_clicked();
    void onKernelSizeChanged(int value);
    void on_EdgespinBox1_valueChanged(int value);
    void on_EdgespinBox2_valueChanged(int value);





    void on_FFTButton_clicked();

    void on_FFTspinBox_valueChanged(int arg1);







    void on_borderComboBox_currentIndexChanged(int index);


    void on_PhaseButton_clicked();


    void on_SaveFButton_clicked();

    void on_ExecuteButton_clicked();

    void on_DeleteFButton_clicked();



    void on_RestoreImageButton_clicked();





    void on_captureImageButton_clicked();






    void on_EdgeDetectionComboBox_activated(int index);

    void on_smoothingComboBox_activated(int index);



    void on_helpButton_clicked();

private:

    cv::Mat loadedMat;
    bool isGrayscale;
  cv::Mat originalMat;
    // Declare the prototype for MatToQImage
    QImage MatToQImage(const cv::Mat &mat);
   // New helper function
   void loadImageInternal(const QString &file_name);
    void displayImage(const Mat& image);
    void saveProcessedImage();
      QVector<cv::Mat> imageHistory;
      QVector<cv::Mat> redoHistory;
      void applyFFTAndNormalization(int normalizationFactor);
      void displayOriginalImage();
       int currentKernelSize;
      int Threshold1;
      int Threshold2;
      int fftSize;
      int borderType;
       Mat filteredComplexImage;
      Mat createButterworthFilter(const Size& size, double cutoff, int order);
      void deleteSavedFunction(const QString& functionName);
      void updateSavedFunctionsFile();
      Mat  displayedImage;
      void executeFunction(const QString& funcName);
      Mat getStructuringElement();
      void displayHistogram(const Mat& image);
      void displayMagnitudeSpectrum(const Mat& filteredComplexImag);

      void dftShift(Mat& magI);


   void applyGaussianBlur();
   void applyMedianBlur();
   void applyMeanBlur();
   void applyBilateralFilter();
   void applyCannyEdgeDetection();
   void applySobelOperator();
   void applyScharrOperator();
   void applyErosion();
   void applyDilation();
   void applyOpening();
   void applyClosing();
   void applyHistogramEqualization();
   void applyHistogramStretching();
   void applyHighPass();
   void applyLowPass();
    void rotatePhase(double angle);


   void trackExecutedFunction(const QString& functionName);
    void estimateNoisePSD(const Mat& loadedMat, Mat& noisePSD);
    void applyWienerFilter(Mat& loadedMat, const Mat& noisePSD);
    Mat noisePSD;
   VideoCapture cap;
   Mat capturedFrame;





   void loadSavedFunctionsFromFile();
   QJsonObject serializeTrackedFunctions(const QStringList &trackedFunctions);
   QStringList deserializeTrackedFunctions(const QJsonObject &json);
   void setupDragAndDrop();
   void dragEnterEvent(QDragEnterEvent *event);
   void dropEvent(QDropEvent *event);
   bool isFreq = false;
   bool isFFTState = false;








private:

   Ui::MainWindow *ui;
    QList<QString> trackedFunctions;
    QMap<QString, std::function<void()>> savedFunctions;
    QStringList redoHistoryList;
QMap<QString, QStringList> savedFunctionNames;


    QTimer* timer;




};

#endif // MAINWINDOW_H
