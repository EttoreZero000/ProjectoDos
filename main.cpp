
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QVector>
#include <vector>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>



// Definir los tres estados posibles para una ficha
enum EstadoFicha {
    Blanco,  // Nodo blanco
    Negro,   // Nodo negro
    Vacío    // Nodo vacío
};

// Clase que representa una ficha (blanca, negra o vacía)
class Ficha {

public:
    EstadoFicha estado; // Estado de la ficha

    // Constructor que por defecto establece el estado en Vacío
    Ficha(EstadoFicha estado = Vacío) : estado(estado) {}

    // Método para cambiar el estado de la ficha
    void cambiarEstado() {
        if (estado == Blanco) {
            estado = Negro;
        } else if (estado == Negro) {
            estado = Vacío;
        } else {
            estado = Blanco;
        }
    }

    // Método para obtener el color asociado al estado
    QColor obtenerColor() const {
        switch (estado) {
            case Blanco:
                return Qt::white;
            case Negro:
                return Qt::black;
            case Vacío:
                return Qt::lightGray; // Color neutral para vacío
            default:
                return Qt::lightGray;
        }
    }
};

// Clase Nodo que representa un nodo en el grafo
class Nodo {
public:
    Ficha ficha; // Atributo de tipo Ficha que almacena el estado del nodo
    QVector<Nodo*> vecinos; // Lista de nodos conectados
    QPoint posicion; // Posición del nodo

    Nodo(EstadoFicha estado = Vacío) : ficha(estado) {} // Constructor, por defecto el nodo está vacío
};

class GrafoWidget : public QWidget {
    QVector<Nodo*> nodos; // Lista de nodos en el grafo
    std::vector<std::vector<int>> adjacencyList; // Lista de adyacencia
    int nodeCount = 33; // Número de nodos
    Nodo* nodoSeleccionado = nullptr; // Nodo seleccionado para mover

private:
    EstadoFicha turnoActual = Blanco; // El turno comienza con las fichas negras
    QTimer* temporizador;        // Temporizador para los 5 segundos
    bool enCadenaDeSaltos = false; // Indica si la ficha negra está en cadena de saltos

public:
    GrafoWidget() {
        initializeGraph();
        // Inicializar el temporizador
        temporizador = new QTimer(this);
        temporizador->setInterval(5000); // 5 segundos

        // Conectar el temporizador para finalizar el turno si no se realiza otro salto
        connect(temporizador, &QTimer::timeout, this, &GrafoWidget::finalizarCadenaDeSaltos);

    }

protected:
    void paintEvent(QPaintEvent *event) override {
    Q_UNUSED(event);
    QPainter painter(this);

        // Mostrar de quién es el turno actual
    QString textoTurno = (turnoActual == Negro) ? "Turno: Negro" : "Turno: Blanco";
    painter.drawText(10, 20, textoTurno);

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

    // Dibujar cada nodo (círculo) sin texto ni números
    for (Nodo* nodo : nodos) {
        // Obtener el color del nodo según su ficha
        QColor colorNodo = nodo->ficha.obtenerColor();

        painter.setBrush(colorNodo);
        painter.drawEllipse(nodo->posicion.x() - 20, nodo->posicion.y() - 20, 40, 40);

        // Resaltar el nodo seleccionado con un contorno
        if (nodo == nodoSeleccionado) {
            QPen pen(Qt::red, 3); // Contorno rojo más grueso
            painter.setPen(pen);
            painter.drawEllipse(nodo->posicion.x() - 20, nodo->posicion.y() - 20, 40, 40);
            painter.setPen(Qt::black); // Restaurar el lápiz original
        }
    }
}


