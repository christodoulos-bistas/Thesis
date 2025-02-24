#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QImage>
#include <QVector>
#include <QQueue>
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<QDialog>
#include<QMouseEvent>
#include<QLabel>
#include<QEvent>
#include<QObject>
#include<QCheckBox>
#include<QWidget>
#include<cmath>
#include<math.h>
#include<QMap>
#include <QtCore/QDebug>
#include <QtCore/QSize>
#include<functional>
#include <QFile>
#include<QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <QCamera>
#include <QImageCapture>
#include<QTimer>
#include <QMimeData>
#include <QCameraDevice>
#include <QInputDialog>
#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <cmath>

using namespace cv;
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),isGrayscale(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Load saved filters from file
    loadSavedFunctionsFromFile();
    setupDragAndDrop();

    ui->EdgeDetectionComboBox->setCurrentIndex(4);

    ui->smoothingComboBox->setCurrentIndex(7);
    //Smoothing
    ui->label_freq->hide();
    ui->label_6->hide();
    ui->SmoothingspinBox->hide();
    ui->FrequencySpinBox->hide();
    ui->OrderspinBox->hide();
    ui->label_3->hide();

    // Edge Detection
    ui->XspinBox->hide();
    ui->YspinBox->hide();
    ui->label_5->hide();
    ui->label_2->hide();
     ui->label_4->hide();
    ui->EdgespinBox1->hide();
    ui->EdgespinBox2->hide();
    ui->KernelspinBox->hide();


}

MainWindow::~MainWindow()

{

    delete ui;

}



QImage MainWindow::MatToQImage(const Mat & mat) {
    if (mat.empty()) {
        qDebug() << "Error: Input matrix is empty.";
        return QImage();
    }

    switch (mat.type()) {
    case CV_8UC4: {
        // 4-channel ARGB image
        QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_ARGB32);
        return image.copy(); // Ensure the QImage owns its data
    }

    case CV_8UC3: {
        // 3-channel BGR image, needs RGB swapping
        QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
        return image.rgbSwapped().copy(); // Swap from BGR to RGB and ensure QImage owns its data
    }

    case CV_8UC1: {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        // Single channel grayscale image
        QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8);
#else
        static QVector<QRgb> sColorTable;
        if (sColorTable.isEmpty()) {
            sColorTable.resize(256);
            for (int i = 0; i < 256; ++i) {
                sColorTable[i] = qRgb(i, i, i);
            }
        }
        QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Indexed8);
        image.setColorTable(sColorTable);
#endif
        return image.copy(); // Ensure the QImage owns its data
    }

    case CV_32F: {
        if (mat.channels() != 1) {
            qDebug() << "Error: Only single-channel 32F matrices are supported for conversion to QImage.";
            return QImage();
        }

        Mat temp;
        mat.convertTo(temp, CV_32F); // Ensure we are working with a float matrix

        // Log the min/max values before normalization
        double minVal, maxVal;
        minMaxLoc(temp, &minVal, &maxVal);
        qDebug() << "Original Min/Max values in mat: " << minVal << "/" << maxVal;

        // Apply logarithmic scaling to enhance visibility of details
        temp += Scalar::all(1); // Avoid log(0) by adding 1 to all elements
        log(temp, temp);

        // Normalize to [0, 255] for display
        normalize(temp, temp, 0, 255, NORM_MINMAX);
        temp.convertTo(temp, CV_8U); // Convert to 8-bit for QImage compatibility

        // Log the min/max values after normalization
        minMaxLoc(temp, &minVal, &maxVal);
        qDebug() << "Normalized Min/Max values in temp: " << minVal << "/" << maxVal;

        // Create the QImage from the processed matrix
        QImage image(temp.data, temp.cols, temp.rows, static_cast<int>(temp.step), QImage::Format_Grayscale8);
        return image.copy(); // Ensure the QImage owns its data
    }

    default:
        qDebug() << "Error: Unsupported matrix type for conversion to QImage.";
        return QImage();
    }
}





void MainWindow::on_LoadButton_clicked()
{qDebug() << "on_LoadButton_clicked() function called";

    QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("All Image Files (*.png *.xpm *.jpg *.jpeg *.bmp *.gif *.tif *.tiff *.webp);;All Files (*.*)"));

    if (!file_name.isEmpty()) {
        // Set the originalMat if it's not already set
        if (originalMat.empty()) {
            // Always update originalMat with the loaded image
            originalMat = loadedMat.clone();
            // Debug output to check originalMat
            qDebug() << "originalMat updated. Size: " << originalMat.cols << "x" << originalMat.rows;

        }

        // Call loadImageInternal only if a file is selected
        loadImageInternal(file_name);

        // Display the original image
        displayOriginalImage();
    } else {
        qDebug() << "Error: No image selected.";
    }
}

void MainWindow::displayOriginalImage(){
    if(!originalMat.empty()){
        //convert the oringal mat to qimage for display
        QImage originalImg = MatToQImage(originalMat);
        //display original image
        int w = ui->label_original->width();
        int h = ui->label_original->height();
        ui->label_original->setPixmap(QPixmap::fromImage(originalImg).scaled(w,h,Qt::KeepAspectRatio));
    }
}

void MainWindow::displayImage(const Mat& image){
    QImage img = MatToQImage(image);
   int w = ui->label_pic->width();
   int h = ui-> label_pic -> height();
   ui->label_pic->setPixmap(QPixmap::fromImage(img).scaled(w,h,Qt::KeepAspectRatio));
   ui->dims->setText(QString("W: %1 H: %2").arg(loadedMat.cols).arg(loadedMat.rows));
     displayedImage = image.clone();

}

void MainWindow::on_GrayscaleButton_clicked(){

    qDebug()<< "Grayscale Button Clicked";

    if (!loadedMat.empty()){
        //check if the image is already in grayscale
        if (loadedMat.channels() == 3) {
            //clear redo history
            redoHistory.clear();
            redoHistory.append(loadedMat.clone());
            //convert to grayscale
            cvtColor(loadedMat,loadedMat,COLOR_BGR2GRAY);
             //update image history
            imageHistory.append(loadedMat.clone());
            trackExecutedFunction("Grayscale");
            //display image
           displayImage(loadedMat);
        }
    } else{
        qDebug() << "Error: No image loaded.";
        QMessageBox::warning(this, "No Image Loaded", " Please load an image before applying any image processing operations.");
        return;
    }
}

void MainWindow::on_ResetButton_clicked(){
    qDebug() << "reset() function called";
    if(!originalMat.empty()){

        loadedMat = originalMat.clone();
        displayImage(loadedMat);
        // Clear the frequency domain representation
        filteredComplexImage.release();
        isFreq = false;
    } else{
            qDebug()<< "Error: No image loaded.";

    }
        ui->functionListWidget->clear();
 }


 void MainWindow::loadImageInternal(const QString &file_name){
     qDebug() << "loadimage called with file:" << file_name;
         if ( file_name.isEmpty()){
         qDebug() << "Error: No file selected";
         return;
        }
         loadedMat = imread(file_name.toStdString());
        if(loadedMat.empty()){
             qDebug() << "Error: Unable to load the image at" << file_name;
            QMessageBox::critical (this, tr("Error"), tr("Unable to load the image at %1").arg(file_name));
            qDebug() << "image channels:" << loadedMat.channels();
            qDebug() << "image depth:" << loadedMat.depth();
            qDebug() << "Image type:" << loadedMat.type();
            return;
         }
        originalMat = loadedMat.clone();
        QImage img = MatToQImage(loadedMat);
        if(img.isNull()){
            qDebug() << " Error: Unable to convert Mat to QImage";
            return;
        }
       displayImage(loadedMat);
        imageHistory.clear();
        imageHistory.append(loadedMat.clone());
 }




