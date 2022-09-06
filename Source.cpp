#include <iostream>

using namespace std;

class Nodo {
public:
    int dato;
    int fe;  
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int dato);
};

class ARBOL {
private:
    Nodo* raiz;
public:
    ARBOL();
    Nodo* Buscar(int dato, Nodo* raiz);
    int   ObtenerFE(Nodo* nodo);
    Nodo* rotacionIZQ(Nodo* nodo);
    Nodo* rotacionDER(Nodo* nodo);
    Nodo* rotacionLR(Nodo* nodo);
    Nodo* rotacionRL(Nodo* nodo);
    Nodo* InsertarNodo(Nodo* nuevo, Nodo* subArbol);
    void  Insertar(int dato);
    void  InOrden(Nodo* nodo);
    void  PreOrden(Nodo* nodo);
    void  PostOrden(Nodo* nodo);
    void mostrar(Nodo* nodo, int count);

    Nodo* obtenerRaiz();
};

Nodo::Nodo(int dato) {
    this->dato = dato;
    this->fe = 0;
    this->izquierdo = NULL;
    this->derecho = NULL;
}

ARBOL::ARBOL() {
    this->raiz = NULL;
}

Nodo* ARBOL::Buscar(int dato, Nodo* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    else if (raiz->dato == dato) {
        return raiz;
    }
    else if (raiz->dato < dato) {
        return Buscar(dato, raiz->derecho);
    }
    else if (raiz->dato > dato) {
        return Buscar(dato, raiz->izquierdo);
    }
}

int ARBOL::ObtenerFE(Nodo* nodo) {
    if (nodo == NULL) {
        return -1;
    }
    else {
        return nodo->fe;
    }
}

Nodo* ARBOL::rotacionIZQ(Nodo* nodo) {
    Nodo* aux = nodo->izquierdo;
    nodo->izquierdo = aux->derecho;

    aux->derecho = nodo;

    nodo->fe = max(this->ObtenerFE(nodo->izquierdo), this->ObtenerFE(nodo->derecho)) + 1;
    aux->fe = max(this->ObtenerFE(aux->izquierdo), this->ObtenerFE(aux->derecho)) + 1;

    return aux;
}

Nodo* ARBOL::rotacionDER(Nodo* nodo) {
    Nodo* aux = nodo->derecho;
    nodo->derecho = aux->izquierdo;

    aux->izquierdo = nodo;

    nodo->fe = max(this->ObtenerFE(nodo->izquierdo), this->ObtenerFE(nodo->derecho)) + 1;
    aux->fe = max(this->ObtenerFE(aux->izquierdo), this->ObtenerFE(aux->derecho)) + 1;

    return aux;
}

Nodo* ARBOL::rotacionLR(Nodo* nodo) {
    Nodo* aux;

    nodo->izquierdo = this->rotacionDER(nodo->izquierdo);
    aux = this->rotacionIZQ(nodo);

    return aux;
}

Nodo* ARBOL::rotacionRL(Nodo* nodo) {
    Nodo* aux;

    nodo->derecho = this->rotacionIZQ(nodo->derecho);
    aux = this->rotacionDER(nodo);

    return aux;
}

Nodo* ARBOL::InsertarNodo(Nodo* nuevo, Nodo* subArbol) {
    Nodo* NuPadre = subArbol;


    
    if (nuevo->dato < subArbol->dato) {
        if (subArbol->izquierdo == NULL) {
            subArbol->izquierdo = nuevo;
        }
        else {
            subArbol->izquierdo = this->InsertarNodo(nuevo, subArbol->izquierdo);

            int balance = this->ObtenerFE(subArbol->izquierdo) - this->ObtenerFE(subArbol->derecho);

            if (balance == 2) {
                if (nuevo->dato < subArbol->izquierdo->dato) {
                    NuPadre = this->rotacionIZQ(subArbol);
                }
                else {
                    NuPadre = this->rotacionLR(subArbol);
                }
            }

        }
    }
    else if (nuevo->dato > subArbol->dato) {
        if (subArbol->derecho == NULL) {
            subArbol->derecho = nuevo;
        }
        else {
            subArbol->derecho = this->InsertarNodo(nuevo, subArbol->derecho);

            int balance = this->ObtenerFE(subArbol->derecho) - this->ObtenerFE(subArbol->izquierdo);

            if (balance == 2) {
                if (nuevo->dato > subArbol->derecho->dato) {
                    NuPadre = this->rotacionDER(subArbol);
                }
                else {
                    NuPadre = this->rotacionRL(subArbol);
                }
            }
        }
    }
    else {
        cout << "Error Nodo duplicado!" << endl;
    }

    if ((subArbol->izquierdo == NULL) && (subArbol->derecho != NULL)) {
        subArbol->fe = subArbol->derecho->fe + 1;
    }
    else if ((subArbol->derecho == NULL) && (subArbol->izquierdo != NULL)) {
        subArbol->fe = subArbol->izquierdo->fe + 1;
    }
    else {
        subArbol->fe = max(this->ObtenerFE(subArbol->izquierdo), this->ObtenerFE(subArbol->derecho)) + 1;
    }
    
    return NuPadre;
}

void ARBOL::Insertar(int dato) {
    Nodo* nuevo = new Nodo(dato);

    if (this->raiz == NULL) {
        this->raiz = nuevo;
    }
    else {
        this->raiz = this->InsertarNodo(nuevo, raiz);
    }

}

void ARBOL::InOrden(Nodo* nodo) {
    if (nodo != NULL) {
        this->InOrden(nodo->izquierdo);
        cout << nodo->dato << ", ";
        this->InOrden(nodo->derecho);
    }
}

void ARBOL::PreOrden(Nodo* nodo) {
    if (nodo != NULL) {
        cout << nodo->dato << ", ";
        this->PreOrden(nodo->izquierdo);
        this->PreOrden(nodo->derecho);
    }
}

void ARBOL::PostOrden(Nodo* nodo) {
    if (nodo != NULL) {
        this->PostOrden(nodo->izquierdo);
        this->PostOrden(nodo->derecho);
        cout << nodo->dato << ", ";
    }
}

void ARBOL::mostrar(Nodo* nodo, int counter) {


    if (nodo == NULL) {
        return;
    }
    else {
        mostrar(nodo->derecho, counter + 1);
        for (int i = 0; i < counter; i++) {
            cout << "   ";
        }
        cout << nodo->dato << endl;
        mostrar(nodo->izquierdo, counter + 1);
    }

}

Nodo* ARBOL::obtenerRaiz() {
    return this->raiz;
}

int main() {

    int counter = 0;
    int A=0;
    ARBOL* arbol = new ARBOL();

    while(1){
        cout << "Inserte un dato: ";
        cin >> A;
        arbol->Insertar(A);

        cout << "\n------------------------------------------------------------" << endl;
        cout << "\nARBOL: " << endl;
        arbol->mostrar(arbol->obtenerRaiz(), counter);
        cout << "\n------------------------------------------------------------" << endl;
        cout << "\n\nPREORDEN: " << endl;
        arbol->PreOrden(arbol->obtenerRaiz());
        cout << "\n------------------------------------------------------------" << endl;
        cout << "\n\nPOSORDEN: " << endl;
        arbol->PostOrden(arbol->obtenerRaiz());
        cout << "\n------------------------------------------------------------" << endl;
        cout << "\n\nINORDEN: " << endl;
        arbol->InOrden(arbol->obtenerRaiz());
        cout << "\n------------------------------------------------------------" << endl;

    }


    return 0;
}