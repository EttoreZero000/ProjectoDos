#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QVector>

class Nodo {
public:
    int dato; // Dato del nodo
    QVector<Nodo*> vecinos; // Lista de nodos conectados

    Nodo(int d) : dato(d) {} // Constructor
};

class GrafoWidget : public QWidget {
    QVector<Nodo*> nodos; // Lista de nodos en el grafo

public:
    GrafoWidget() {
        // Inicializar el grafo
        initializeGraph();
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        
        // Tamaño de la ventana
        int width = this->width();
        int height = this->height() - 60; // Ajustar altura si es necesario
        
        // Coordenadas centradas de los nodos
        QPoint nodes[9] = {
            QPoint(width / 3, height / 20), // 0
            QPoint(width / 2, height / 20),   // 1
            QPoint(width * 2/3, height / 20), // 2

            QPoint(width / 3, height / 7),   // 3
            QPoint(width / 2, height / 7), // 4
            QPoint(width * 2/3, height / 7), // 5

            QPoint(width / 3, height / 4),// 6
            QPoint(width / 2, height / 4),// 7
            QPoint(width * 2/3, height / 4)// 8
        };

        // Dibujar las conexiones entre nodos
        painter.setPen(Qt::black);
        for (Nodo* nodo : nodos) {
            for (Nodo* vecino : nodo->vecinos) {
                int x1 = nodes[nodo->dato].x();
                int y1 = nodes[nodo->dato].y();
                int x2 = nodes[vecino->dato].x();
                int y2 = nodes[vecino->dato].y();
                painter.drawLine(x1, y1, x2, y2);
            }
        }

        // Dibujar cada nodo (círculo)
        for (int i = 0; i < nodos.size(); i++) {
            painter.setBrush(Qt::lightGray);
            painter.drawEllipse(nodes[i].x() - 10, nodes[i].y() - 10, 20, 20);
            
            // Dibujar número dentro del nodo
            painter.drawText(nodes[i].x() - 5, nodes[i].y() + 5, QString::number(nodos[i]->dato));
        }
    }

    void initializeGraph() {
        // Crear nodos
        for (int i = 0; i < 9; i++) {
            nodos.append(new Nodo(i)); // Crear nodos con valores de 0 a 6
        }

        // Inicializa el grafo con conexiones (nodos adyacentes)
        nodos[0]->vecinos = {nodos[1], nodos[3], nodos[4]};
        nodos[1]->vecinos = {nodos[0], nodos[2], nodos[4]};
        nodos[2]->vecinos = {nodos[1], nodos[4], nodos[5]};
        nodos[3]->vecinos = {nodos[0], nodos[4], nodos[6]};
        nodos[4]->vecinos = {nodos[0], nodos[1], nodos[2], nodos[3], nodos[5], nodos[6], nodos[7], nodos[8]};
        nodos[5]->vecinos = {nodos[2], nodos[4], nodos[8]};
        nodos[6]->vecinos = {nodos[3], nodos[4], nodos[7]};
        nodos[7]->vecinos = {nodos[4], nodos[6], nodos[8]};
        nodos[8]->vecinos = {nodos[4], nodos[5], nodos[7]};
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