void MainWindow::on_BlurButton_clicked(){
    if(!loadedMat.empty()){
        int smoothingMethodIndex = ui->smoothingComboBox->currentIndex();

        switch(smoothingMethodIndex){
        case 0 ://Gausian Blur
            applyGaussianBlur();
            trackExecutedFunction("Gaussian Blur");
            break;
        case 1://Mean Blur
            applyMeanBlur();
            trackExecutedFunction("Mean Blur");
            break;
        case 2://Median Blur
            applyMedianBlur();
            trackExecutedFunction("Median Blur");
            break;
        case 3://Bilateral Filter

            applyBilateralFilter();
            trackExecutedFunction("Bilateral Filter");
            break;
        case 4://HighPass
            if (isFreq == true){
                applyHighPass();
                trackExecutedFunction("High Pass");
                break;
            }else{
                qDebug() << "Error: Image is not in the frequency domain.";
                QMessageBox::warning(this, " Image is not in the frequency domain.", " Please click the FFTbutton to tranfer the image to the Frequency Domain");
                return;
            }
        case 5://LowPass
            if (isFreq == true) {
                applyLowPass();
                trackExecutedFunction("Low Pass");
                break;
            }else{
                    qDebug() << "Error: Image is not in the frequency domain.";
                   QMessageBox::warning(this, " Image is not in the frequency domain.", " Please click the FFTbutton to tranfer the image to the Frequency Domain");
                    return;
            }

        }
    }else{
        qDebug() << "Error: No image loaded.";
        QMessageBox::warning(this, "No Image Loaded", " Please load an image before applying any image processing operations.");
        return;
    }


}

void MainWindow::on_smoothingComboBox_activated(int index)

{
    switch(index){

    case 0 ://Gausian Blur
        ui->label_freq->show();
        ui->label_6->show();
        ui->SmoothingspinBox->show();
        ui->FrequencySpinBox->show();
        ui->OrderspinBox->hide();
        ui->label_3->hide();
        break;
    case 1://Mean Blur
        ui->label_freq->hide();
        ui->label_6->show();
        ui->SmoothingspinBox->show();
        ui->FrequencySpinBox->hide();
        ui->OrderspinBox->hide();
        ui->label_3->hide();
        break;
    case 2://Median Blur
        ui->label_freq->hide();
        ui->label_6->show();
        ui->SmoothingspinBox->show();
        ui->FrequencySpinBox->hide();
        ui->OrderspinBox->hide();
        ui->label_3->hide();
        break;
    case 3://Bilateral Filter
        ui->label_freq->hide();
        ui->label_6->show();
        ui->SmoothingspinBox->show();
        ui->FrequencySpinBox->hide();
        ui->OrderspinBox->hide();
        ui->label_3->hide();
        break;
    case 4://HighPass
        ui->label_freq->hide();
        ui->label_6->show();
        ui->SmoothingspinBox->show();
        ui->FrequencySpinBox->hide();
        ui->OrderspinBox->show();
        ui->label_3->hide();
        break;
    case 5://LowPass
        ui->label_freq->show();
        ui->label_6->show();
        ui->SmoothingspinBox->show();
        ui->FrequencySpinBox->show();
        ui->OrderspinBox->show();
        ui->label_3->show();
    default:
        break;
    }

}


void MainWindow::applyGaussianBlur()
{
     if (!loadedMat.empty()) {

        // Clear redo history
        redoHistory.clear();
         redoHistory.append(loadedMat.clone());
         int kernelSize = (currentKernelSize > 0 && currentKernelSize % 2 == 1) ? currentKernelSize : 5;
         double Frequency = ui->FrequencySpinBox->value();

        // Apply Gaussian blur to the loaded image
         GaussianBlur(loadedMat, loadedMat, Size(kernelSize, kernelSize), Frequency );

        displayImage(loadedMat);
        // Update the image history
        imageHistory.append(loadedMat.clone());

     } else {
         qDebug() << "Error: No image loaded.";
         QMessageBox::warning(this, "No Image Loaded", " Please load an image before applying any image processing operations.");
         return;
     }
}

void MainWindow::applyMeanBlur()
{
    if (!loadedMat.empty()) {

        // Clear redo history
        redoHistory.clear();
        redoHistory.append(loadedMat.clone());

        // Determine kernel size
        int kernelSize = (currentKernelSize > 0 && currentKernelSize % 2 == 1) ? currentKernelSize : 5;

        // Create the kernel for the mean blur
        Mat kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);

        // Apply the mean blur using filter2D
        filter2D(loadedMat, loadedMat, -1, kernel);
        displayImage(loadedMat);
        // Update the image history
        imageHistory.append(loadedMat.clone());

    } else {
        qDebug() << "Error: No image loaded.";
        QMessageBox::warning(this, "No Image Loaded", "Please load an image before applying any image processing operations.");
    }
}

void MainWindow::applyMedianBlur()
{
     if (!loadedMat.empty()) {

        // Clear redo history
        redoHistory.clear();
        redoHistory.append(loadedMat.clone());
        int kernelSize = (currentKernelSize > 0 && currentKernelSize % 2 == 1) ? currentKernelSize : 5;
        // Apply Median blur to the loaded image
        medianBlur(loadedMat, loadedMat,kernelSize); // You can adjust the kernel size as needed

        displayImage(loadedMat);
        // Update the image history
        imageHistory.append(loadedMat.clone());

     } else {
         qDebug() << "Error: No image loaded.";
         QMessageBox::warning(this, "No Image Loaded", " Please load an image before applying any image processing operations.");
         return;
     }
}

void MainWindow::applyBilateralFilter()
{
     if (!loadedMat.empty()) {
        Mat result;

        // Check the channel count of the loaded image
        if (loadedMat.channels() > 3) {
            // Convert to a three-channel image if it has more than three channels
            cvtColor(loadedMat, loadedMat, cv::COLOR_BGRA2BGR);
        }

        // Clear redo history
        redoHistory.clear();
         redoHistory.append(loadedMat.clone());
         int kernelSize = (currentKernelSize > 0 && currentKernelSize % 2 == 1) ? currentKernelSize : 5;


        // Apply Bilateral filter to the loaded image
        bilateralFilter(loadedMat, result, kernelSize, 75, 75);


        // Copy the result back to loadedMat
        loadedMat = result;


        displayImage(loadedMat);
        // Update the image history
        imageHistory.append(loadedMat.clone());


        // Check if the image is grayscale
        if (loadedMat.channels() == 1) {
            qDebug() << "Warning: Applying bilateral filter to grayscale image. Consider using other filters.";
        }
     } else {
         qDebug() << "Error: No image loaded.";
         QMessageBox::warning(this, "No Image Loaded", " Please load an image before applying any image processing operations.");
         return;
     }
}
void MainWindow::applyHighPass() {
    if (loadedMat.empty()) {
        qDebug() << "Error: No image loaded.";
        return;
    }

    if (!isFreq) {
        qDebug() << "Error: Image is not in the frequency domain.";
        return;
    }

    // Clear redo history
    redoHistory.clear();
    redoHistory.append(filteredComplexImage.clone());
    int order = ui->OrderspinBox->value();
    isFFTState = false;


    // Create a high-pass filter (as already implemented)
    Mat highPassFilter = Mat::ones(filteredComplexImage.size(), CV_32F);
    Mat lowPassFilter = createButterworthFilter(filteredComplexImage.size(), currentKernelSize, order);
    highPassFilter -= lowPassFilter;

    // Apply high-pass filter
    Mat planes[2];
    split(filteredComplexImage, planes);
    planes[0] = planes[0].mul(highPassFilter);
    planes[1] = planes[1].mul(highPassFilter);
    merge(planes, 2, filteredComplexImage);

    // Display the updated frequency domain image
    displayMagnitudeSpectrum(filteredComplexImage);

    // Update the image history to track the change
    imageHistory.append(filteredComplexImage.clone());
}

