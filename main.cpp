#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QString>
#include <QDebug>

class Nodo {
public:
    int dato;
    QVector<Nodo*> vecinos;

    Nodo(int d) : dato(d) {}
};

class Tablero : public QWidget {
public:
    Tablero(int filas, int columnas, QWidget* parent = nullptr) : QWidget(parent) {
        QGridLayout* layout = new QGridLayout(this);
        for (int i = 0; i < filas; ++i) {
            QVector<Nodo*> fila;
            for (int j = 0; j < columnas; ++j) {
                Nodo* nodo = new Nodo(i * columnas + j);
                fila.append(nodo);

                QPushButton* boton = new QPushButton(QString::number(nodo->dato));
                layout->addWidget(boton, i, j);

                // Conectar el botón a una función que maneje la interacción
                connect(boton, &QPushButton::clicked, [=]() { manejarClick(nodo); });
            }
            nodos.append(fila);
        }

        conectarNodos();
    }

private:
    QVector<QVector<Nodo*>> nodos;

    void conectarNodos() {
        for (int i = 0; i < nodos.size(); ++i) {
            for (int j = 0; j < nodos[i].size(); ++j) {
                if (i > 0) nodos[i][j]->vecinos.append(nodos[i - 1][j]); // arriba
                if (i < nodos.size() - 1) nodos[i][j]->vecinos.append(nodos[i + 1][j]); // abajo
                if (j > 0) nodos[i][j]->vecinos.append(nodos[i][j - 1]); // izquierda
                if (j < nodos[i].size() - 1) nodos[i][j]->vecinos.append(nodos[i][j + 1]); // derecha
            }
        }
    }

    void manejarClick(Nodo* nodo) {
        // Aquí puedes manejar la lógica del juego al hacer clic en un nodo
        // Por ejemplo, mostrar el número del nodo
        qDebug() << "Nodo clicado:" << nodo->dato;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Tablero tablero(3, 3);
    tablero.setWindowTitle("Juego de Tablero");
    tablero.show();
    return app.exec();
}
