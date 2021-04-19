#include "mainwindow.h"
#include <QApplication>
#include <cmath>

#include "qcustomplot.h"
#include <iostream>
using namespace std;


void graficarFuncion(QMainWindow &win, QVector<double> &x, QVector<double> &y)
{
    //Creando un objeto QCustomPlot (es un tipo de widget).
    QCustomPlot *cPlot = new QCustomPlot();

    //El widget cPlot definido sera el widget principal de la ventana creada.
    win.setCentralWidget(cPlot);

    //Definir un grafico nuevo en el cPlot

    cPlot->addGraph();

    //Asignamos los datos a graficar
    cPlot->graph(0)->setData(x, y);
    cPlot->graph(0)->rescaleAxes();

    //Poner las etiquetas a los ejes.
    cPlot->xAxis->setLabel("Valores Joystick Parallax");
    cPlot->yAxis->setLabel("Valores Driver Pololu");


    //Definir las posiciones y dimensiones de la VENTANA
    win.setGeometry(100,100,500,400);
    win.show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Crear un widget tipo ventanas.

    QMainWindow win;

    /* El rango de valores del joystick en el eje horizontal es de: 387 a 643. Diferencia: 643-387: 256
     * El centro del joystick está en 512.
     * El rango de valores del Driver Pololu es: -3200 a 3200.     */
    int valMinJoystick = 387;
    int valMaxJoystick = 643;
    int valMedioJoystick = 512;
    int diferencia = valMaxJoystick - valMinJoystick + 1;

    //Creamos dos arreglos del tipo doble con tantos valores como el rango del joystick
    //Estos vectores son únicamente para graficación de los valores.
    QVector<double> x(diferencia);
    QVector<double> y(diferencia);

    //15.45 parece un buen valor para iniciar.

    float ajusteExpParking_L = 40.05;   //Más sensible al joystick.
    float ajusteExpParking_R = 41.45;

    float ajusteExpCiudad_L = 28.05;   //Sensibilidad media para la ciudad.
    float ajusteExpCiudad_R = 29.45;
    float ajusteEscalar_Ciudad = 40.0;

    float ajusteExpCarretera_L = 19.05;  //Menos sensible al joystick en la carretera .
    float ajusteExpCarretera_R = 20.05;
    float ajusteEscalar_Carretera = 5;

    bool modoCiudadActivado = false; //ModoCarreteraActivado.

    //for(int ii=0; ii<255; ii++)
    for(int ii = valMinJoystick; ii < valMaxJoystick; ii++)
    {

        double x_Temp;
        int ind = ii - valMinJoystick; //Para garantizar indices > 0.
        x[ind] = (ii - valMedioJoystick);//Para graficar valores de -127 a 127 (aprox).

        int ajusteExp;
        int signo;
        int ajusteEscalar;

        if(x[ind] >= 0) //Valores de control positivos.
        {
            signo = 1;
            if(modoCiudadActivado) {
                ajusteExp = ajusteExpCiudad_R;
                ajusteEscalar = ajusteEscalar_Ciudad;
            }
            else{ //modoCarreteraActivado
                ajusteExp = ajusteExpCarretera_R;
                ajusteEscalar = ajusteEscalar_Carretera;
            }
        }
        else { //Valores de control negativos.
            signo = -1;
            if(modoCiudadActivado) {
                ajusteExp = ajusteExpCiudad_L;
                ajusteEscalar = ajusteEscalar_Ciudad;
            } else { // ModoCarretera.
                ajusteExp = ajusteExpCarretera_L;
                ajusteEscalar = ajusteEscalar_Carretera;
            }
        }
        x_Temp = x[ind] / ajusteExp;
        y[ind] = signo*(exp(signo*(x_Temp))) * ajusteEscalar;
        y[ind] -= signo*ajusteEscalar;  //Cuando signo es negativo: sumar; cuando positivo: restar.

        if(y[ind] > 3200) y[ind] = 3200;
        if(y[ind] < -3200) y[ind]= -3200;

        cout << "X[i]: "<< x[ind]<< "\t Y[i]: " << y[ind] << endl;
    }
    cout << "Rango: (" << x[0] << ", " << y[0] << "), ";
    cout << "(" << x[valMedioJoystick-valMinJoystick] << ", " << y[valMedioJoystick-valMinJoystick] << "), ";
    cout << "(" << x[diferencia-2] << ", " << y[diferencia-2] <<")." << endl;

    graficarFuncion(win, x, y);


    return a.exec();
}