Mat MainWindow::createButterworthFilter(const Size& size, double cutoff, int order) {
    Mat butterworthFilter(size, CV_32F);

    Point center(size.width / 2, size.height / 2);
    double maxVal = 0.0;
    for (int i = 0; i < size.height; ++i) {
        for (int j = 0; j < size.width; ++j) {
            double radius = sqrt(pow(i - center.y, 2) + pow(j - center.x, 2));
            double value = 1.0 / (1.0 + pow(radius / cutoff, 2 * order));
            butterworthFilter.at<float>(i, j) = static_cast<float>(value);
            if(value > maxVal){
                maxVal = value;
            }
        }
    }
    butterworthFilter /= maxVal;
    return butterworthFilter;
}

void MainWindow::applyLowPass()
{

    if (loadedMat.empty()) {
        qDebug() << "Error: No image loaded.";
        return;
    }

    if (!isFreq) {
        qDebug() << "Error: Image is not in the frequency domain.";
        return;
    }

    // Clear redo history
    redoHistory.clear();
    redoHistory.append(filteredComplexImage.clone());
    int order = ui->OrderspinBox->value();
    isFFTState = false;

    // Create a low-pass Butterworth filter
    Mat lowPassFilter = createButterworthFilter(filteredComplexImage.size(), currentKernelSize, order);

    normalize(lowPassFilter, lowPassFilter, 0, 1, NORM_MINMAX);

    // Split the complex image into real and imaginary parts
    Mat planes[2];
    split(filteredComplexImage, planes);

    // Ensure both real and imaginary parts are of the same size and type
    if (planes[0].size() != planes[1].size()) {
        qDebug() << "Error: Real and imaginary parts are not the same size.";
        return;
    }
    if (planes[0].type() != planes[1].type()) {
        qDebug() << "Error: Real and imaginary parts are not the same type.";
        return;
    }

    // Convert both real and imaginary parts to CV_32F if necessary
    planes[0].convertTo(planes[0], CV_32F);
    planes[1].convertTo(planes[1], CV_32F);

    // Apply the low-pass filter to both the real and imaginary parts
    planes[0] = planes[0].mul(lowPassFilter);
    planes[1] = planes[1].mul(lowPassFilter);

    merge(planes, 2, filteredComplexImage);

    // Merge the planes back into the complex image
    merge(planes, 2, filteredComplexImage);

    // Display the updated frequency domain image
    displayMagnitudeSpectrum(filteredComplexImage);

    // Update the image history to track the change
    imageHistory.append(filteredComplexImage.clone());
}



void MainWindow::onKernelSizeChanged(int value)
{
    currentKernelSize = value;
}


void MainWindow::on_EdgeDetectionComboBox_activated(int index)
{

    switch (index) {
    case 0:  // Canny Edge Detection
        ui->XspinBox->hide();
        ui->YspinBox->hide();
        ui->label_5->hide();
        ui->label_2->show();
        ui->EdgespinBox1->show();
        ui->EdgespinBox2->show();
        ui->KernelspinBox->show();
        break;
    case 1:  // Sobel Operator
        ui->EdgespinBox1->hide();
        ui->EdgespinBox2->hide();
        ui->label_2->hide();
        ui->label_5->show();
        ui->XspinBox->show();
        ui->YspinBox->show();
        ui->KernelspinBox->show();
        break;
    case 2:  // Scharr Operator
        ui->EdgespinBox1->hide();
        ui->EdgespinBox2->hide();
        ui->label_2->hide();
        ui->label_5->show();
        ui->XspinBox->show();
        ui->YspinBox->show();
        ui->KernelspinBox->show();
        break;
    default:
        break;
    }
}


void MainWindow::on_EdgeButton_clicked(){
     qDebug() << " Edge Detection button clicked";

     if (!loadedMat.empty()) {
        // Check if the image is already in grayscale
        if (loadedMat.channels() == 1) {
            // Get the selected operation from the edgeDetectionComboBox
            int operationIndex = ui->EdgeDetectionComboBox->currentIndex();

        switch (operationIndex) {
            case 0:  // Canny Edge Detection
                applyCannyEdgeDetection();
                trackExecutedFunction("Canny Edge Detection");
                break;
            case 1:  // Sobel Operator
                applySobelOperator();
                trackExecutedFunction("Sobel Operator");

                break;
            case 2:  // Scharr Operator
                applyScharrOperator();
                trackExecutedFunction("Scharr Operator");

                break;
            default:
                break;
            }
        } else {
            QMessageBox::warning(this, "Invalid Image", "Edge Detection operations require a grayscale image. Please convert the image to grayscale before proceeding.");
            return;
        }
        ui->verticalLayout_3->update();
        // Display the final image
        displayImage(loadedMat);

    }else{
        qDebug() << "Error: No image loaded.";
        QMessageBox::warning(this, "No Image Loaded", " Please load an image before applying any image processing operations.");
        return;
    }
}



void MainWindow::applyCannyEdgeDetection(){
        if (!loadedMat.empty()) {
           Mat result;

        // Check if the image is grayscale
           if (loadedMat.channels() == 1) {

        // Clear redo history
        redoHistory.clear();
         redoHistory.append(loadedMat.clone());
        if (Threshold1 > 0 && Threshold2 > 0){
        // Apply Canny edge detection
        Canny(loadedMat, result, Threshold1, Threshold2);
        // Copy the result back to loadedMat
        loadedMat = result;

        // Update the image history
        imageHistory.append(loadedMat.clone());
        }else {
            qDebug() << "Error: Invalid Canny thresholds.";
            QMessageBox::warning(this, "Invalid Thresholds", "Canny thresholds must be positive values.");

        }

    }else {
        qDebug() << "Error: No image loaded.";
        }
    }
}


void MainWindow::applySobelOperator(){
        if (!loadedMat.empty()) {
          Mat result;

        // Check if the image is grayscale
        if (loadedMat.channels() == 1) {


        // Clear redo history
        redoHistory.clear();
         redoHistory.append(loadedMat.clone());


        int xOrder = ui->XspinBox->value();
        int yOrder = ui->YspinBox->value();
        int kernelSize = ui->KernelspinBox->value();


        // Apply Sobel operator
        Sobel(loadedMat, result, CV_8U, xOrder , yOrder,  kernelSize, 1, 0); // You can adjust the parameters as needed

        // Copy the result back to loadedMat
        loadedMat = result;


        // Update the image history
        imageHistory.append(loadedMat.clone());
        }
        }else {
        qDebug() << "Error: No image loaded.";
        }
}

void MainWindow::applyScharrOperator(){
        if (!loadedMat.empty()) {
        cv::Mat result;

        // Check if the image is grayscale
        if (loadedMat.channels() == 1) {

       // Clear redo history
        redoHistory.clear();
         redoHistory.append(loadedMat.clone());
        int xOrder = ui->XspinBox->value();
        int yOrder = ui->YspinBox->value();

        // Apply Scharr operator
        Scharr(loadedMat, result, CV_8U, xOrder, yOrder); // You can adjust the parameters as needed

        // Copy the result back to loadedMat
        loadedMat = result;



        // Update the image history
        imageHistory.append(loadedMat.clone());
        }
        }else {
        qDebug() << "Error: No image loaded.";
        }
}

void MainWindow::on_EdgespinBox1_valueChanged(int value)
{
    Threshold1 = value;
}

