#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int tirarDado() {
    return rand() % 6 + 1; 
}


void jugarDados(int &dinero) {
    int dadoJugador[3]; 
    int dadoCasa[3];    
    int apuesta;

    cout << "Bienvenido al Casino - Juego de Dados " <<endl;
    cout << "Tienes $" << dinero << " disponibles."<< endl;


    cout << "¿Cuánto deseas apostar? " <<endl;
    cin >> apuesta;

    
    if (apuesta > dinero || apuesta <= 0) {
        cout << "Apuesta inválida. No puedes apostar más de lo que tienes."<< endl;
        return;
    }


    for (int i = 0; i < 3; i++) {
        dadoJugador[i] = tirarDado();
        dadoCasa[i] = tirarDado();
        cout << "Ronda " << i+1 << ": " <<endl;
        cout << "Jugador sacó: " << dadoJugador[i] << endl;
        cout << "Casa sacó: " << dadoCasa[i] << endl;
    }

    
    int totalJugador = dadoJugador[0] + dadoJugador[1] + dadoJugador[2];
    int totalCasa = dadoCasa[0] + dadoCasa[1] + dadoCasa[2];

    cout << "Resultados" <<endl;
    cout << "Total jugador: " << totalJugador << endl;
    cout << "Total casa: " << totalCasa << endl;

    
    if (totalJugador > totalCasa) {
        cout << "¡Ganaste en los dados!" << endl;
        dinero += apuesta;
    } else if (totalJugador < totalCasa) {
        cout << "La casa ganó en los dados." <<endl;
        dinero -= apuesta;
    } else {
        cout << "Empate. Tu dinero no cambia." <<endl;
    }

    cout << "Tu saldo actual es: $" << dinero << endl;
}

int main() {
    srand(time(0)); 
    int dinero;

    cout << "Ingresa el monto inicial de dinero para jugar: " <<endl;
    cin >> dinero;

    if (dinero <= 0) {
        cout << "No puedes empezar sin dinero." <<endl;
        return 0;
    }

    int opcion;
    
    do {
        cout << "Casino - Juego de Dados " << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Salir" << endl;
        cout << "Elige una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                jugarDados(dinero);
                if (dinero <= 0) {
                    cout << "Te quedaste sin dinero. Fin del juego.";
                    opcion = 2;
                }
                break;
            case 2:
                cout << "Gracias por jugar. Te vas con $" << dinero << endl;
                break;
            default:
                cout << "Opción inválida.";
        }
    } while(opcion != 2);

    return 0;
}

