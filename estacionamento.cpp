#include <iostream>
#include <string>
using namespace std;

typedef string TIPOCHAVE;
class REGISTRO {
public:
    TIPOCHAVE chave;
};

class ELEMENTO {
public:
    REGISTRO reg;
    ELEMENTO *prox;
};

class PilhaDin {
private:
    ELEMENTO *topo;
public:
    PilhaDin() { topo = NULL; }
    ~PilhaDin() { reinicializaPilha(); }

    int tamanhoPilha() {
        ELEMENTO *ender = topo;
        int tam = 0;
        while (ender != nullptr) {
            tam++;
            ender = ender->prox;
        }
        return tam;
    }

    bool estaVazia() { return topo == NULL; }

    void listaPilha() {
        ELEMENTO *ender = topo;
        cout << "\nPilha [";
        while (ender != nullptr) {
            cout << ender->reg.chave << " ";
            ender = ender->prox;
        }
        cout << "]\n";
    }

    bool pushElemPilha(REGISTRO reg) {
        ELEMENTO *novo = new ELEMENTO();
        novo->reg = reg;
        novo->prox = topo;
        topo = novo;
        return true;
    }

    bool popElemPilha(REGISTRO &reg) {
        if (topo == nullptr) return false;
        reg = topo->reg;
        ELEMENTO *apagar = topo;
        topo = topo->prox;
        delete (apagar);
        return true;
    }

    void reinicializaPilha() {
        ELEMENTO *apagar;
        ELEMENTO *posicao = topo;
        while (posicao != nullptr) {
            apagar = posicao;
            posicao = posicao->prox;
            delete (apagar);
        }
        topo = nullptr;
    }
};

class Estacionamento {
private:
    PilhaDin estacionamento, patio;

public:
    void entradaVeiculo(const string& placa) {
        REGISTRO reg;
        reg.chave = placa;
        estacionamento.pushElemPilha(reg);
    }

    void saidaVeiculo(const string& placa) {
        REGISTRO reg;
        while (!estacionamento.estaVazia()) {
            estacionamento.popElemPilha(reg);
            if (reg.chave == placa) break;
            patio.pushElemPilha(reg);
        }

        while (!patio.estaVazia()) {
            patio.popElemPilha(reg);
            estacionamento.pushElemPilha(reg);
        }
    }

    void mostrarEstadoAtual() {
        cout << "\nEstacionamento: ";
        estacionamento.listaPilha();
        cout << "\nPatio: ";
        patio.listaPilha();
    }
};

int main() {
    Estacionamento est;
    int opcao;
    string placa;

    do {
        cout << "Menu:\n";
        cout << "1. Entrada de Veiculo\n";
        cout << "2. Saida de Veiculo\n";
        cout << "3. Mostrar Estado Atual\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "Digite a placa do veiculo: ";
            cin >> placa;
            est.entradaVeiculo(placa);
            break;
        case 2:
            cout << "Digite a placa do veiculo: ";
            cin >> placa;
            est.saidaVeiculo(placa);
            break;
        case 3:
            est.mostrarEstadoAtual();
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);

    return 0;
}