void MainWindow::on_EdgespinBox2_valueChanged(int value)
{
    Threshold2 = value;
}
void MainWindow::on_HistogramButton_clicked()
{        qDebug() << "Histogram Manipulation button clicked";


        if (!loadedMat.empty()) {
        // Check if the image is already in grayscale
        if (loadedMat.channels() == 1) {
        int operationIndex = ui->HistogramcomboBox->currentIndex();

            if (!filteredComplexImage.empty()) {
                qDebug() << "Warning: Attempting histogram operation while in the frequency domain. This is not allowed.";
                QMessageBox::warning(this, "Invalid Operation", "Histogram operations cannot be performed while the image is in the frequency domain. Please convert back to the spatial domain first.");
                return;
            }
            if (loadedMat.channels() != 1 || loadedMat.type() != CV_8UC1) {
                qDebug() << "Error: The image is not in the correct format for histogram operations.";
                QMessageBox::warning(this, "Invalid Image", "The histogram operations require an 8-bit grayscale image. Please ensure the image is correctly formatted.");
                return;
            }

        switch (operationIndex) {
        case 0:  // HistogramEqualization
                applyHistogramEqualization();
                trackExecutedFunction("Histogram Equalization");

                break;
        case 1:  // HistogramStretching
                applyHistogramStretching();
                trackExecutedFunction("Histogram Stretching");

                break;
        default:
                break;
        }

        displayImage(loadedMat);
        displayHistogram(loadedMat);
       }
     }else {
            qDebug() << "Error: No image loaded.";
            QMessageBox::warning(this, "No Image Loaded", " Please load an image before applying any image processing operations.");
            return;

        }


}

void MainWindow::displayHistogram(const Mat& image)
{
    // Calculate histogram
    Mat hist;
    int histSize = 256; // number of bins
    float range[] = {0, 256}; // the range of intensity values
    const float* histRange = {range};

    // Calculate the histogram for the grayscale image
    calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    // Normalize the histogram so it fits in the image
    int hist_w = 512; int hist_h = 400;
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255));  // Create white image
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX);

    // Draw the intensity line for histogram
    int bin_w = cvRound((double)hist_w / histSize);
    for (int i = 1; i < histSize; i++) {
        line(histImage,
             Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(hist.at<float>(i))),
             Scalar(0), 2, 8, 0);  // Black line for the histogram
    }
    namedWindow("Histogram", WINDOW_GUI_NORMAL + WINDOW_AUTOSIZE);
    // Show the histogram using imshow
    imshow("Histogram", histImage);
    waitKey(0);
}

void MainWindow::applyHistogramEqualization()
{
        if (!loadedMat.empty() && loadedMat.channels() == 1) {
        // Clear redo history
        redoHistory.clear();
         redoHistory.append(loadedMat.clone());

        Mat equalizedMat;
         loadedMat.copyTo(equalizedMat);
        // Apply histogram equalization
        equalizeHist(equalizedMat, equalizedMat);
        loadedMat = equalizedMat;
       // Update the image history
        imageHistory.append(loadedMat.clone());


        }
        else {
        qDebug() << "Error: No image loaded.";
            QMessageBox::warning(this, "Invalid Image", "Histogram Equalization requires a grayscale image. Please convert the image to grayscale before proceeding.");
            return;
        }
    }

void MainWindow::applyHistogramStretching()
{
        if (!loadedMat.empty() && loadedMat.channels() == 1) {

        // Clear redo history
        redoHistory.clear();
         redoHistory.append(loadedMat.clone());

        Mat tempMAT;
         loadedMat.convertTo(tempMAT,CV_32F);

        double minVal, maxVal;
        minMaxLoc(tempMAT, &minVal, &maxVal);

        if(maxVal != minVal){
        // Apply histogram stretching
        tempMAT = 255 * (tempMAT - minVal) / (maxVal - minVal);
        }else{
            qDebug() << "Warning: Image has no contrast to stretch.";
            QMessageBox::warning(this, "Warning", "The image has no contrast to stretch.");
            return;
        }

        tempMAT.convertTo(tempMAT, CV_8UC1);
        loadedMat = tempMAT.clone();
        // Update the image history
        imageHistory.append(loadedMat.clone());



        } else {
          qDebug() << "Error: No image loaded.";
            QMessageBox::warning(this, "Invalid Image", "Histogram Stretching requires a grayscale image. Please convert the image to grayscale before proceeding.");
            return;
        }
}





void MainWindow::on_RotateButton_clicked()
// Rotate the loaded image clockwise
{
        qDebug() << "Rotate Clockwise button clicked";

        if (!loadedMat.empty()) {
        transpose(loadedMat, loadedMat);
        flip(loadedMat, loadedMat, 1);


        displayImage(loadedMat);


        // Update the image history
        imageHistory.append(loadedMat.clone());



        } else {
        qDebug() << "Error: No image loaded.";
        }
}


void MainWindow::on_FlipHorizontalButton_clicked()
        // Flip the loaded image horizontally
{
        qDebug() << "Flip Horizontal button clicked";

        if (!loadedMat.empty()) {
        flip(loadedMat, loadedMat, 1);


        displayImage(loadedMat);


        // Update the image history
        imageHistory.append(loadedMat.clone());


        } else {
        qDebug() << "Error: No image loaded.";
        }
}


void MainWindow::on_FlipVerticalButton_clicked()
// Flip the loaded image vertically
{
        qDebug() << "Flip Vertical button clicked";

        if (!loadedMat.empty()) {
        flip(loadedMat, loadedMat, 0);

        displayImage(loadedMat);



        // Update the image history
        imageHistory.append(loadedMat.clone());


        } else {
        qDebug() << "Error: No image loaded.";
        }
}


Mat MainWindow::getStructuringElement(){

    int shapeIndex = ui->MorphcomboBox->currentIndex();
    int shape;
    switch (shapeIndex) {
    case 0: shape = MORPH_RECT; break;
    case 1: shape = MORPH_ELLIPSE; break;
    case 2: shape = MORPH_CROSS; break;
    default: shape = MORPH_RECT;
    }

    int size = ui->spinBox->value();
    return ::getStructuringElement(shape,Size(size,size));
}


void MainWindow::applyErosion ()
{
        if (!loadedMat.empty() && loadedMat.channels() == 1) {

        // Clear redo history
        redoHistory.clear();
         redoHistory.append(loadedMat.clone());

        Mat kernel = getStructuringElement();

        // Apply erosion to the loaded image
       erode(loadedMat, loadedMat, kernel);
        // Update the image history
        imageHistory.append(loadedMat.clone());

        } else {
        qDebug() << "Error: No image loaded.";
            QMessageBox::warning(this, "Invalid Image", "The Erosion operation requires a grayscale image. Please convert the image to grayscale before proceeding.");
            return;
        }
}


void MainWindow::applyDilation()
{

        if (!loadedMat.empty() && loadedMat.channels() == 1) {

        // Clear redo history
        redoHistory.clear();
        redoHistory.append(loadedMat.clone());

        Mat kernel = getStructuringElement();

        // Apply dilation to the loaded image
        dilate(loadedMat, loadedMat, kernel);
        // Update the image history
        imageHistory.append(loadedMat.clone());
        } else {
        qDebug() << "Error: No image loaded.";
            QMessageBox::warning(this, "Invalid Image", "The Dilation operation requires a grayscale image. Please convert the image to grayscale before proceeding.");
            return;
        }

}