    void initializeGraph() {
        // Crear nodos con ficha vacía
        for (int i = 0; i < nodeCount; i++) {
            nodos.append(new Nodo(Vacío)); // Cada nodo inicia con una ficha vacía
        }

        // Inicializar la lista de adyacencia
        adjacencyList.resize(nodeCount);

        // Definir las conexiones usando la lista de adyacencia
        adjacencyList[0] = {1, 3, 4};  // Nodo 0
        adjacencyList[1] = {0, 2, 4};
        adjacencyList[2] = {1, 4, 5};
        adjacencyList[3] = {0, 4, 6};
        adjacencyList[4] = {0, 1, 2, 3, 5, 6, 7 ,8};
        adjacencyList[5] = {2, 4, 8};  // Nodo 5 (Inicialmente blanca)
        adjacencyList[6] = {3 ,4 ,7, 10, 14, 15, 16};
        adjacencyList[7] = {4, 6, 8, 16};
        adjacencyList[8] = {4, 5, 7, 11, 16, 17, 18};
        adjacencyList[9] = {10, 13, 14};
        adjacencyList[10] = {6, 9 , 14}; 
        adjacencyList[11] = {8, 12, 18}; 
        adjacencyList[12] = {11, 18, 19};
        adjacencyList[13] = {9,14, 20};
        adjacencyList[14] = {6, 9, 10, 13, 15, 20, 21, 22}; 
        adjacencyList[15] = {6, 14, 16, 22};
        adjacencyList[16] = {6, 7, 8, 15, 17, 22, 23, 24};
        adjacencyList[17] = {8, 16, 18, 24};
        adjacencyList[18] = {8, 11, 12, 17, 19, 24, 25, 26};
        adjacencyList[19] = {12, 18, 26};
        adjacencyList[20] = {13, 14, 21};
        adjacencyList[21] = {14, 20, 22};
        adjacencyList[22] = {14, 15, 16, 21, 23, 27, 28};
        adjacencyList[23] = {16, 22, 24, 28};
        adjacencyList[24] = {16, 17, 18, 23, 25, 28, 29};
        adjacencyList[25] = {18, 24, 26};
        adjacencyList[26] = {18, 19, 25};
        adjacencyList[27] = {22, 28, 30};
        adjacencyList[28] = {22, 23, 24, 27, 29, 30, 31, 32};
        adjacencyList[29] = {24, 28, 32}; 
        adjacencyList[30] = {27, 28, 31}; 
        adjacencyList[31] = {28, 30, 32}; 
        adjacencyList[32] = {28, 29, 31};

        // Inicializar los vecinos de cada nodo basado en la lista de adyacencia
        for (int i = 0; i < nodeCount; i++) {
            for (int vecino : adjacencyList[i]) {
                nodos[i]->vecinos.append(nodos[vecino]);
            }
        }

        // Inicializar el nodo 0 con ficha negra y el nodo 5 con ficha blanca
        nodos[3]->ficha = Ficha(Negro);
        nodos[5]->ficha = Ficha(Negro);

        for (int i = 9; i <= 32; ++i) {
            nodos[i]->ficha = Ficha(Blanco);
        }
        
    }

