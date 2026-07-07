#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int sacarCarta() {
    return rand() % 11 + 1; 
}


void jugarBlackjack(int &dinero) {
    int puntajeJugador = 0, puntajeCasa = 0;
    char opcion;
    int apuesta;

    cout << "Bienvenido al Casino - Juego de Blackjack ";
    cout << "Tienes $" << dinero << " disponibles.";


    cout << "¿Cuanto deseas apostar? ";
    cin >> apuesta;


    if (apuesta > dinero || apuesta <= 0) {
        cout << "Apuesta invalida. No puedes apostar mas de lo que tienes.";
    return;
    }


    do {
        int carta = sacarCarta();
        puntajeJugador += carta;
        cout << "Sacaste una carta de valor: " << carta << endl;
        cout << "Tu puntaje actual: " << puntajeJugador << endl;

        if (puntajeJugador >= 21) break;

        cout << "¿Quieres otra carta? (s/n): ";
        cin >> opcion;
    } while(opcion == 's');


    while (puntajeCasa < 17) {
        puntajeCasa += sacarCarta();
    }

    
    cout << "Resultados"<<endl;
    cout << "Puntaje jugador: " << puntajeJugador << endl;
    cout << "Puntaje casa: " << puntajeCasa << endl;


    if ((puntajeJugador > puntajeCasa && puntajeJugador <= 21) || puntajeCasa > 21) {
        cout << "¡Ganaste el Blackjack!";
        dinero += apuesta; 
    } else if (puntajeJugador == puntajeCasa) {
        cout << "Empate. Tu dinero no cambia.";
    } else {
        cout << "Perdiste contra la casa." <<endl;
        dinero -= apuesta; 
    }

    cout << "Tu saldo actual es: $" << dinero << endl;
}

int main() {
    srand(time(0)); 
    int dinero;

    cout << "Ingresa el monto inicial de dinero para jugar: ";
    cin >> dinero;

    
    if (dinero <= 0) {
        cout << "No puedes empezar sin dinero.";
        return 0;
    }


    while (dinero > 0) {
        jugarBlackjack(dinero);

        if (dinero <= 0) {
            cout << "Te quedaste sin dinero. Fin del juego.";
            break;
        }

        char seguir;
        cout << "¿Quieres seguir jugando? (s/n): ";
        cin >> seguir;
        if (seguir != 's') {
            cout << "Gracias por jugar. Te vas con $" << dinero << endl;
            break;
        }
    }

    return 0;
}