void  MainWindow::applyOpening()
{
        if (!loadedMat.empty() && loadedMat.channels() == 1) {

        // Clear redo history
        redoHistory.clear();
         redoHistory.append(loadedMat.clone());

         Mat kernel = getStructuringElement();
        // Apply erosion followed by dilation
        erode(loadedMat, loadedMat,  kernel);
        dilate(loadedMat, loadedMat, kernel);

        // Update the image history
        imageHistory.append(loadedMat.clone());

        } else {
        qDebug() << "Error: No image loaded.";
            QMessageBox::warning(this, "Invalid Image", "The Opening operation requires a grayscale image. Please convert the image to grayscale before proceeding.");
            return;
        }
}

void MainWindow::applyClosing()
{
        if (!loadedMat.empty() && loadedMat.channels() == 1) {

        // Clear redo history
        redoHistory.clear();
         redoHistory.append(loadedMat.clone());

        Mat kernel = getStructuringElement();

        // Apply dilation followed by erosion
        dilate(loadedMat, loadedMat, kernel);
        erode(loadedMat, loadedMat,  kernel);

        // Update the image history
        imageHistory.append(loadedMat.clone());
        } else {
        qDebug() << "Error: No image loaded.";
            QMessageBox::warning(this, "Invalid Image", "The Closing operation requires a grayscale image. Please convert the image to grayscale before proceeding.");
            return;
        }
}


void MainWindow::on_MorphologicalButton_clicked()
{if (!loadedMat.empty()) {
        int operationIndex = ui->MorphologicalcomboBox->currentIndex();

        switch (operationIndex) {
        case 0:  // Erosion
        applyErosion();
        trackExecutedFunction("Erosion");
        break;
        case 1:  // Dilation
        applyDilation();
        trackExecutedFunction("Dilation");
        break;
        case 2:  // Opening
        applyOpening();
        trackExecutedFunction("Opening");
        break;
        case 3:  // Closing
        applyClosing();
        trackExecutedFunction("Closing");
        break;
        default:
        break;
        }

        } else {
        qDebug() << "Error: No image loaded.";
        }
       displayImage(loadedMat);

}


void MainWindow::on_MorphologicalcomboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
}


void MainWindow::on_smoothingComboBox_currentIndexChanged(int index)
{
     Q_UNUSED(index);
}


void MainWindow::on_EdgeDetectionComboBox_currentIndexChanged(int index)
{
     Q_UNUSED(index);
}


void MainWindow::on_HistogramcomboBox_currentIndexChanged(int index)
{
     Q_UNUSED(index);
}





void MainWindow::on_SaveButton_clicked()
{
    if (!displayedImage.empty()) {
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("Images (*.png *.xpm *.jpg)"));

        if (!file_name.isEmpty()) {
            // Save the image using OpenCV's imwrite function
            std::vector<int> compression_params; // Compression parameters for JPEG

            // Optionally set compression parameters for JPEG format (if needed)
            compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
            compression_params.push_back(90); // Example: quality level 90

            // Save the image without resizing or altering its dimensions
            cv::imwrite(file_name.toStdString(), displayedImage, compression_params);

            qDebug() << "Image saved to: " << file_name;
        }
    } else {
        qDebug() << "Error: No image loaded.";
    }
}






void MainWindow::on_UndoButton_clicked()
{
    if (imageHistory.size() > 1) {


        // Save the current state for redo
        redoHistory.append(isFreq ? filteredComplexImage.clone() : loadedMat.clone());

        // Remove the last state from history
        imageHistory.removeLast(); // Remove the most recent state
        if (isFreq && isFFTState) {
            QMessageBox::warning(this, "Undo Error", "You can't undo right after pressing the FFT button. Please press the Restore Button to return to the spatial domain first.");
            return;
        }

        // Load the previous state
        if (isFreq == true) {
            // If currently in frequency domain, load the last complex image
            filteredComplexImage = imageHistory.last().clone();
            displayMagnitudeSpectrum(filteredComplexImage); // Display the frequency domain image


        } else {
            // If in spatial domain, load the last spatial image
            loadedMat = imageHistory.last().clone();
            displayImage(loadedMat); // Display the spatial domain image
        }

        if (ui->functionListWidget->count() > 0) {
            redoHistoryList.append(ui->functionListWidget->takeItem(ui->functionListWidget->count() - 1)->text());
        } else {
            qDebug() << "Error: Cannot undo further.";
        }
    } else {
        qDebug() << "Error: Cannot undo further.";
    }
}

void MainWindow::on_RedoButton_clicked()
{
    if (!redoHistory.isEmpty()) {
        // Load the last state from redo history
        Mat lastState = redoHistory.takeLast();

        // Check if the last state is in the frequency domain or spatial domain
        if (isFreq) {
            // It is in the frequency domain
            filteredComplexImage = lastState;
            displayMagnitudeSpectrum(filteredComplexImage); // Display the frequency domain output

        } else {
            // It is in the spatial domain
            loadedMat = lastState;
            displayImage(loadedMat); // Display the spatial domain output
        }

        // Update the history to include the restored image
        imageHistory.append(lastState.clone()); // Add back to the history

        if (!redoHistoryList.isEmpty()) {
            ui->functionListWidget->addItem(redoHistoryList.takeLast());
        } else {
            qDebug() << "Error: Cannot redo further.";
        }
    } else {
        qDebug() << "Error: Cannot redo further.";
    }
}



void MainWindow::on_DeleteButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Delete Image","Are you sure you want to delete the image?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
    // Clear the loaded image
    loadedMat.release();
    // Clear the displayed image
    ui->label_pic->clear();
    ui->label_original->clear();
    // Update the label with image dimensions
    ui->dims->setText(QString("W: %1  H: %2").arg(0).arg(0));
    // Reset originalMat
    originalMat.release();
    qDebug() << "Image deleted.";
    // Clear the function list widget for the next set of tracked functions
    // Clear the frequency domain representation
    filteredComplexImage.release();
    isFreq = false;

    ui->functionListWidget->clear();
    }else{
        qDebug()<<"Deletion cancelled.";
    }
}




void MainWindow::on_ThreshButton_clicked(){
          // Update a label or other UI element to display the current threshold value
    int thresholdValue = ui->ThreshspinBox->value();
    qDebug() << "Threshold value:" << thresholdValue;

    // Apply binary thresholding
    if (!loadedMat.empty() && loadedMat.channels() == 1) {
        qDebug() << "Grayscale image loaded successfully.";

        // Clear redo history
        redoHistory.clear();
        redoHistory.append(loadedMat.clone());

        Mat thresholdedMat;
        threshold(loadedMat, thresholdedMat, thresholdValue, 255, THRESH_BINARY);
        qDebug() << "Thresholding applied.";
        loadedMat = thresholdedMat;
        displayImage(loadedMat);
        // Update the image history
        imageHistory.append(loadedMat.clone());
        trackExecutedFunction("Binary");
        qDebug() << "Function tracked.";

    } else {
        qDebug() << "Error: No grayscale image loaded.";
        QMessageBox::warning(this, "Invalid Image", "To transform the image to Binary the image requires to be a grayscale image. Please convert the image to grayscale before proceeding.");
    }
}