    void setNodePositions(int width, int height) {
        // Calcular posiciones de los nodos de manera responsiva
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

    // Método para manejar el clic del mouse y cambiar el estado del nodo
void mousePressEvent(QMouseEvent *event) override {
    QPoint clickPos = event->pos();

    // Intentar seleccionar o deseleccionar un nodo
    if (manejarSeleccion(clickPos)) {
        update();
        return;
    }

    // Si estamos en una cadena de saltos, solo permitir saltos válidos
    if (enCadenaDeSaltos) {
        if (comerFicha(clickPos)) {
            update();
            return; // Movimiento válido, continuar en la cadena de saltos
        }
        return; // Bloquear cualquier otro movimiento
    }

    // Verificar que el nodo seleccionado pertenece al jugador actual
    if (nodoSeleccionado && nodoSeleccionado->ficha.estado != turnoActual) {
        return; // Bloquear si no es el turno de esta ficha
    }

    // Intentar comer una ficha
    if (comerFicha(clickPos)) {
        update();
        return; // Turno continúa si se realiza un salto válido
    }

    // Intentar mover la ficha a un nodo vecino vacío (solo si no estamos en cadena de saltos)
    if (!enCadenaDeSaltos && moverFicha(clickPos)) {
        cambiarTurno();
        update();
        return;
    }

    // Si no pasa nada, deseleccionar cualquier nodo seleccionado
    nodoSeleccionado = nullptr;
    update();
}

void cambiarTurno() {
    if (!enCadenaDeSaltos) {
        // Verificar si las negras ganaron
        if (contarFichasBlancas() < 9) {
            QMessageBox::information(this, "Victoria", "¡Las Negras han ganado!");
            QApplication::quit();
            return;  // Detener el juego
        }

        // Verificar si las blancas ganaron
        if (hanGanadoLasBlancas()) {
            QMessageBox::information(this, "Victoria", "¡Las Blancas han ganado!");
            QApplication::quit();
            return;  // Detener el juego
        }

        // Cambiar turno
        turnoActual = (turnoActual == Negro) ? Blanco : Negro;
        temporizador->stop();
    } else {
        temporizador->start(); // Mantener el temporizador activo para la cadena de saltos
    }
}


bool esMovimientoDeDosEspacios(const Nodo* origen, const Nodo* destino) {
    int dx = abs(origen->posicion.x() - destino->posicion.x());
    int dy = abs(origen->posicion.y() - destino->posicion.y());
    return dx == 80 || dy == 80; // Ajusta este valor según la escala de tu tablero
}

bool manejarSeleccion(const QPoint& clickPos) {
    // Si ya hay un nodo seleccionado y se vuelve a hacer clic en él, deseleccionarlo
    if (nodoSeleccionado) {
        if (QRect(nodoSeleccionado->posicion.x() - 20, nodoSeleccionado->posicion.y() - 20, 40, 40).contains(clickPos)) {
            nodoSeleccionado = nullptr;
            return true; // Se manejó el evento
        }
    }

    // Intentar seleccionar un nodo nuevo
    for (Nodo* nodo : nodos) {
        if (QRect(nodo->posicion.x() - 20, nodo->posicion.y() - 20, 40, 40).contains(clickPos)) {
            if (nodo->ficha.estado != Vacío) {
                nodoSeleccionado = nodo;
                return true; // Se manejó el evento
            }
        }
    }

    return false; // No se manejó el evento
}

bool moverFicha(const QPoint& clickPos) {
    if (!nodoSeleccionado) return false;

    for (Nodo* vecino : nodoSeleccionado->vecinos) {
        if (QRect(vecino->posicion.x() - 20, vecino->posicion.y() - 20, 40, 40).contains(clickPos)) {
            if (vecino->ficha.estado == Vacío) {
                vecino->ficha = nodoSeleccionado->ficha;
                nodoSeleccionado->ficha = Ficha(Vacío);
                nodoSeleccionado = nullptr; // Deseleccionar después de mover
                return true; // Movimiento realizado
            }
        }
    }

    return false; // Movimiento no realizado
}

// Función para verificar si dos valores están dentro de un rango de tolerancia
bool valoresCercanos(int a, int b, int tolerancia = 2) {
    return abs(a - b) <= tolerancia;
}


bool comerFicha(const QPoint& clickPos) {
    if (!nodoSeleccionado) return false;

    // Solo fichas negras pueden comer
    if (nodoSeleccionado->ficha.estado != Negro) {
        return false;
    }

    // Recorrer los vecinos del nodo seleccionado
    for (Nodo* vecino : nodoSeleccionado->vecinos) {
        if (vecino->ficha.estado == Blanco) { // El vecino inmediato debe contener una ficha blanca
            for (Nodo* saltoVecino : vecino->vecinos) {
                // Verificar que el clic coincide con el nodo destino del salto
                if (QRect(saltoVecino->posicion.x() - 40, saltoVecino->posicion.y() - 40, 80, 80).contains(clickPos) &&
                    saltoVecino->ficha.estado == Vacío) {

                    // Calcular diferencias en posiciones
                    int dx = vecino->posicion.x() - nodoSeleccionado->posicion.x();
                    int dy = vecino->posicion.y() - nodoSeleccionado->posicion.y();
                    int saltoDx = saltoVecino->posicion.x() - vecino->posicion.x();
                    int saltoDy = saltoVecino->posicion.y() - vecino->posicion.y();

                    // Verificar que el movimiento es un salto válido (a dos espacios y sobre ficha blanca)
                    if (valoresCercanos(dx, saltoDx) && valoresCercanos(dy, saltoDy)) {
                        // Realizar el salto
                        saltoVecino->ficha = nodoSeleccionado->ficha;
                        nodoSeleccionado->ficha = Ficha(Vacío);
                        vecino->ficha = Ficha(Vacío); // Comer la ficha blanca intermedia
                        nodoSeleccionado = saltoVecino;

                        // Verificar si hay más oportunidades de comer
                        if (tieneOportunidadDeComer(nodoSeleccionado)) {
                            enCadenaDeSaltos = true; // Continuar cadena de saltos
                            temporizador->start();
                        } else {
                            enCadenaDeSaltos = false; // Finalizar cadena de saltos
                            cambiarTurno();
                        }

                        update();
                        return true;
                    }
                }
            }
        }
    }

    return false; // No se realizó un salto válido
}

bool tieneOportunidadDeComer(Nodo* nodo) {
    for (Nodo* vecino : nodo->vecinos) {
        if (vecino->ficha.estado == Blanco) { // El vecino inmediato debe contener una ficha blanca
            for (Nodo* saltoVecino : vecino->vecinos) {
                int dx = vecino->posicion.x() - nodo->posicion.x();
                int dy = vecino->posicion.y() - nodo->posicion.y();
                int saltoDx = saltoVecino->posicion.x() - vecino->posicion.x();
                int saltoDy = saltoVecino->posicion.y() - vecino->posicion.y();

                // Verificar que el salto es válido
                if (saltoVecino->ficha.estado == Vacío &&
                    valoresCercanos(dx, saltoDx) && valoresCercanos(dy, saltoDy)) {
                    return true; // Hay un salto válido disponible
                }
            }
        }
    }
    return false; // No hay saltos válidos
}





void finalizarCadenaDeSaltos() {
    temporizador->stop(); // Detener el temporizador
    enCadenaDeSaltos = false; // Finalizar la cadena de saltos
    cambiarTurno(); // Cambiar turno automáticamente
    update();
}


int contarFichasBlancas() const {
    int count = 0;
    for (Nodo* nodo : nodos) {
        if (nodo->ficha.estado == Blanco) {
            count++;
        }
    }
    return count;
}

bool hanGanadoLasBlancas() const {
    for (int i = 0; i <= 8; ++i) {
        if (nodos[i]->ficha.estado != Blanco) {
            return false;  // Si algún nodo del rango 0-8 no está ocupado por una ficha blanca, no han ganado
        }
    }
    return true;  // Todos los nodos del 0 al 8 están ocupados por fichas blancas
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
