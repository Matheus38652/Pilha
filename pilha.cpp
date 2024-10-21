#include <iostream>
using namespace std;
typedef int TIPOCHAVE;

class REGISTRO{
public:
	TIPOCHAVE chave;
	// outros campos aqui
};

class ELEMENTO {
public:
	REGISTRO reg;
	ELEMENTO *prox;
};


class PilhaDin{
private:
	ELEMENTO *topo;
public:

	PilhaDin(){topo = NULL;}

	int tamanhoPilha(){
		ELEMENTO *ender = topo;
		int tam = 0;
		while (ender != nullptr){
			tam++;
			ender = ender->prox;
		}
		return tam;
	}

	bool estaVazia(){return topo == NULL;}

	void listaPilha(){
		ELEMENTO *ender = topo;
		cout << "\nPilha [";
		while (ender != nullptr){
			cout << ender->reg.chave<<" ";
			ender = ender->prox;
		}
		cout << "]\n";
	}

	bool pushElemPilha(REGISTRO reg){
		ELEMENTO *novo = new ELEMENTO(); //(PONT)malloc(sizeof(ELEMENTO));
		novo->reg = reg;
		novo->prox = topo;
		topo = novo;
		return true;
	}


	bool popElemPilha(REGISTRO reg){
		if (topo  == nullptr) return false;
		reg = topo->reg;
		ELEMENTO *apagar = topo;
		topo = topo->prox;
		delete (apagar);
		return true;
	}

	void reinicializaPilha(){
		ELEMENTO * apagar;
		ELEMENTO *posicao = topo;
		while (posicao != nullptr){
			apagar = posicao;
			posicao = posicao->prox;
			delete (apagar);
		}
		topo = nullptr;
	}
};
int main() {
	PilhaDin p;
	REGISTRO r;
	r.chave = 10;
	p.pushElemPilha(r);
	r.chave = 20;
	p.pushElemPilha(r);
	r.chave = 30;
	p.pushElemPilha(r);
	p.listaPilha();
	if (p.popElemPilha(r)) cout <<"removido"<<r.chave<<endl;
	cout <<"Tamanho da pilha "<<p.tamanhoPilha()<<endl;
	p.listaPilha();
	p.reinicializaPilha();
	p.listaPilha();
	return 0;
}