#include <iostream>
#include <string>
using namespace std;

enum colores{verde,rojo,amarillo, naranja};

struct Pimiento{
    string nombre;
    int shu;
    string color;
};

Pimiento solicitarDato(){
    Pimiento unPimiento;
    int opcion;
    //cin.ignore();
    cout << "Nombre del pimiento: ";
    getline(cin, unPimiento.nombre);
    do{
        cout << "Shu: ";
        cin >> unPimiento.shu;
    } while (unPimiento.shu < 0);

    cout << "\nColor del pimiento\n" << endl;
    cout << "\t1. Verde\t" << endl;
    cout << "\t2. Rojo\t" << endl;
    cout << "\t3. Amarillo\t" << endl;
    cout << "\t4. Naranja\t" << endl;
    cout << "\tOpcion elegida: ";

    cin >> opcion;
    switch (opcion)
    {
    case 1:
        unPimiento.color = "Verde";
        break;
    case 2:
        unPimiento.color = "Rojo";
        break;
    case 3:
        unPimiento.color = "Amarillo";
        break;
    case 4:
        unPimiento.color = "Naranja";
        break;
    default:
        cout << "Opcion no valida" << endl;
        exit(0);
        break;
    }

    return unPimiento;   
}
void mostrarDato(Pimiento unPimiento){
    cout << "Nombre del pimineto: " << unPimiento.nombre << endl;
    cout << "Shu: " << unPimiento.shu << endl;
    cout << "Color: " << unPimiento.color << endl;
}

enum comparacion{menorque,mayorque,igualque};

bool comparar(Pimiento a, comparacion operador, Pimiento b){
    bool resultado = false;
    switch(operador){
        case menorque: 
            resultado = a.shu < b.shu; 
            break;
        case mayorque: 
            resultado = a.shu > b.shu; 
            break;
        case igualque: 
            resultado = a.shu == b.shu; 
            break;
        default:
        break;
    }
    return resultado;
}

typedef Pimiento T;

struct Nodo{
    T info;
    struct Nodo *izq;
    struct Nodo *der;
};
typedef struct Nodo *Arbol;

Arbol crearArbol(T x);

void asignarIzq(Arbol a, T unDato);
void asignarDer(Arbol a, T unDato);
void agregarNodo(Arbol a);
void preorden(Arbol a);
void inorden(Arbol a);
void postorden(Arbol a);
void recorrerArbol(Arbol a);
void crearPersonalizado(Arbol p);

int main(){
    cout<<"Inicializando arbol"<< endl;
    Arbol arbol = crearArbol(solicitarDato());
    
    bool continuar = true;
    do{
        int opcion = 0;
        cout << "\nMenu: \n";
        cout << "\t1. Agregar\n";
        cout << "\t2. Recorrer\n";
        cout << "\t3. Salir\n";
        cout << "\tOpcion elegida: ";
        cin >> opcion; 
        cin.ignore();
        switch(opcion){
            case 1: 
                agregarNodo(arbol); 
                break;
            case 2: 
                recorrerArbol(arbol); 
                break;
            case 3: 
                continuar = false; 
                break;
            default: 
                cout << "Opcion no valida" << endl;
            break;
        }
    }while(continuar);
    
    return 0;
}

Arbol crearArbol(T x){
    Arbol p = new Nodo;

    p->info = x;
    p->izq = NULL;
    p->der = NULL;
    return p;
}

void asignarIzq(Arbol a, T unDato){
    if(a == NULL){
        cout << "Error: arbol vacio" << endl;
    }
    else if(a->izq != NULL){
        cout << "Error: subarbol IZQ ya existe" << endl;
    }
    else{
        a->izq = crearArbol(unDato);
    }
}

void asignarDer(Arbol a, T unDato){
    if(a == NULL){
        cout << "Error: arbol vacio" << endl;
    }
    else if(a->der != NULL){
        cout << "Error: subarbol DER ya existe" << endl;
    }
    else{
        a->der = crearArbol(unDato);
    }
}

void agregarNodo(Arbol a){

    cout << "Dato a agregar:" <<endl;
    T unDato = solicitarDato();
    
    Arbol p = a;

    while(true){
        if(comparar(unDato, igualque, p->info)){
            cout << "Error: dato ya existe!" << endl;
            return;
        }
        else if(comparar(unDato, menorque, p->info)){//ir a la izquierda
            if(p->izq == NULL){
                break;
            }
            else{
                p = p->izq;
            }
        }
        else{//ir a la derecha
            if(p->der == NULL){
                break;
            }
            else{
                p = p->der;
            }
        }
    }
    
    if(comparar(unDato, menorque, p->info)){
        asignarIzq(p, unDato);
    }
    else{
        asignarDer(p, unDato);
    }
}

void preorden(Arbol a){
    if (a != NULL)
    {
        if (a->info.color == "Rojo")
        {
            cout << "\n";
            mostrarDato(a->info);
            preorden(a->izq);
            preorden(a->der);
        }
    }
}
void inorden(Arbol a){
    if(a != NULL){
        inorden(a->izq);
        cout << "\n"; 
        mostrarDato(a->info);
        inorden(a->der);
    }
}
void postorden(Arbol a){
    if (a != NULL)
    {
        if (a->info.shu > 50000)
        {
            postorden(a->izq);
            postorden(a->der);
            cout << "\n";
            mostrarDato(a->info);
        }
    }
}

void recorrerArbol(Arbol a){
    cout << "\nRecorrido PRE orden:-----"; preorden(a); cout << endl;
    cout << "\nRecorrido IN orden:-----"; inorden(a); cout << endl;
    cout << "\nRecorrido POST orden:-----"; postorden(a); cout << endl;
}

