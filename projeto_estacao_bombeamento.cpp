#include <iostream>
#include <string>

using namespace std;

// ================= CLASSE BASE =================
class AtivoCampo {
private:
    string tag;          // private: identidade não deve ser alterada diretamente
    bool bloqueado;      // private: controle interno de segurança

protected:
    string area;         // protected: derivadas podem precisar alterar área

    void redefinirArea(string novaArea) {
        area = novaArea;
    }

public:
    // construtor base
    AtivoCampo(string novaTag, string novaArea)
        : tag(novaTag), bloqueado(false), area(novaArea) {}

    // acesso controlado
    string getTag() const {
        return tag;
    }

    bool estaBloqueado() const {
        return bloqueado;
    }

    void bloquear() {
        bloqueado = true;
    }

    void liberar() {
        bloqueado = false;
    }
};

// ================= SENSOR =================
class SensorNivel : public AtivoCampo {
private:
    double nivelAtual;   // private: estado interno do sensor
    double limiteAlto;   // private: parâmetro operacional

public:
    // construtor reaproveitando a base
    SensorNivel(string tag, string area, double limite)
        : AtivoCampo(tag, area), nivelAtual(0.0), limiteAlto(limite) {}

    // validação de atualização
    void atualizarNivel(double novoNivel) {
        if (estaBloqueado()) {
            cout << "Sensor bloqueado.\n";
            return;
        }

        if (novoNivel < 0) {
            cout << "Nivel invalido.\n";
            return;
        }

        nivelAtual = novoNivel;
    }

    // resumo
    void exibirResumo() const {
        cout << "[SensorNivel] " << getTag()
             << " | Area: " << area
             << " | Nivel: " << nivelAtual
             << " | Limite: " << limiteAlto << "\n";
    }

    // friend: acesso técnico direto (uso controlado e justificado)
    friend void inspecaoSensor(const SensorNivel& s);
};

// função friend (uso restrito para diagnóstico técnico)
void inspecaoSensor(const SensorNivel& s) {
    cout << "\n[INSPECAO TECNICA]\n";
    cout << "Nivel interno: " << s.nivelAtual << "\n";
    cout << "Limite alto: " << s.limiteAlto << "\n";
}

// ================= BOMBA =================
class BombaDosadora : public AtivoCampo {
private:
    double vazaoPercentual; // private: estado interno da bomba

public:
    // construtor usando base
    BombaDosadora(string tag, string area)
        : AtivoCampo(tag, area), vazaoPercentual(0.0) {}

    // validação de vazão
    void ajustarVazao(double v) {
        if (estaBloqueado()) {
            cout << "Bomba bloqueada.\n";
            return;
        }

        if (v < 0 || v > 100) {
            cout << "Vazao invalida.\n";
            return;
        }

        vazaoPercentual = v;
    }

    // uso de protected com controle
    void moverParaArea(string novaArea) {
        redefinirArea(novaArea);
    }

    // resumo
    void exibirResumo() const {
        cout << "[BombaDosadora] " << getTag()
             << " | Area: " << area
             << " | Vazao: " << vazaoPercentual << "%\n";
    }
};

// ================= MAIN =================
int main() {

    // criação dos objetos
    SensorNivel sensor("LT-100", "Tanque A", 2000.0);
    BombaDosadora bomba("P-100", "Tanque A");

    // atualização de estados
    sensor.atualizarNivel(1200.0);
    bomba.ajustarVazao(50.0);

    // teste de bloqueio
    bomba.bloquear();
    bomba.ajustarVazao(80.0); // não altera

    // mudança de área
    bomba.liberar();
    bomba.moverParaArea("Tanque B");

    // exibir resumo
    cout << "\n=== RESUMO DOS ATIVOS ===\n";
    sensor.exibirResumo();
    bomba.exibirResumo();

    // inspeção técnica
    inspecaoSensor(sensor);

    return 0;
}