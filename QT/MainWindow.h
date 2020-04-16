#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "downloader.h"
#include <QString>
#include <QFile>
#include <QLabel>
#include <QScrollArea>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QtCharts>
#include <QCoreApplication>
//#include <qDebug>

class MainWindow: public QMainWindow
{
  Q_OBJECT
private:
    unsigned int EMIArtist; //contEMIArtist
    unsigned int UniversalArtist; //contUniversalArtist
    bool flag; //Serve per sapere se ricalcolare o meno

public:
  MainWindow(){
      EMIArtist = 0;
      UniversalArtist = 0;
      flag = false;
  }
  ~ MainWindow(){}

  void Execute(){

      const QString preURL = "https://en.wikipedia.org";
      QFile file(QCoreApplication::applicationDirPath() + "/tempFile.txt");

      QLabel *testLabel= new QLabel;
      QString line;
      QString temp;
      QStringList list;
      if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
          QTextStream stream(&file);
          while (!stream.atEnd()){
              temp = stream.readLine();
              if( temp.compare("&&&&&") == 0 )
                  break;
              list = temp.split('"');
              //this->EMIArtist++;
              if( list[2].isEmpty() ){
                  list[2].append("???");
              }
              if( list[1].isEmpty() ){
                  line.append(list[2]+ "<br/>");
              }
              else{
                  line.append("<a href=\""+preURL+list[1]+"\">"+list[2]+ "</a> <br/>");
              }
          }
          testLabel->setText(line);
      }
      file.close();

      testLabel->setTextFormat(Qt::RichText);
      testLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
      testLabel->setOpenExternalLinks(true);

      QLabel *title1 = new QLabel("List of EMI artists");

      QScrollArea *scrollArea1 = new QScrollArea;
      scrollArea1->setBackgroundRole(QPalette::Light);
      scrollArea1->setWidget(testLabel);



      QFile file2(QCoreApplication::applicationDirPath() + "/tempFile.txt");
      QLabel *testLabel2= new QLabel;

      QString line2;
      QString temp2;
      QStringList list2;
      unsigned int cont = 0;
      if (file2.open(QIODevice::ReadOnly | QIODevice::Text)){
          QTextStream stream2(&file2);
          while (!stream2.atEnd()){
              temp2 = stream2.readLine();
              if( cont == 1 && temp2.compare("&&&&&") != 0 && !temp2.isEmpty() ){
                  list2 = temp2.split('"');
                  if( list2[2].isEmpty() ){
                      list2[2].append("???");
                  }
                  if( list2[1].isEmpty() ){
                      line2.append(list2[2]+ "<br/>");
                  }
                  else{
                      line2.append("<a href=\""+preURL+list2[1]+"\">"+list2[2]+ "</a> <br/>");
                  }
                  //this->UniversalArtist++;
              }
              if( temp2.compare("&&&&&") == 0 )
                  cont++;
          }
          testLabel2->setText(line2);
      }
      file2.close();

      testLabel2->setTextFormat(Qt::RichText);
      testLabel2->setTextInteractionFlags(Qt::TextBrowserInteraction);
      testLabel2->setOpenExternalLinks(true);

      QLabel *title2 = new QLabel("List of Universal artists");


      QScrollArea *scrollArea2 = new QScrollArea;
      scrollArea2->setBackgroundRole(QPalette::Light);
      scrollArea2->setWidget(testLabel2);




      QPushButton *button1= new QPushButton;
      button1->setText("Plot Graph Numbers");
      QObject::connect(button1, SIGNAL(clicked()),this, SLOT( clickedSlot1() ) );




      QPushButton *button2= new QPushButton;
      button2->setText("Plot Graph Letters");
      QObject::connect(button2, SIGNAL(clicked()),this, SLOT( clickedSlot2() ) );




      QGroupBox *groupBox = new QGroupBox(); //QWidget *groupBox = new QWidget;

      QVBoxLayout *vbox = new QVBoxLayout;
      vbox->addWidget(title1);
      vbox->addWidget(scrollArea1);
      vbox->addWidget(title2);
      vbox->addWidget(scrollArea2);
      vbox->addWidget(button1);
      vbox->addWidget(button2);
      vbox->addStretch(1);

