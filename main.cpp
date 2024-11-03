#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QPainter>
#include <QResizeEvent>

class Nodo {
public:
    int dato;
    QVector<Nodo*> vecinos;
    QPoint pos; // Posición del nodo en el tablero

    Nodo(int d, const QPoint& position) : dato(d), pos(position) {}
};

class Tablero : public QWidget {
public:
    Tablero(QWidget* parent = nullptr) 
        : QWidget(parent) {
        setMinimumSize(400, 400);
        setWindowTitle("Juego de Tablero");

        // Crear nodos
        for (int i = 0; i < 5; ++i) {
            Nodo* nodo = new Nodo(i, QPoint(0, 0)); // Inicializa con una posición nula
            nodos.append(nodo);

            QPushButton* boton = new QPushButton(QString::number(nodo->dato), this);
            boton->setGeometry(0, 0, 60, 30); // Inicializa con geometría nula
            connect(boton, &QPushButton::clicked, [=]() { manejarClick(nodo); });
        }

        conectarNodos();
        actualizarPosiciones(); // Establecer las posiciones iniciales
    }

protected:
    void resizeEvent(QResizeEvent* event) override {
        QWidget::resizeEvent(event);
        actualizarPosiciones(); // Actualiza las posiciones al redimensionar
    }

    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setPen(Qt::black); // Color de la línea

        for (Nodo* nodo : nodos) {
            // Dibuja líneas hacia los nodos vecinos
            for (Nodo* vecino : nodo->vecinos) {
                painter.drawLine(nodo->pos.x() + 30, nodo->pos.y() + 15, 
                                 vecino->pos.x() + 30, vecino->pos.y() + 15);
            }
        }
    }

private:
    QVector<Nodo*> nodos;

    void conectarNodos() {
        nodos[0]->vecinos.append(nodos[1]);
        nodos[0]->vecinos.append(nodos[2]);
        nodos[0]->vecinos.append(nodos[4]);

        nodos[1]->vecinos.append(nodos[0]);
        nodos[1]->vecinos.append(nodos[3]);

        nodos[2]->vecinos.append(nodos[0]);
        nodos[2]->vecinos.append(nodos[3]);

        nodos[3]->vecinos.append(nodos[1]);
        nodos[3]->vecinos.append(nodos[2]);
        nodos[3]->vecinos.append(nodos[4]);

        nodos[4]->vecinos.append(nodos[0]);
        nodos[4]->vecinos.append(nodos[3]);
    }

    void actualizarPosiciones() {
        int width = this->width();
        int height = this->height();

        // Definir nuevas posiciones de los nodos en relación con el tamaño de la ventana
        QVector<QPoint> posiciones = {
            QPoint(width / 4, height / 2),   // Nodo 0
            QPoint(width / 2, height / 4),   // Nodo 1
            QPoint(3 * width / 4, height / 2), // Nodo 2
            QPoint(width / 2, 3 * height / 4), // Nodo 3
            QPoint(width / 4, 3 * height / 4) // Nodo 4
        };

        // Actualizar la posición de los nodos y los botones
        for (int i = 0; i < nodos.size(); ++i) {
            nodos[i]->pos = posiciones[i];

            // Actualizar la geometría del botón
            QPushButton* boton = findChild<QPushButton*>(QString::number(i));
            if (boton) {
                boton->setGeometry(posiciones[i].x(), posiciones[i].y(), 60, 30);
            }
        }

        update(); // Pinta de nuevo el widget
    }

    void manejarClick(Nodo* nodo) {
        qDebug() << "Nodo clicado:" << nodo->dato;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Tablero tablero;
    tablero.show();
    return app.exec();
}
