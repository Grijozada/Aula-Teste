#include <iostream>
#include <string>

using namespace std;

class SensorNivel {
private:
    string tag;
    double minimo;
    double maximo;
    double valorAtual;

public:
    // Construtor mínimo: cria sensor com valores padrão seguros
    SensorNivel(string tagSensor) {
        tag = tagSensor;
        minimo = 0.0;
        maximo = 100.0;
        valorAtual = 0.0;
    }

    // Construtor completo: permite configurar o sensor
    SensorNivel(string tagSensor, double min, double max, double valor) {
        if (min < max) {
            minimo = min;
            maximo = max;
        } else {
            minimo = 0.0;
            maximo = 100.0;
        }
        tag = tagSensor;
        valorAtual = valor;
    }

    void exibirResumo() const {
        cout << "[SensorNivel] " << tag
             << " | faixa: " << minimo << " a " << maximo
             << " | valor atual: " << valorAtual << "\n";
    }
};

class Bomba {
private:
    string tag;
    double velocidade;

public:
    // Construtor mínimo: bomba desligada
    Bomba(string tagBomba) {
        tag = tagBomba;
        velocidade = 0.0;
    }

    // Construtor completo: define velocidade inicial
    Bomba(string tagBomba, double vel) {
        tag = tagBomba;
        if (vel >= 0 && vel <= 100)
            velocidade = vel;
        else
            velocidade = 0.0;
    }

    void exibirResumo() const {
        cout << "[Bomba] " << tag
             << " | velocidade: " << velocidade << "%\n";
    }
};

class ControladorTanque {
private:
    string tag;
    double setpoint;
    double kp;

public:
    // Construtor mínimo: parâmetros padrão
    ControladorTanque(string tagControlador) {
        tag = tagControlador;
        setpoint = 0.0;
        kp = 1.0;
    }

    // Construtor completo: configura controle
    ControladorTanque(string tagControlador, double sp, double ganho) {
        tag = tagControlador;
        setpoint = sp;
        if (ganho > 0)
            kp = ganho;
        else
            kp = 1.0;
    }

    void exibirResumo() const {
        cout << "[ControladorTanque] " << tag
             << " | SP=" << setpoint
             << " | Kp=" << kp << "\n";
    }
};

int main() {
    SensorNivel sn1("LT-401");
    SensorNivel sn2("LT-402", 0.0, 5000.0, 2780.0);

    Bomba b1("P-101");
    Bomba b2("P-102", 75.0);

    ControladorTanque ct1("LIC-01");
    ControladorTanque ct2("LIC-02", 3000.0, 2.5);

    cout << "\n=== RESUMO DOS OBJETOS ===\n\n";

    sn1.exibirResumo();
    sn2.exibirResumo();

    b1.exibirResumo();
    b2.exibirResumo();

    ct1.exibirResumo();
    ct2.exibirResumo();

    return 0;
}