      groupBox->setLayout(vbox);
      groupBox->show();


  }

public slots:
  void clickedSlot1(){
      //Grafo per i numeri degli artisti
      if( !flag ){

          QFile file(QCoreApplication::applicationDirPath() + "/tempFile.txt");
          QString line;
          QString temp;
          QStringList list;
          if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
              QTextStream stream(&file);
              while (!stream.atEnd()){
                  temp = stream.readLine();
                  if( temp.compare("&&&&&") == 0 )
                      break;

                  this->EMIArtist++;
              }
          }
          file.close();

          QFile file2(QCoreApplication::applicationDirPath() + "/tempFile.txt");
          QString line2;
          QString temp2;
          QStringList list2;
          unsigned int cont = 0;
          if (file2.open(QIODevice::ReadOnly | QIODevice::Text)){
              QTextStream stream2(&file2);
              while (!stream2.atEnd()){
                  temp2 = stream2.readLine();
                  if( cont == 1 && temp2.compare("&&&&&") != 0 && !temp2.isEmpty() ){
                      this->UniversalArtist++;
                  }
                  if( temp2.compare("&&&&&") == 0 )
                      cont++;
              }
          }
          file2.close();

          flag = true;
      }

      QBarSet *set1 = new QBarSet("Universal Artists (N." + QString::number(this->UniversalArtist) +")" );
      QBarSet *set0 = new QBarSet("EMI Artists (N." + QString::number(this->EMIArtist) +")" );

      *set1 << this->UniversalArtist ;
      *set0 << this->EMIArtist ;

      QBarSeries *barseries = new QBarSeries();
      barseries->append(set0);
      barseries->append(set1);

      QChart *chart = new QChart();
      chart->addSeries(barseries);
      chart->setTitle("Number of Artists");

      QValueAxis *axisY = new QValueAxis();
      chart->addAxis(axisY, Qt::AlignLeft);
      barseries->attachAxis(axisY);
      axisY->setRange(0, max(this->EMIArtist, this->UniversalArtist) );

      QChartView *chartView = new QChartView(chart);
      chartView->setRenderHint(QPainter::Antialiasing);

      QMainWindow *window = new QMainWindow;
      window->setCentralWidget(chartView);
      window->resize(440, 300);
      window->show();

  }

  void clickedSlot2(){
      //Grafico per le Lettere degli artisti
      //EMI
      QBarSet *set0 = new QBarSet("A");
      QBarSet *set1 = new QBarSet("B");
      QBarSet *set2 = new QBarSet("C");
      QBarSet *set3 = new QBarSet("D");
      QBarSet *set4 = new QBarSet("E");
      QBarSet *set5 = new QBarSet("F");
      QBarSet *set6 = new QBarSet("G");
      QBarSet *set7 = new QBarSet("H");
      QBarSet *set8 = new QBarSet("I");
      QBarSet *set9 = new QBarSet("J");
      QBarSet *set10 = new QBarSet("K");
      QBarSet *set11 = new QBarSet("L");
      QBarSet *set12 = new QBarSet("M");
      QBarSet *set13 = new QBarSet("N");
      QBarSet *set14 = new QBarSet("O");
      QBarSet *set15 = new QBarSet("P");
      QBarSet *set16 = new QBarSet("Q");
      QBarSet *set17 = new QBarSet("R");
      QBarSet *set18 = new QBarSet("S");
      QBarSet *set19 = new QBarSet("T");
      QBarSet *set20 = new QBarSet("U");
      QBarSet *set21 = new QBarSet("V");
      QBarSet *set22 = new QBarSet("W");
      QBarSet *set23 = new QBarSet("X");
      QBarSet *set24 = new QBarSet("Y");
      QBarSet *set25 = new QBarSet("Z");
      QBarSet *set26 = new QBarSet("altro");

      int array[27];
      lettersUniversal(array);


      *set0 << array[0] ;
      *set1 << array[1] ;
      *set2 << array[2] ;
      *set3 << array[3] ;
      *set4 << array[4] ;
      *set5 << array[5] ;
      *set6 << array[6] ;
      *set7 << array[7] ;
      *set8 << array[8] ;
      *set9 << array[9] ;
      *set10 << array[10] ;
      *set11 << array[11] ;
      *set12 << array[12] ;
      *set13 << array[13] ;
      *set14 << array[14] ;
      *set15 << array[15] ;
      *set16 << array[16] ;
      *set17 << array[17] ;
      *set18 << array[18] ;
      *set19 << array[19] ;
      *set20 << array[20] ;
      *set21 << array[21] ;
      *set22 << array[22] ;
      *set23 << array[23] ;
      *set24 << array[24] ;
      *set25 << array[25] ;
      *set26 << array[26] ;


      QBarSeries *barseries = new QBarSeries();
      barseries->append(set0);
      barseries->append(set1);
      barseries->append(set2);
      barseries->append(set3);
      barseries->append(set4);
      barseries->append(set5);
      barseries->append(set6);
      barseries->append(set7);
      barseries->append(set8);
      barseries->append(set9);
      barseries->append(set10);
      barseries->append(set11);
      barseries->append(set12);
      barseries->append(set13);
      barseries->append(set14);
      barseries->append(set15);
      barseries->append(set16);
      barseries->append(set17);
      barseries->append(set18);
      barseries->append(set19);
      barseries->append(set20);
      barseries->append(set21);
      barseries->append(set22);
      barseries->append(set23);
      barseries->append(set24);
      barseries->append(set25);
      barseries->append(set26);

      barseries->setLabelsVisible(true);


      QChart *chart = new QChart();
      chart->addSeries(barseries);
      chart->setTitle("EMI Artists");

      QValueAxis *axisY = new QValueAxis();
      chart->addAxis(axisY, Qt::AlignLeft);
      barseries->attachAxis(axisY);
      axisY->setRange(0, max(array) );

      QChartView *chartView = new QChartView(chart);
      chartView->setRenderHint(QPainter::Antialiasing);

      QMainWindow *window = new QMainWindow;
      window->setCentralWidget(chartView);
      window->resize(440, 300);
      window->show();



      //Universal
      QBarSet *set0b = new QBarSet("A");
      QBarSet *set1b = new QBarSet("B");
      QBarSet *set2b = new QBarSet("C");
      QBarSet *set3b = new QBarSet("D");
      QBarSet *set4b = new QBarSet("E");
      QBarSet *set5b = new QBarSet("F");
      QBarSet *set6b = new QBarSet("G");
      QBarSet *set7b = new QBarSet("H");
      QBarSet *set8b = new QBarSet("I");
      QBarSet *set9b = new QBarSet("J");
      QBarSet *set10b = new QBarSet("K");
      QBarSet *set11b = new QBarSet("L");
      QBarSet *set12b = new QBarSet("M");
      QBarSet *set13b = new QBarSet("N");
      QBarSet *set14b = new QBarSet("O");
      QBarSet *set15b = new QBarSet("P");
      QBarSet *set16b = new QBarSet("Q");
      QBarSet *set17b = new QBarSet("R");
      QBarSet *set18b = new QBarSet("S");
      QBarSet *set19b = new QBarSet("T");
      QBarSet *set20b = new QBarSet("U");
      QBarSet *set21b = new QBarSet("V");
      QBarSet *set22b = new QBarSet("W");
      QBarSet *set23b = new QBarSet("X");
      QBarSet *set24b = new QBarSet("Y");
      QBarSet *set25b = new QBarSet("Z");
      QBarSet *set26b = new QBarSet("altro");

      int arrayb[27];
      lettersEMI(arrayb);

      *set0b << arrayb[0] ;
      *set1b << arrayb[1] ;
      *set2b << arrayb[2] ;
      *set3b << arrayb[3] ;
      *set4b << arrayb[4] ;
      *set5b << arrayb[5] ;
      *set6b << arrayb[6] ;
      *set7b << arrayb[7] ;
      *set8b << arrayb[8] ;
      *set9b << arrayb[9] ;
      *set10b << arrayb[10] ;
      *set11b << arrayb[11] ;
      *set12b << arrayb[12] ;
      *set13b << arrayb[13] ;
      *set14b << arrayb[14] ;
      *set15b << arrayb[15] ;
      *set16b << arrayb[16] ;
      *set17b << arrayb[17] ;
      *set18b << arrayb[18] ;
      *set19b << arrayb[19] ;
      *set20b << arrayb[20] ;
      *set21b << arrayb[21] ;
      *set22b << arrayb[22] ;
      *set23b << arrayb[23] ;
      *set24b << arrayb[24] ;
      *set25b << arrayb[25] ;
      *set26b << arrayb[26] ;


      QBarSeries *barseriesb = new QBarSeries();
      barseriesb->append(set0b);
      barseriesb->append(set1b);
      barseriesb->append(set2b);
      barseriesb->append(set3b);
      barseriesb->append(set4b);
      barseriesb->append(set5b);
      barseriesb->append(set6b);
      barseriesb->append(set7b);
      barseriesb->append(set8b);
      barseriesb->append(set9b);
      barseriesb->append(set10b);
      barseriesb->append(set11b);
      barseriesb->append(set12b);
      barseriesb->append(set13b);
      barseriesb->append(set14b);
      barseriesb->append(set15b);
      barseriesb->append(set16b);
      barseriesb->append(set17b);
      barseriesb->append(set18b);
      barseriesb->append(set19b);
      barseriesb->append(set20b);
      barseriesb->append(set21b);
      barseriesb->append(set22b);
      barseriesb->append(set23b);
      barseriesb->append(set24b);
      barseriesb->append(set25b);
      barseriesb->append(set26b);

      barseriesb->setLabelsVisible(true);



      QChart *chartb = new QChart();
      chartb->addSeries(barseriesb);
      chartb->setTitle("Universal Artists");

      QValueAxis *axisYb = new QValueAxis();
      chartb->addAxis(axisYb, Qt::AlignLeft);
      barseriesb->attachAxis(axisYb);
      axisYb->setRange(0, max(arrayb) );

      QChartView *chartViewb = new QChartView(chartb);
      chartViewb->setRenderHint(QPainter::Antialiasing);

      QMainWindow *windowb = new QMainWindow;
      windowb->setCentralWidget(chartViewb);
      windowb->resize(440, 300);
      windowb->show();

  }

  void ExecutSlot(){
      //qDebug() << "executeSlot";
      Execute();
  }

