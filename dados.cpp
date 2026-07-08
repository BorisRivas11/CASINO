#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int tirarDado() {
    return rand() % 6 + 1; 
}


void jugarDados(int & dinero) {
    int dadoJugador[3]; 
    int dadoCasa[3];    
    int apuesta;

    cout << "Bienvenido al Casino - Juego de Dados " <<endl;
    cout << "Tienes $" << dinero << " disponibles."<< endl;


    cout << "¿Cuanto deseas apostar? " <<endl;
    cin >> apuesta;

    
    if (apuesta > dinero || apuesta <= 0) {
        cout << "Apuesta invalida. No puedes apostar mas de lo que tienes."<< endl;
        return;
    }


    for (int i = 0; i < 3; i++) {
        dadoJugador[i] = tirarDado();
        dadoCasa[i] = tirarDado();
        cout << "Ronda " << i+1 << ": " <<endl;
        cout << "Jugador saco: " << dadoJugador[i] << endl;
        cout << "Casa saco: " << dadoCasa[i] << endl;
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
        cout << "La casa gano en los dados." <<endl;
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
        cout << "Elige una opcion: " <<endl;
        cout << "1. Jugar" << endl;
        cout << "2. Salir" << endl;

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
                cout << "Opcion invalida.";
        }
    } while(opcion != 2);

    return 0;
}

