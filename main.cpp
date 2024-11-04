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
        adjacencyList[1] = {0}; // Nodos conectados al nodo 1
        adjacencyList[2] = {1}; // Nodos conectados al nodo 2
        adjacencyList[3] = {0}; // Nodos conectados al nodo 3
        adjacencyList[4] = {0}; // Nodos conectados al nodo 4
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