private:
  int max(int a, int b){
      if( a > b ){
          return a;
      }
      return b;
  }

  void lettersUniversal(int array[27]){
      for(int i = 0; i < 27; i++){
          array[i] = 0;
      }

      QFile file(QCoreApplication::applicationDirPath() + "/tempFile.txt");
      QString temp;
      QStringList list;
      int index;
      if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
          QTextStream stream(&file);
          while (!stream.atEnd()){
              temp = stream.readLine();
              if( temp.compare("&&&&&") == 0 )
                  break;
              list = temp.split('"');
              if( list[2].isEmpty() ){
                  array[26]++;
              }
              else{
                  index = list[2].trimmed()[0].toLower().unicode() - QChar('a').unicode();
                  if( index > 25 || index < 0 ){
                      array[26]++;
                  }
                  else{
                      array[index]++;
                  }
              }
          }
      }
      file.close();

  }

  void lettersEMI(int array2[27]){
      for(int i = 0; i < 27; i++){
          array2[i] = 0;
      }

      QFile file2(QCoreApplication::applicationDirPath() + "/tempFile.txt");
      QString temp2;
      QStringList list2;
      int index2;

      unsigned int cont = 0;
      if (file2.open(QIODevice::ReadOnly | QIODevice::Text)){
          QTextStream stream2(&file2);
          while (!stream2.atEnd()){
              temp2 = stream2.readLine();
              if( cont == 1 && temp2.compare("&&&&&") != 0 && !temp2.isEmpty() ){

                  list2 = temp2.split('"');
                  if( list2[2].isEmpty() ){
                      array2[26]++;
                  }
                  else{
                      index2 = list2[2].trimmed()[0].toLower().unicode() - QChar('a').unicode();
                      if( index2 > 25 || index2 < 0 ){
                          array2[26]++;
                      }
                      else{
                          array2[index2]++;
                      }
                  }
              }
              if( temp2.compare("&&&&&") == 0 )
                  cont++;
          }
      }
      file2.close();

  }

  int max(int array[27]){
      int m = array[0];
      for(int i = 1; i < 27; i++){
          if( array[i] > m ){
              m = array[i];
          }
      }
      return m;
  }

};


#endif // MAINWINDOW_H