void MainWindow::on_FFTButton_clicked() {
    if (loadedMat.empty()) {
        qDebug() << "Error: No image loaded.";
        QMessageBox::warning(this, "No Image Loaded", "Please load an image before applying any image processing operations.");
        return;
    }

    if (loadedMat.channels() != 1) {
        qDebug() << "Error: The image is not in grayscale.";
        QMessageBox::warning(this, "Invalid Image", "The FFT operation requires a grayscale image. Please convert the image to grayscale before proceeding.");
        return;
    }

    if (isFreq) {
        qDebug() << "Error: The image is already in the frequency domain.";
        QMessageBox::warning(this, "Frequency Domain", "The image is already in the frequency domain. Please convert it back to the spatial domain before applying FFT again.");
        return;
    }

    redoHistory.clear();

    // Save the current state for undo
    imageHistory.append(loadedMat.clone());

    // Convert the image to floating point type
    Mat floatImage;
    loadedMat.convertTo(floatImage, CV_32F);

    if (floatImage.empty()) {
        qDebug() << "Error: Failed to convert image to float.";
        QMessageBox::warning(this, "Conversion Error", "Failed to convert the image to float.");
        return;
    }

    // Validate the borderType
    if (borderType != cv::BORDER_CONSTANT &&
        borderType != cv::BORDER_REFLECT &&
        borderType != cv::BORDER_REFLECT_101 &&
        borderType != cv::BORDER_REPLICATE &&
        borderType != cv::BORDER_WRAP) {
        qDebug() << "Warning: Unsupported border type detected. Defaulting to BORDER_REFLECT.";
        borderType = cv::BORDER_REFLECT;
    }

    // Expand image to optimal size
    Mat padded;
    int m = cv::getOptimalDFTSize(floatImage.rows);
    int n = cv::getOptimalDFTSize(floatImage.cols);
    copyMakeBorder(floatImage, padded, 0, m - floatImage.rows, 0, n - floatImage.cols, borderType, cv::Scalar::all(0));

    if (padded.empty()) {
        qDebug() << "Error: Padded image creation failed.";
        QMessageBox::warning(this, "Padded Image Error", "Failed to create a padded image for FFT.");
        return;
    }

    qDebug() << "Padded image dimensions: " << padded.rows << "x" << padded.cols;

    // Create complex image
    Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
    Mat complexImage;
    merge(planes, 2, complexImage);

    try {
        // Perform FFT
        dft(complexImage, complexImage, DFT_COMPLEX_OUTPUT);
    } catch (Exception &e) {
        qDebug() << "FFT failed with exception:" << e.what();
        QMessageBox::critical(this, "FFT Error", "Failed to perform FFT on the image.");
        return;
    }


    // Store the complex image for further processing
    filteredComplexImage = complexImage.clone();
    isFreq = true;
    isFFTState = true;


    // Display the magnitude spectrum
    displayMagnitudeSpectrum(filteredComplexImage);



    // Update the image history
    imageHistory.append(filteredComplexImage.clone());


    // Track the executed function
    trackExecutedFunction("FFT");

}
void MainWindow::on_FFTspinBox_valueChanged(int value) {
    if (value <= 0) {
        qDebug() << "Error: Invalid FFT size value.";
        QMessageBox::warning(this, "Invalid FFT Size", "FFT size must be a positive integer.");
        return;
    }
    fftSize = value;
}

void MainWindow::on_borderComboBox_currentIndexChanged(int index) {
    switch (index) {
    case 0: borderType = BORDER_CONSTANT; break;
    case 1: borderType = BORDER_REPLICATE; break;
    case 2: borderType = BORDER_REFLECT; break;
    case 3: borderType = BORDER_TRANSPARENT; break;
    case 4: borderType = BORDER_WRAP; break;
    default:
        qDebug() << "Warning: Unexpected index in borderComboBox. Defaulting to BORDER_CONSTANT.";
        borderType = BORDER_CONSTANT;
        break;
    }
}

void MainWindow::rotatePhase(double angle) {
    if (filteredComplexImage.empty()) {
        qDebug() << "Error: No complex image data available.";
        QMessageBox::warning(this, "No Complex Image Data", "Please perform FFT or other frequency domain operations before attempting to rotate the phase.");
        return;
    }

    if (angle < 0 || angle >= 360) {
        qDebug() << "Error: Invalid angle value.";
        QMessageBox::warning(this, "Invalid Angle", "The rotation angle must be between 0 and 360 degrees.");
        return;
    }

    // Ensure filteredComplexImage has 2 channels
    if (filteredComplexImage.channels() != 2) {
        qDebug() << "Error: Complex image data must have 2 channels.";
        return;
    }


    // Clear redo history and save the current state for undo functionality
    redoHistory.clear();
    redoHistory.append(filteredComplexImage.clone());

    isFFTState = false;

    // Split the complex image into real and imaginary parts
    Mat planes[2];
    split(filteredComplexImage, planes);

    // Calculate magnitude and phase
    Mat mag, phase;
    cartToPolar(planes[0], planes[1], mag, phase);

    // Convert angle from degrees to radians
    double radians = angle * CV_PI / 180.0;

    // Rotate the phase spectrum by the specified angle
    phase += radians;
    // Apply fmod element-wise to keep phase within [0, 2 * CV_PI]
        for (int i = 0; i < phase.rows; ++i) {
        for (int j = 0; j < phase.cols; ++j) {
            phase.at<float>(i, j) = fmod(phase.at<float>(i, j) + 2 * CV_PI, 2 * CV_PI);
        }
    }

    // Reconstruct the frequency domain image with the rotated phase
    Mat outputReal, outputImaginary;
    polarToCart(mag, phase, outputReal, outputImaginary);

    // Merge the real and imaginary parts back into a complex image
    Mat mergedPlanes[] = { outputReal, outputImaginary };
    merge(mergedPlanes, 2, filteredComplexImage);

    // Optionally, display the updated magnitude spectrum
    displayMagnitudeSpectrum(filteredComplexImage);

    // Update the image history
    imageHistory.append(filteredComplexImage.clone());

}

void MainWindow::on_PhaseButton_clicked() {
    if (!isFreq) {
        qDebug() << "Error: Image is not in the frequency domain.";
        QMessageBox::warning(this, "Invalid Operation", "The phase rotation function can only be applied to images in the frequency domain. Please convert the image to the frequency domain before proceeding.");
        return;
    }

    double angle = ui->PhasespinBox->value(); // Get the rotation angle from the spin box
    rotatePhase(angle);

    // Display the complex image (after phase rotation)
    if (filteredComplexImage.empty()) {
        qDebug() << "Error: Filtered complex image is empty after phase rotation.";
        return;
    }

    // Track the executed function
    trackExecutedFunction("Phase");

}

void MainWindow::on_RestoreImageButton_clicked() {
    if (filteredComplexImage.empty()) {
        qDebug() << "Error: No complex image data available.";
        QMessageBox::warning(this, "No Complex Image Data", "Please perform FFT or other frequency domain operations before attempting to restore the image.");
        return;
    }

    if (!isFreq) {
        qDebug() << "Error: Image is not in the frequency domain.";
        QMessageBox::warning(this, "Invalid Operation", "The restore operation can only be applied to images in the frequency domain.");
        return;
    }

    // Save the current state to redo history
    redoHistory.clear();
    redoHistory.append(filteredComplexImage.clone());

    // Perform the Inverse Discrete Fourier Transform (IDFT)
    Mat restoredImage;
    idft(filteredComplexImage, restoredImage, DFT_REAL_OUTPUT | DFT_SCALE);

    if (restoredImage.type() == CV_32F) {
        // Find min and max values for normalization
        double minVal, maxVal;
        minMaxLoc(restoredImage, &minVal, &maxVal);
        qDebug() << "Min Value: " << minVal << " Max Value: " << maxVal; // Debugging range

        // Normalize based on the actual range of the image
        if (maxVal - minVal > 0) {  // Avoid division by zero
            normalize(restoredImage, restoredImage, 0, 255, NORM_MINMAX);
        }

        // Convert to 8-bit depth for grayscale
        restoredImage.convertTo(restoredImage, CV_8UC1);
    } else if (restoredImage.type() == CV_8UC1) {
        // If already CV_8UC1, check if normalization is needed
        double minVal, maxVal;
        minMaxLoc(restoredImage, &minVal, &maxVal);
        qDebug() << "Min Value: " << minVal << " Max Value: " << maxVal; // Debugging range
        if (minVal < 0 || maxVal > 255) {
            normalize(restoredImage, restoredImage, 0, 255, NORM_MINMAX);
        }
    }

    // Convert to 8-bit depth image (either grayscale or RGB based on original)
    if (loadedMat.channels() == 3) {
        restoredImage.convertTo(restoredImage, CV_8UC3);  // RGB image
    } else {
        restoredImage.convertTo(restoredImage, CV_8UC1);  // Grayscale image
    }

    // Update loadedMat with the restored image and display it
    loadedMat = restoredImage.clone();
    displayImage(loadedMat);

    // Clear the frequency domain representation
    filteredComplexImage.release();
    isFreq = false;

    // Update the image history
    imageHistory.append(loadedMat.clone());

    // Track the restoration operation
    trackExecutedFunction("Restore Image");
}

