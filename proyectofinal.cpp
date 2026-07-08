#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// FUNCIONES DE UTILIDAD
void guardarSaldo(int saldo) {
    ofstream archivo("puntaje.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Saldo actual: " << saldo << endl;
        archivo.close();
    }
}

int pedirApuesta(int saldo) {
    int apuesta;
    cout << "Cuanto deseas apostar? ";
    cin >> apuesta;
    if (apuesta <= 0 || apuesta > saldo) {
        cout << "Apuesta invalida. Debe ser mayor que 0 y menor o igual al saldo.";
        return -1;
    }
    return apuesta;
}

// BLACKJACK

int sacarCarta() { 
    return rand() % 11 + 1; }

int turnoJugador() {
    int puntajeJugador = 0;
    char opcion;
    do {
        int carta = sacarCarta();
        puntajeJugador += carta;
        cout << "Sacaste una carta de valor: " << carta << endl;
        cout << "Tu puntaje actual: " << puntajeJugador << endl;
        if (puntajeJugador >= 21) break;
        cout << "Quieres otra carta? (s/n): ";
        cin >> opcion;
    } while(opcion == 's');
    return puntajeJugador;
}

int turnoCasa() {
    int puntajeCasa = 0;
    while (puntajeCasa < 17) {
        puntajeCasa += sacarCarta();
    }
    return puntajeCasa;
}

void blackJack(int &saldo) {
    cout << "=== BLACKJACK ==="<<endl;
    int apuesta = pedirApuesta(saldo);
    if (apuesta == -1) return;

    int puntajeJugador = turnoJugador();
    int puntajeCasa = turnoCasa();

    cout << "Resultados"<<endl;
    cout << "Puntaje jugador: " << puntajeJugador << endl;
    cout << "Puntaje casa: " << puntajeCasa << endl;

    if ((puntajeJugador > puntajeCasa && puntajeJugador <= 21) || puntajeCasa > 21) {
        cout << "Ganaste el Blackjack!"<<endl;
        saldo += apuesta;
    } else if (puntajeJugador == puntajeCasa) {
        cout << "Empate. Tu dinero no cambia."<<endl;
    } else {
        cout << "Perdiste contra la casa."<<endl;
        saldo -= apuesta;
    }
    cout << "Saldo actual: $" << saldo << endl;
    guardarSaldo(saldo);
}

// DADOS
int tirarDado() { return rand() % 6 + 1; }

void turnoDados(int dadoJugador[], int dadoCasa[]) {
    for (int i = 0; i < 3; i++) {
        dadoJugador[i] = tirarDado();
        dadoCasa[i] = tirarDado();
        cout << "Ronda " << i+1 << ": Jugador saco " << dadoJugador[i]
             << " | Casa saco " << dadoCasa[i] << endl;
    }
}

void dados(int &saldo) {
    cout << "=== JUEGO DE DADOS ==="<<endl;
    int apuesta = pedirApuesta(saldo);
    if (apuesta == -1) return;

    int dadoJugador[3], dadoCasa[3];
    turnoDados(dadoJugador, dadoCasa);

    int totalJugador = dadoJugador[0] + dadoJugador[1] + dadoJugador[2];
    int totalCasa = dadoCasa[0] + dadoCasa[1] + dadoCasa[2];

    cout << "Resultados"<<endl;
    cout << "Total jugador: " << totalJugador << endl;
    cout << "Total casa: " << totalCasa << endl;

    if (totalJugador > totalCasa) {
        cout << "Ganaste en los dados!"<<endl;
        saldo += apuesta;
    } else if (totalJugador < totalCasa) {
        cout << "La casa gano en los dados."<<endl;
        saldo -= apuesta;
    } else {
        cout << "Empate. Tu dinero no cambia."<<endl;
    }
    cout << "Saldo actual: $" << saldo << endl;
    guardarSaldo(saldo);
}

