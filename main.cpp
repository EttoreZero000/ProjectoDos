#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QVector>
#include <vector>

class Nodo {
public:
    int dato; // Dato del nodo
    QVector<Nodo*> vecinos; // Lista de nodos conectados
    QPoint posicion; // Posición del nodo

    Nodo(int d) : dato(d) {} // Constructor
};

class GrafoWidget : public QWidget {
    QVector<Nodo*> nodos; // Lista de nodos en el grafo
    std::vector<std::vector<int>> adjacencyList; // Lista de adyacencia
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

        // Inicializar la lista de adyacencia
        adjacencyList.resize(nodeCount);
        
        // Definir las conexiones usando la lista de adyacencia
        adjacencyList[0] = {1, 3, 4}; // Nodos conectados al nodo 0
        adjacencyList[1] = {0, 2, 4}; // Nodos conectados al nodo 1
        adjacencyList[2] = {0, 2, 4}; // Nodos conectados al nodo 2
        adjacencyList[3] = {0, 2, 4}; // Nodos conectados al nodo 3
        adjacencyList[4] = {0, 2, 4}; // Nodos conectados al nodo 4
        adjacencyList[5] = {0, 2, 4}; // Nodos conectados al nodo 5
        adjacencyList[6] = {0, 2, 4}; // Nodos conectados al nodo 6
        adjacencyList[7] = {0, 2, 4}; // Nodos conectados al nodo 7
        adjacencyList[8] = {0, 2, 4}; // Nodos conectados al nodo 8
        adjacencyList[9] = {0, 2, 4}; // Nodos conectados al nodo 9
        adjacencyList[10] = {0, 2, 4}; // Nodos conectados al nodo 10
        adjacencyList[11] = {0, 2, 4}; // Nodos conectados al nodo 11
        adjacencyList[12] = {0, 2, 4}; // Nodos conectados al nodo 12
        adjacencyList[13] = {0, 2, 4}; // Nodos conectados al nodo 13
        adjacencyList[14] = {0, 2, 4}; // Nodos conectados al nodo 14
        adjacencyList[15] = {0, 2, 4}; // Nodos conectados al nodo 15
        adjacencyList[16] = {0, 2, 4}; // Nodos conectados al nodo 16
        adjacencyList[17] = {0, 2, 4}; // Nodos conectados al nodo 17
        adjacencyList[18] = {0, 2, 4}; // Nodos conectados al nodo 18
        adjacencyList[19] = {0, 2, 4}; // Nodos conectados al nodo 19
        adjacencyList[20] = {0, 2, 4}; // Nodos conectados al nodo 20
        adjacencyList[21] = {0, 2, 4}; // Nodos conectados al nodo 21
        adjacencyList[22] = {0, 2, 4}; // Nodos conectados al nodo 22
        adjacencyList[23] = {0, 2, 4}; // Nodos conectados al nodo 23
        adjacencyList[24] = {0, 2, 4}; // Nodos conectados al nodo 24
        adjacencyList[25] = {0, 2, 4}; // Nodos conectados al nodo 25
        adjacencyList[26] = {0, 2, 4}; // Nodos conectados al nodo 26
        adjacencyList[27] = {0, 2, 4}; // Nodos conectados al nodo 27
        adjacencyList[28] = {0, 2, 4}; // Nodos conectados al nodo 28
        adjacencyList[29] = {0, 2, 4}; // Nodos conectados al nodo 29
        adjacencyList[30] = {0, 2, 4}; // Nodos conectados al nodo 30
        adjacencyList[31] = {0, 2, 4}; // Nodos conectados al nodo 31
        adjacencyList[32] = {0, 2, 4}; // Nodos conectados al nodo 32
        // Agrega más conexiones según sea necesario para otros nodos...

        // Inicializar los vecinos de cada nodo basado en la lista de adyacencia
        for (int i = 0; i < nodeCount; i++) {
            for (int vecino : adjacencyList[i]) {
                nodos[i]->vecinos.append(nodos[vecino]);
            }
        }
    }

    void setNodePositions(int width, int height) {
        // Calcular posiciones de los nodos de manera responsiva
        nodos[0]->posicion = QPoint(width * 3 / 8, height / 8); // 0
        nodos[1]->posicion = QPoint(width * 4 / 8, height / 8); // 1
        nodos[2]->posicion = QPoint(width * 5 / 8, height / 8); // 2
        nodos[3]->posicion = QPoint(width * 3 / 8, height * 2 / 8); // 3
        nodos[4]->posicion = QPoint(width * 4 / 8, height * 2 / 8); // 4
        // Continúa asignando posiciones a los demás nodos...
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
