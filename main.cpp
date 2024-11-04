#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QVector>

class Nodo {
public:
    int dato; // Dato del nodo
    QVector<Nodo*> vecinos; // Lista de nodos conectados
    QPoint posicion; // Posición del nodo

    Nodo(int d) : dato(d) {} // Constructor
};

class GrafoWidget : public QWidget {
    QVector<Nodo*> nodos; // Lista de nodos en el grafo
    int nodeCount = 33; // Número de nodos

public:
    GrafoWidget() {
        initializeGraph();
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);

        // Calcular posiciones de los nodos según el tamaño de la ventana
        int width = this->width();
        int height = this->height() - 60; // Ajustar altura si es necesario
        setNodePositions(width, height);

        // Dibujar las conexiones entre nodos
        painter.setPen(Qt::black);
        for (Nodo* nodo : nodos) {
            for (Nodo* vecino : nodo->vecinos) {
                painter.drawLine(nodo->posicion, vecino->posicion);
            }
        }

        // Dibujar cada nodo (círculo)
        for (Nodo* nodo : nodos) {
            painter.setBrush(Qt::lightGray);
            painter.drawEllipse(nodo->posicion.x() - 10, nodo->posicion.y() - 10, 20, 20);
            painter.drawText(nodo->posicion.x() - 5, nodo->posicion.y() + 5, QString::number(nodo->dato));
        }
    }

    void initializeGraph() {
        // Crear nodos
        for (int i = 0; i < nodeCount; i++) {
            nodos.append(new Nodo(i));
        }

        // Definir las conexiones usando una matriz de adyacencia
        int adjacencyMatrix[33][33] = {
        {0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //2
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //4
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //5
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //6
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //8
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //9
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //10
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //11
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //12
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //13
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //14
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //15
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //16
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //17
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //18
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //19
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //20
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //21
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //22
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //23
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //24
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //25
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //26
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //27
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //28
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //29
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //30
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //31
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //32
    };

        // Inicializa las conexiones a partir de la matriz de adyacencia
        for (int i = 0; i < nodeCount; i++) {
            for (int j = 0; j < nodeCount; j++) {
                if (adjacencyMatrix[i][j] == 1) {
                    nodos[i]->vecinos.append(nodos[j]);
                }
            }
        }
    }

    void setNodePositions(int width, int height) {
        // Calcular posiciones de los nodos de manera responsiva
        // Puedes ajustar estos valores para crear la disposición que prefieras
        nodos[0]->posicion = QPoint(width * 3 / 8, height / 8); // 0
        nodos[1]->posicion = QPoint(width * 4 / 8, height / 8); // 1
        nodos[2]->posicion = QPoint(width * 5 / 8, height / 8); // 2

        nodos[3]->posicion = QPoint(width * 3 / 8, height * 2 / 8); // 3
        nodos[4]->posicion = QPoint(width * 4 / 8, height * 2 / 8); // 4
        nodos[5]->posicion = QPoint(width * 5 / 8, height * 2 / 8); // 5

        nodos[6]->posicion = QPoint(width * 3 / 8, height * 3 / 8); // 6
        nodos[7]->posicion = QPoint(width * 4 / 8, height * 3 / 8); // 7
        nodos[8]->posicion = QPoint(width * 5 / 8, height * 3 / 8); // 8

        nodos[9]->posicion = QPoint(width * 1 / 8, height * 3 / 8); // 9
        nodos[10]->posicion = QPoint(width * 2 / 8, height * 3 / 8); // 10
        nodos[11]->posicion = QPoint(width * 6 / 8, height * 3 / 8); // 11
        nodos[12]->posicion = QPoint(width * 7 / 8, height * 3 / 8); // 12

        nodos[13]->posicion = QPoint(width * 1 / 8, 2 * height / 4); // 13
        nodos[14]->posicion = QPoint(width * 2 / 8, 2 * height / 4); // 14
        nodos[15]->posicion = QPoint(width * 3 / 8, 2 * height / 4); // 15
        nodos[16]->posicion = QPoint(width * 4 / 8, 2 * height / 4); // 16
        nodos[17]->posicion = QPoint(width * 5 / 8, 2 * height / 4); // 17
        nodos[18]->posicion = QPoint(width * 6 / 8, 2 * height / 4); // 18
        nodos[19]->posicion = QPoint(width * 7 / 8, 2 * height / 4); // 19

        nodos[20]->posicion = QPoint(width * 1 / 8, height * 5 / 8); // 20
        nodos[21]->posicion = QPoint(width * 2 / 8, height * 5 / 8); // 21
        nodos[22]->posicion = QPoint(width * 3 / 8, height * 5 / 8); // 22
        nodos[23]->posicion = QPoint(width * 4 / 8, height * 5 / 8); // 23
        nodos[24]->posicion = QPoint(width * 5 / 8, height * 5 / 8); // 24
        nodos[25]->posicion = QPoint(width * 6 / 8, height * 5 / 8); // 25
        nodos[26]->posicion = QPoint(width * 7 / 8, height * 5 / 8); // 26

        nodos[27]->posicion = QPoint(width * 3 / 8, height * 6 / 8); // 27
        nodos[28]->posicion = QPoint(width * 4 / 8, height * 6 / 8); // 28
        nodos[29]->posicion = QPoint(width * 5 / 8, height * 6 / 8); // 29

        nodos[30]->posicion = QPoint(width * 3 / 8, height * 7 / 8); // 30
        nodos[31]->posicion = QPoint(width * 4 / 8, height * 7 / 8); // 31
        nodos[32]->posicion = QPoint(width * 5 / 8, height * 7 / 8); // 32
    }

public:
    ~GrafoWidget() {
        // Liberar memoria de los nodos
        qDeleteAll(nodos);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    GrafoWidget window;
    window.resize(400, 400);
    window.setWindowTitle("Grafo Simple");
    window.show();
    
    return app.exec();
}
