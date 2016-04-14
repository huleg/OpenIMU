#include "accdatadisplay.h"
#include "newAcquisition/wimuacquisition.h"

#include <QPropertyAnimation>

QT_CHARTS_USE_NAMESPACE

AccDataDisplay::AccDataDisplay()
{

}
AccDataDisplay::AccDataDisplay(std::string filePath){

    WimuAcquisition acceleroData = WimuAcquisition(filePath,50);

    accReader = new AccelerometerReader(filePath);

    accReader->LoadSensorData(false);
    availableData = accReader->GetAccelerometerData();

    if(availableData.size()>0)
    {

        chart = new QChart();
        chart->legend()->show();
        chart->legend()->setAlignment(Qt::AlignBottom);
        fillChartSeries(0);

        chart->createDefaultAxes();
        chart->setTitle("Données accéléromètre");

        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        centralWidget = new QWidget();
        layout = new QVBoxLayout(centralWidget);

        //Initialize Slider
        slider = new QSlider();
        slider->setOrientation(Qt::Horizontal);
        layout->addWidget(chartView);
        layout->addWidget(slider);

        connect(slider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));
    }
}
void AccDataDisplay::sliderValueChanged(int value)
{
    //chart->setTitle("Slider Value is: "+ QString::number(value) );
    chart->removeAllSeries();
    fillChartSeries(value);
    chartView->setChart(chart);
}
void AccDataDisplay::fillChartSeries(int i){

    vector<signed short> x;
    vector<signed short> y;
    vector<signed short> z;
    vector<float> t;

    for(int k = i; k <availableData.at(0).getDataPerDay().at(0).getAccelerometerDataPerHour().size();k++){
        for(float i=0.0;i<0.98;i+=0.02)
        {
            t.push_back(i+k);
        }

        vector<signed short> tmpx = availableData.at(0).getDataPerDay().at(0).getAccelerometerDataPerHour().at(k).getXAxisValues();
        vector<signed short> tmpy = availableData.at(0).getDataPerDay().at(0).getAccelerometerDataPerHour().at(k).getYAxisValues();
        vector<signed short> tmpz = availableData.at(0).getDataPerDay().at(0).getAccelerometerDataPerHour().at(k).getZAxisValues();

        x.insert(x.end(),tmpx.begin(),tmpx.end());
        y.insert(y.end(),tmpy.begin(),tmpy.end());
        z.insert(z.end(),tmpz.begin(),tmpz.end());
    }

    lineseriesX = new QtCharts::QLineSeries();
    lineseriesX->setName("Axe X");
    lineseriesX->setUseOpenGL(true);

    lineseriesY = new QtCharts::QLineSeries();
    lineseriesY->setName("Axe Y");
    lineseriesY->setUseOpenGL(true);

    lineseriesZ = new QtCharts::QLineSeries();
    lineseriesZ->setName("Axe Z");
    lineseriesZ->setUseOpenGL(true);

    for(unsigned int i = 0; i <x.size(); i++)
    {
        lineseriesX->append(QPoint(t.at(i),x.at(i)));
        lineseriesY->append(QPoint(t.at(i),y.at(i)));
        lineseriesZ->append(QPoint(t.at(i),z.at(i)));
    }
    chart->addSeries(lineseriesX);
    chart->addSeries(lineseriesY);
    chart->addSeries(lineseriesZ);
}
QWidget * AccDataDisplay::getCentralView(){
    return centralWidget;
}