void MainWindow::displayMagnitudeSpectrum(const Mat& filteredComplexImage) {
    if (filteredComplexImage.empty()) {
        qDebug() << "Error: No complex image data available for display.";
        return;
    }

    // Split the complex image into real and imaginary parts
    Mat planes[2];
    split(filteredComplexImage, planes);

    // Compute the magnitude
    Mat magnitudeImage;
    magnitude(planes[0], planes[1], magnitudeImage);

    // Logarithmic scaling and normalization for better visibility
    magnitudeImage += Scalar::all(1);  // Avoid log(0)
    log(magnitudeImage, magnitudeImage);
    normalize(magnitudeImage, magnitudeImage, 0, 255, NORM_MINMAX);
    magnitudeImage.convertTo(magnitudeImage, CV_8UC1);  // Convert to 8-bit grayscale

    // Display the magnitude spectrum
    displayImage(magnitudeImage);
}


void MainWindow::trackExecutedFunction(const QString& functionName) {
    // Add the function name to the list widget
    ui->functionListWidget->addItem(functionName);
}
void MainWindow::on_SaveFButton_clicked(){
    QString functionName = ui->NamelineEdit->text();
    QStringList trackedFunctions;
    for (int i = 0; i < ui->functionListWidget->count(); ++i) {
        trackedFunctions.append(ui->functionListWidget->item(i)->text());
    }
    savedFunctions[functionName] = [trackedFunctions, this]() {
        for (const QString& funcName : trackedFunctions) {
            if (funcName == "Grayscale") {
                on_GrayscaleButton_clicked();
            } else if (funcName == "Binary") {
                on_ThreshButton_clicked();
            } else if (funcName == "Gaussian Blur" ||  funcName =="Mean Blur"||funcName == "MedianBlur" || funcName == "BilateralFilter" || funcName == "High Pass"
                       || funcName == "Low Pass") {
                on_BlurButton_clicked();
            } else if (funcName == "Canny Edge Detection" || funcName == "Sobel Operator" || funcName == "Scharr Operator") {
                on_EdgeButton_clicked();
            } else if (funcName == "Histogram Equalization" || funcName == "Histogram Stretching") {
                on_HistogramButton_clicked();
            } else if (funcName == "Erosion" || funcName == "Dilation" || funcName == "Opening" || funcName == "Closing") {
                on_MorphologicalButton_clicked();
            } else if (funcName == "FFT") {
                on_FFTButton_clicked();
            } else if (funcName == "Phase") {
                on_PhaseButton_clicked();
            } else if (funcName == "Restore Image") {
                on_RestoreImageButton_clicked();
            }
        }
    };
    // Store the tracked functions in the new map
    savedFunctionNames[functionName] = trackedFunctions;
    ui->functionListWidget->clear();
    ui->SavecomboBox->addItem(functionName);
    updateSavedFunctionsFile();
}




void MainWindow::on_ExecuteButton_clicked(){
    QString functionName = ui->SavecomboBox->currentText();

    if (!savedFunctions.isEmpty()) {
        if (savedFunctions.contains(functionName)) {
            savedFunctions[functionName](); // Call the saved function
            ui->functionListWidget->addItem("Executed: " + functionName);
        } else {

            QMessageBox::critical(this, "Error", "Selected function not found.");
        }
    } else {

        QMessageBox::warning(this, "Warning", "No saved functions found.");
    }
}

void MainWindow::deleteSavedFunction(const QString &functionName){

    int index = ui->SavecomboBox->findText(functionName);
    if (index != -1) {
        ui->SavecomboBox->removeItem(index);
    }
    savedFunctions.remove(functionName);
    savedFunctionNames.remove(functionName);

    QFile file("saved_functions.json");
    if (!file.exists()) {
        qWarning() << "JSON file does not exist:";
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Couldn't open the JSON file for reading:";
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc(QJsonDocument::fromJson(fileData));
    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "Invalid JSON data in file:";
        return;
    }

    QJsonObject jsonObj = doc.object();

    if (jsonObj.contains(functionName)) {
        jsonObj.remove(functionName);
    } else {
        qWarning() << "Function not found in JSON file.";
        return;
    }

    QJsonDocument saveDoc(jsonObj);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Couldn't open the JSON file for writing:";
        return;
    }
    file.write(saveDoc.toJson());
    file.close();

    updateSavedFunctionsFile();
}




void MainWindow::updateSavedFunctionsFile(){
    QFile file("saved_functions.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QJsonObject json;
        for (const QString& functionName : savedFunctionNames.keys()) {
            QStringList trackedFunctions = savedFunctionNames[functionName];
            QJsonArray functionsArray;
            for (const QString &funcName : trackedFunctions) {
                functionsArray.append(funcName);
            }
            QJsonObject functionJson;
            functionJson["functions"] = functionsArray;
            json[functionName] = functionJson;
        }
        QJsonDocument doc(json);
        file.write(doc.toJson());
        file.close();
    } else {
        qDebug() << "Error: Failed to update saved functions file.";
    }
}



void MainWindow::loadSavedFunctionsFromFile() {
    QFile file("saved_functions.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject json = doc.object();

        for (const QString& functionName : json.keys()) {
            QJsonObject functionJson = json[functionName].toObject();
            QJsonArray functionsArray = functionJson["functions"].toArray();
            QStringList trackedFunctions;
            for (const QJsonValue &value : functionsArray) {
                trackedFunctions.append(value.toString());
            }

            savedFunctions[functionName] = [trackedFunctions, this]() {
                for (const QString& funcName : trackedFunctions) {
                    if (funcName == "Grayscale") {
                        on_GrayscaleButton_clicked();
                    } else if (funcName == "Binary") {
                        on_ThreshButton_clicked();
                    } else if (funcName == "Gaussian Blur" || funcName =="Mean Blur"|| funcName == "MedianBlur" || funcName == "BilateralFilter" || funcName == "High Pass"
                               || funcName == "Low Pass") {
                        on_BlurButton_clicked();
                    } else if (funcName == "Canny Edge Detection" || funcName == "Sobel Operator" || funcName == "Scharr Operator") {
                        on_EdgeButton_clicked();
                    } else if (funcName == "Histogram Equalization" || funcName == "Histogram Stretching") {
                        on_HistogramButton_clicked();
                    } else if (funcName == "Erosion" || funcName == "Dilation" || funcName == "Opening" || funcName == "Closing") {
                        on_MorphologicalButton_clicked();
                    } else if (funcName == "FFT") {
                        on_FFTButton_clicked();
                    } else if (funcName == "Phase") {
                        on_PhaseButton_clicked();
                    } else if (funcName == "Restore Image") {
                        on_RestoreImageButton_clicked();
                    }
                }
            };

            // Populate the new map with the loaded data
            savedFunctionNames[functionName] = trackedFunctions;

            ui->SavecomboBox->addItem(functionName);
        }
        file.close();
    } else {
        qDebug() << "Error: Failed to load saved functions file.";
    }
}