// RULETA
void ruleta(int &saldo) {
    cout << "=== RULETA ==="<<endl;
    int apuesta = pedirApuesta(saldo);
    if (apuesta == -1) return;

    int ruleta[36];
    for (int i = 0; i < 36; i++) ruleta[i] = i + 1;

    int numeroUsuario;
    cout << "Elige un numero del 1 al 36: ";
    cin >> numeroUsuario;
    while(numeroUsuario < 1 || numeroUsuario > 36) {
        cout << "Numero invalido. Intente de nuevo: ";
        cin >> numeroUsuario;
    }

    int resultado = ruleta[rand() % 36];
    cout << "La ruleta cayo en: " << resultado << endl;

    if(numeroUsuario == resultado) {
        cout << "¡Ganaste " << apuesta*5 << "!";
        saldo += apuesta*5;
    } else if(abs(numeroUsuario - resultado) <= 3) {
        cout << "¡Casi! Ganaste " << apuesta*2 << "!";
        saldo += apuesta*2;
    } else {
        cout << "Perdiste."<<endl;
        saldo -= apuesta;
    }

    if(saldo < 0) saldo = 0;
    cout << "Saldo actual: $" << saldo << endl;
    guardarSaldo(saldo);
}

// TRAGAMONEDAS
const char* simbolos[] = {"#", "$", "@", "*", "!"};
const int numSimbolos = 5;

const char* girarRodillo() {
    int indice = rand() % numSimbolos;
    return simbolos[indice];
}

int evaluarPremio(const char* r1, const char* r2, const char* r3, int apuesta) {
    if (r1 == r2 && r2 == r3) {
        cout << "¡Jackpot! Ganaste: " << apuesta * 5 << endl;
        return apuesta * 5;
    } else if (r1 == r2 || r2 == r3 || r1 == r3) {
        cout << "Ganaste " << apuesta * 2 << endl;
        return apuesta * 2;
    } else {
        cout << "Nada esta vez..."<<endl;
        return 0;
    }
}

int jugarRonda(int apuesta) {
    const char* r1 = girarRodillo();
    const char* r2 = girarRodillo();
    const char* r3 = girarRodillo();

    cout << r1 << " | " << r2 << " | " << r3 << endl;

    return evaluarPremio(r1, r2, r3, apuesta);
}

void tragamonedas(int &saldo) {
    cout << "=== TRAGAMONEDAS ==="<<endl;
    int apuesta = pedirApuesta(saldo);
    if (apuesta == -1) return;

    int premio = jugarRonda(apuesta);

    if (premio > 0) {
        saldo += premio;   
        saldo -= apuesta;  
    } else {
        saldo -= apuesta;  
    }

    if (saldo <= 0) {
        cout << "Te quedaste sin dinero. Fin del juego."<<endl;
    }
    cout << "Saldo actual: $" << saldo << endl;
    guardarSaldo(saldo);
}

// MENU PRINCIPAL
void menuCasino() {
    int opcion;
    int saldo = 100;

    do {
    
        if (saldo <= 0) {   
            cout << "Te quedaste sin dinero. Fin del juego.\n";
            guardarSaldo(saldo);
            break;         
        }

        cout << "\n========================";
        cout << "\n      CASINO ONLINE";
        cout << "\n========================";
        cout << "\n1. Black Jack";
        cout << "\n2. Tragamonedas";
        cout << "\n3. Ruleta";
        cout << "\n4. Dados";
        cout << "\n5. Salir";
        cout << "\n\nSaldo: " << saldo;
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: blackJack(saldo); break;
            case 2: tragamonedas(saldo); break;
            case 3: ruleta(saldo); break;
            case 4: dados(saldo); break;
            case 5:
                cout << "Gracias por jugar."<<endl;
                guardarSaldo(saldo);
                break;
            default:
                cout << "Opcion invalida."<<endl;
        }
    } while(opcion != 5);
}

// MAIN
int main() {
    srand(time(0));
    menuCasino();
    return 0;
}