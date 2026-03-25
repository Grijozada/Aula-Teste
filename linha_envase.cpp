#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ================= BASE =================
class AtuadorLinha {
private:
    string tag;
    string area;

protected:
    // protegido: reutilizado pelas derivadas
    double limitarPercentual(double p) const {
        if (p < 0.0) return 0.0;
        if (p > 100.0) return 100.0;
        return p;
    }

public:
    AtuadorLinha(string t, string a) : tag(t), area(a) {}

    virtual ~AtuadorLinha() = default;

    string getTag() const { return tag; }
    string getArea() const { return area; }

    // virtual: permite que cada atuador interprete o comando de forma diferente
    virtual void aplicarReferenciaPercentual(double percentual) = 0;

    // virtual: garante polimorfismo na exibição
    virtual void exibirResumo() const = 0;
};

// ================= MOTOR =================
class MotorEsteira : public AtuadorLinha {
private:
    double frequenciaHz;

public:
    // construtor usando a base
    MotorEsteira(string tag, string area)
        : AtuadorLinha(tag, area), frequenciaHz(0.0) {}

    // converte percentual → frequência
    void aplicarReferenciaPercentual(double percentual) override {
        double p = limitarPercentual(percentual);
        frequenciaHz = (p / 100.0) * 60.0; // 0–100% → 0–60 Hz
    }

    void exibirResumo() const override {
        cout << "[MotorEsteira] " << getTag()
             << " | Area: " << getArea()
             << " | Frequencia: " << frequenciaHz << " Hz\n";
    }
};

// ================= VALVULA =================
class ValvulaDosagem : public AtuadorLinha {
private:
    double aberturaPercentual;

public:
    // construtor usando a base
    ValvulaDosagem(string tag, string area)
        : AtuadorLinha(tag, area), aberturaPercentual(0.0) {}

    // usa percentual diretamente
    void aplicarReferenciaPercentual(double percentual) override {
        aberturaPercentual = limitarPercentual(percentual);
    }

    void exibirResumo() const override {
        cout << "[ValvulaDosagem] " << getTag()
             << " | Area: " << getArea()
             << " | Abertura: " << aberturaPercentual << "%\n";
    }
};

// ================= MAIN =================
int main() {

    // criando objetos
    MotorEsteira motor("M-01", "Linha Envase");
    ValvulaDosagem valvula("V-01", "Linha Envase");

    // vetor polimórfico
    vector<AtuadorLinha*> atuadores;
    atuadores.push_back(&motor);
    atuadores.push_back(&valvula);

    // mesmo comando para todos
    double referencia = 80.0;

    for (auto a : atuadores) {
        a->aplicarReferenciaPercentual(referencia);
    }

    // saída
    cout << "\n=== RESUMO DA LINHA ===\n";
    for (auto a : atuadores) {
        a->exibirResumo();
    }

    return 0;
}
