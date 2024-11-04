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
    int nodeCount = 11; // Número de nodos

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
        int adjacencyMatrix[11][11] = {
            {0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
            {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0},
            {0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
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
        nodos[0]->posicion = QPoint(width / 3, height / 8);
        nodos[1]->posicion = QPoint(width / 2, height / 8);
        nodos[2]->posicion = QPoint(width * 2/3, height / 8);

        nodos[3]->posicion = QPoint(width / 3, height / 4);
        nodos[4]->posicion = QPoint(width / 2, height / 4);
        nodos[5]->posicion = QPoint(width * 2/3, height / 4);

        nodos[6]->posicion = QPoint(width / 3, 3 * height / 8);
        nodos[7]->posicion = QPoint(width / 2, 3 * height / 8);
        nodos[8]->posicion = QPoint(width * 2/3, 3 * height / 8);

        nodos[9]->posicion = QPoint(width * 0.1, 3 * height / 8);
        nodos[10]->posicion = QPoint(width * 0.2, 3 * height / 8);
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