void MainWindow::on_DeleteFButton_clicked(){
    QString functionName = ui->SavecomboBox->currentText();
    if (!functionName.isEmpty()) {
        // Confirm deletion with the user
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete Function",
                                      "Are you sure you want to delete the function?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // Delete the function
            deleteSavedFunction(functionName);
        }
    } else {
        qDebug() << "Error: No function selected for deletion.";
    }

}


QJsonObject serializeTrackedFunctions(const QStringList &trackedFunctions) {
    QJsonObject json;
    QJsonArray functionsArray;
    for (const QString &funcName : trackedFunctions) {
        functionsArray.append(funcName);
    }
    json["functions"] = functionsArray;
    return json;
}

// Function to deserialize the tracked functions
QStringList deserializeTrackedFunctions(const QJsonObject &json) {
    QStringList trackedFunctions;
    QJsonArray functionsArray = json["functions"].toArray();
    for (const QJsonValue &value : functionsArray) {
        trackedFunctions.append(value.toString());
    }
    return trackedFunctions;
}




void MainWindow::on_captureImageButton_clicked()
{
    vector<int> availableCameras;
    for (int i = 0; i < 10; ++i) {
        VideoCapture tempCamera(i);
        if (tempCamera.isOpened()) {
            availableCameras.push_back(i);
            tempCamera.release();
        }
    }

    if (availableCameras.empty()) {
        qDebug() << "No cameras found.";
        return;
    }
    bool ok;
    QStringList cameraList;
    for (int camIndex : availableCameras) {
        cameraList << QString("Camera %1").arg(camIndex);
    }
    QString selectedCamera = QInputDialog::getItem(this, "Select Camera", "Camera:", cameraList, 0, false, &ok);

    if (!ok) {
        return; // User canceled the dialog
    }

    int selectedCameraIndex = availableCameras[cameraList.indexOf(selectedCamera)];

    //  pen the selected camera
    VideoCapture inputVideo;
    inputVideo.open(selectedCameraIndex);

    if (!inputVideo.isOpened()) {
        qDebug() << "Failed to open the selected camera.";
        return;
    }
    namedWindow("Camera", WINDOW_GUI_NORMAL + WINDOW_AUTOSIZE);
    Mat frame;
    while (inputVideo.grab()) {
        inputVideo.retrieve(frame);
        QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        QPixmap pixmap = QPixmap::fromImage(qimg.rgbSwapped());
         imshow("Camera", frame);
        ui->label_pic->setPixmap(pixmap);
        ui->label_original->setPixmap(pixmap);
        char key = (char) waitKey(10);
        if (key == 27){// it closes with Esc
            destroyWindow("Camera");
            ui->label_pic->clear();
            ui->label_original->clear();
            break;
        }
        else if (getWindowProperty("Camera",WND_PROP_VISIBLE) < 1){
            ui->label_pic->clear();
            ui->label_original->clear();
            break;
        }
        else if (key == 32) // Capture with spacebar
        {
            originalMat = frame.clone();
            displayOriginalImage();
            displayImage(frame);
            QString fileName = "captured_image.jpg";
            if (imwrite(fileName.toStdString(), frame)) {
                qDebug() << "Image successfully saved to" << fileName;
                loadImageInternal(fileName);
                  destroyWindow("Camera");
                break;
            } else {
                qDebug() << "Failed to save image to" << fileName;
            }
        }


    }

    inputVideo.release();
}


void MainWindow::setupDragAndDrop() {
        setAcceptDrops(true);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}



void MainWindow::dropEvent(QDropEvent *event) {
    foreach (const QUrl &url, event->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        loadImageInternal(fileName);
        if (!fileName.isEmpty()) {
            Mat loadedMat = imread(fileName.toStdString());
            if (!loadedMat.empty()) {    
                originalMat = loadedMat.clone();
                displayOriginalImage();
                displayImage(loadedMat);

            } else {
                qDebug() << "Failed to load image:" << fileName;
            }
        }
    }
}




void MainWindow::on_helpButton_clicked()
    {

        QString helpText =
            "<h1>Welcome! This is your guide to the application!</h1>"
            "<h2>Overview of Features:</h2>"
            "<ul>"
            "<li><b>Load Image:</b><br>"
            "You have three ways to load an image:<br>"
            "<ol>"
            "<li>The traditional way by clicking the Load Image Button.</li>"
            "<li>Drag and Drop an image for quick loading.</li>"
            "<li>Capture an image from your webcam by clicking the Capture Image Button. You can press the spacebar to capture an image. Press the escape button or click the x to close the camera.</li>"
            "</ol>"
            "</li>"
            "<li><b>Grayscale:</b><br>"
            "Transforms the image to grayscale.</li>"
            "<li><b>Binary:</b><br>"
            "Transforms the image to binary. Convert to grayscale first and use the spinbox to set the threshold (0-255).</li>"
            "<li><b>Smoothing:</b><br>"
            "Includes 5 filters with different parameters:<br>"
            "<ul>"
            "<li>LowPass and HighPass filters require the image to be in the frequency domain. Use the FFT button to transfer the image.</li>"
            "<li>Kernel size ranges from 3 to 9 (odd numbers), which affects the strength of the filter.</li>"
            "<li>The frequency parameter (0.1 to 10) is used by Gaussian Blur and Low Pass filters.</li>"
            "<li>The order parameter (used by Low Pass filter) indicates the number of reactive components in the filter design.</li>"
            "</ul>"
            "</li>"
            "<li><b>Edge Detection:</b><br>"
            "Includes three operations with adjustable parameters:<br>"
            "<ul>"
            "<li>Kernel size ranges from 3 to 9.</li>"
            "<li>Low and high thresholds for the Canny Edge detector identify weak and strong edges.</li>"
            "<li>X and Y parameters detect vertical and horizontal edges, respectively.</li>"
            "</ul>"
            "</li>"
            "<li><b>Morphological Operations:</b><br>"
            "Includes 4 operations. Use the Kernel size and shape combobox to create an element structure that determines how the operations are applied to the image.</li>"
            "<li><b>Histogram Manipulation:</b><br>"
            "Includes Histogram Equalization and Stretching to enhance contrast and visibility.</li>"
            "<li><b>Frequency Domain:</b><br>"
            "Use the FFT button to transfer the image to the frequency domain.<br>"
            "<ul>"
            "<li>Border combo box and spinbox determine FFT size and spacing.</li>"
            "<li>Rotate Phase button rotates the phase of the image.</li>"
            "<li>Restore button brings the image back to the spatial domain.</li>"
            "</ul>"
            "</li>"
            "<li><b>Flip, Rotate:</b><br>"
            "Flip the image vertically or horizontally and rotate by 90 degrees.</li>"
            "<li><b>Undo, Redo, Reset:</b><br>"
            "Undo or redo changes. Reset clears all editing.</li>"
            "<li><b>Save & Delete:</b><br>"
            "Save the edited image to your computer, choosing its name and location. Delete button removes the loaded image.</li>"
            "</ul>";


        // Create a QDialog
        QDialog *helpDialog = new QDialog(this);
        helpDialog->setWindowTitle("Help");

        // Create a QTextEdit to display the help text
        QTextEdit *textEdit = new QTextEdit(helpDialog);
        textEdit->setHtml(helpText);
        textEdit->setReadOnly(true); // Make the text edit read-only
        textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Ensure it expands
        //Window Size
        helpDialog->resize(800, 600);

        // Create a QVBoxLayout and add the QTextEdit to it
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(textEdit);

        // Set the layout on the dialog
        helpDialog->setLayout(layout);

        // Show the dialog
        helpDialog->exec();
}


