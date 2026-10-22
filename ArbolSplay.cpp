#include "ArbolSplay.hpp"
#include <iostream>
#include <chrono>

// =====================================================================
// Rotaciones
// =====================================================================
void Arbol::rotarIzquierda(Nodo *pNodo){
    Nodo *pHijoDerecho = pNodo->Derecha();
    if (pHijoDerecho == nullptr) return;

    Nodo *pHijoIzquierdo = pHijoDerecho->Izquierda();
    Nodo *pPadre = pNodo->padre();

    pNodo->asignarDerecha(pHijoIzquierdo);
    if (pHijoIzquierdo != nullptr){
        pHijoIzquierdo->asignarPadre(pNodo);
    }

    pHijoDerecho->asignarPadre(pPadre);
    if (pPadre == nullptr){
        apRaiz = pHijoDerecho;
    } else if (pPadre->Izquierda() == pNodo){
        pPadre->asignarIzquierda(pHijoDerecho);
    } else {
        pPadre->asignarDerecha(pHijoDerecho);
    }

    // Colocar el nodo original como hijo izquierdo
    pHijoDerecho->asignarIzquierda(pNodo);
    pNodo->asignarPadre(pHijoDerecho);
}

void Arbol::rotarDerecha(Nodo *pNodo){
    Nodo *pHijoIzquierdo = pNodo->Izquierda();
    if (pHijoIzquierdo == nullptr) return;

    Nodo *pHijoDerecho = pHijoIzquierdo->Derecha();
    Nodo *pPadre = pNodo->padre();

    // Conectar el subarbol con el nodo original
    pNodo->asignarIzquierda(pHijoDerecho);
    if (pHijoDerecho != nullptr){
        pHijoDerecho->asignarPadre(pNodo);
    }

    // Conectar el hijo izquierdo con el antiguo padre
    pHijoIzquierdo->asignarPadre(pPadre);
    if (pPadre == nullptr){
        apRaiz = pHijoIzquierdo;
    } else if (pPadre->Derecha() == pNodo){
        pPadre->asignarDerecha(pHijoIzquierdo);
    } else {
        pPadre->asignarIzquierda(pHijoIzquierdo);
    }

    // Colocar el nodo original como hijo derecho
    pHijoIzquierdo->asignarDerecha(pNodo);
    pNodo->asignarPadre(pHijoIzquierdo);
}

// =====================================================================
// sube pNodo hasta la raiz con zig, zig-zig y zig-zag
// =====================================================================
void Arbol::ajustarArbol(Nodo *pNodo){
    if (pNodo == nullptr) return;

    while (pNodo->padre() != nullptr){
        Nodo *pPadre = pNodo->padre();
        Nodo *pAbuelo = pPadre->padre();

        if (pAbuelo == nullptr){
           
            if (pPadre->Izquierda() == pNodo) rotarDerecha(pPadre);
            else rotarIzquierda(pPadre);
        } else if (pAbuelo->Izquierda() == pPadre && pPadre->Izquierda() == pNodo){
            
            rotarDerecha(pAbuelo);
            rotarDerecha(pPadre);
        } else if (pAbuelo->Derecha() == pPadre && pPadre->Derecha() == pNodo){
            
            rotarIzquierda(pAbuelo);
            rotarIzquierda(pPadre);
        } else if (pAbuelo->Izquierda() == pPadre && pPadre->Derecha() == pNodo){
         
            rotarIzquierda(pPadre);
            rotarDerecha(pAbuelo);
        } else {
            
            rotarDerecha(pPadre);
            rotarIzquierda(pAbuelo);
        }
    }
    apRaiz = pNodo;
}


Nodo *Arbol::buscarYAjustar(int pId){
    Nodo *pActual = apRaiz;
    Nodo *pUltimo = nullptr;

    while (pActual != nullptr){
        pUltimo = pActual;
        if (pId == pActual->Id()){
            ajustarArbol(pActual);
            return pActual;
        }
        pActual = (pId < pActual->Id()) ? pActual->Izquierda() : pActual->Derecha();
    }
    ajustarArbol(pUltimo);
    return nullptr;
}

Nodo *Arbol::maximo(Nodo *pNodo) const{
    if (pNodo == nullptr) return nullptr;
    while (pNodo->Derecha() != nullptr){
        pNodo = pNodo->Derecha();
    }
    return pNodo;
}

void Arbol::liberar(Nodo *pNodo){
    if (pNodo == nullptr) return;
    liberar(pNodo->Izquierda());
    liberar(pNodo->Derecha());
    delete pNodo;
}


std::string Arbol::normalizar(const std::string &pTexto){
    int inicio = 0;
    int fin = (int)pTexto.size() - 1;
    while (inicio <= fin && (pTexto[inicio] == ' ' || pTexto[inicio] == '\t')) inicio++;
    while (fin >= inicio && (pTexto[fin] == ' ' || pTexto[fin] == '\t')) fin--;

    std::string resultado = "";
    for (int i = inicio; i <= fin; i++){
        char c = pTexto[i];
        if (c >= 'A' && c <= 'Z') c = (char)(c - 'A' + 'a');
        resultado += c;
    }
    return resultado;
}

// =====================================================================
// Constructor / destructor
// =====================================================================
Arbol::Arbol() : apRaiz(nullptr), aSiguienteId(1) {}

Arbol::~Arbol(){
    liberar(apRaiz);
    apRaiz = nullptr;
}

bool Arbol::estaVacio() const{
    return apRaiz == nullptr;
}

// =====================================================================
// Opciones administrativas
// =====================================================================
int Arbol::agregar(std::string pNombre, std::string pCategoria, std::string pMarca,
                   double pPrecio, std::string pDescripcion){
    int nuevoId = aSiguienteId++;
    Nodo *pNuevo = new Nodo(nuevoId, pNombre, pCategoria, pMarca, pPrecio, pDescripcion);

    if (apRaiz == nullptr){
        apRaiz = pNuevo;
        return nuevoId;
    }

    
    Nodo *pActual = apRaiz;
    Nodo *pPadre = nullptr;
    while (pActual != nullptr){
        pPadre = pActual;
        pActual = (nuevoId < pActual->Id()) ? pActual->Izquierda() : pActual->Derecha();
    }
    pNuevo->asignarPadre(pPadre);
    if (nuevoId < pPadre->Id()) pPadre->asignarIzquierda(pNuevo);
    else pPadre->asignarDerecha(pNuevo);

    // El nodo insertado sube a la raiz
    ajustarArbol(pNuevo);
    return nuevoId;
}

bool Arbol::eliminar(int pId){
    if (estaVacio()) return false;

    Nodo *pBorrar = buscarYAjustar(pId);// si existe, queda en la raiz
    if (pBorrar == nullptr) return false;

    Nodo *pIzquierdo = pBorrar->Izquierda();
    Nodo *pDerecho = pBorrar->Derecha();
    if (pIzquierdo != nullptr) pIzquierdo->asignarPadre(nullptr);
    if (pDerecho != nullptr) pDerecho->asignarPadre(nullptr);
    delete pBorrar;

    if (pIzquierdo == nullptr){
        apRaiz = pDerecho;
    } else {
        // Se sube el mayor del subarbol izquierdo y se le cuelga el derecho
        apRaiz = pIzquierdo;
        Nodo *pMayor = maximo(pIzquierdo);
        ajustarArbol(pMayor);// ahora pMayor es raiz y no tiene hijo derecho
        pMayor->asignarDerecha(pDerecho);
        if (pDerecho != nullptr) pDerecho->asignarPadre(pMayor);
    }
    return true;
}

Nodo *Arbol::buscar(int pId){
    if (estaVacio()) return nullptr;
    return buscarYAjustar(pId);
}

bool Arbol::modificar(int pId, std::string pNombre, std::string pCategoria,
                      std::string pMarca, double pPrecio, std::string pDescripcion){
    Nodo *pNodo = buscar(pId);
    if (pNodo == nullptr) return false;

    // El id no se modifica, asi el orden del arbol se mantiene
    pNodo->asignarNombre(pNombre);
    pNodo->asignarCategoria(pCategoria);
    pNodo->asignarMarca(pMarca);
    pNodo->asignarPrecio(pPrecio);
    pNodo->asignarDescripcion(pDescripcion);
    return true;
}

// =====================================================================
// Visualizacion del arbol
// =====================================================================
int Arbol::altura(Nodo *pNodo) const{
    if (pNodo == nullptr) return 0;
    int alturaIzq = altura(pNodo->Izquierda());
    int alturaDer = altura(pNodo->Derecha());
    return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);
}


void Arbol::mostrarLateral(Nodo *pNodo, int pNivel) const{
    if (pNodo == nullptr) return;

    mostrarLateral(pNodo->Derecha(), pNivel + 1);

    for (int i = 0; i < pNivel; i++){
        std::cout << "        ";
    }
    if (pNivel == 0){
        std::cout << "[RAIZ] " << pNodo->Id() << std::endl;
    } else {
        std::cout << "|-- " << pNodo->Id() << std::endl;
    }

    mostrarLateral(pNodo->Izquierda(), pNivel + 1);
}

void Arbol::mostrarNivel(Nodo *pNodo, int pNivelActual, int pNivelObjetivo) const{
    if (pNodo == nullptr) return;
    if (pNivelActual == pNivelObjetivo){
        std::cout << pNodo->Id() << "  ";
        return;
    }
    mostrarNivel(pNodo->Izquierda(), pNivelActual + 1, pNivelObjetivo);
    mostrarNivel(pNodo->Derecha(), pNivelActual + 1, pNivelObjetivo);
}

//usando std::cout
void Arbol::mostrarArbol() const{
    if (estaVacio()){
        std::cout << "El arbol esta vacio." << std::endl;
        return;
    }

    std::cout << std::endl << "--- Arbol Splay (raiz a la izquierda, derecha arriba, izquierda abajo) ---"
              << std::endl << std::endl;
    mostrarLateral(apRaiz, 0);

    std::cout << std::endl << "--- Identificadores por nivel ---" << std::endl;
    int totalNiveles = altura(apRaiz);
    for (int nivel = 0; nivel < totalNiveles; nivel++){
        if (nivel == 0) std::cout << "Nivel 0 (raiz): ";
        else std::cout << "Nivel " << nivel << ": ";
        mostrarNivel(apRaiz, 0, nivel);
        std::cout << std::endl;
    }
}

// =====================================================================
// Opciones de usuario
// =====================================================================
void Arbol::mostrarProducto(const Nodo *pNodo){
    if (pNodo == nullptr) return;
    std::cout << "  ID:          " << pNodo->Id() << std::endl;
    std::cout << "  Nombre:      " << pNodo->nombre() << std::endl;
    std::cout << "  Categoria:   " << pNodo->categoria() << std::endl;
    std::cout << "  Marca:       " << pNodo->marca() << std::endl;
    std::cout << "  Precio:      " << pNodo->precio() << std::endl;
    std::cout << "  Descripcion: " << pNodo->descripcion() << std::endl;
    std::cout << "  Consultas:   " << pNodo->consultas() << std::endl;
}


Nodo *Arbol::consultarPorId(int pId, long long &pNanosegundos){
    std::chrono::steady_clock::time_point inicio = std::chrono::steady_clock::now();

    Nodo *pEncontrado = nullptr;
    if (!estaVacio()){
        pEncontrado = buscarYAjustar(pId);
    }

    std::chrono::steady_clock::time_point fin = std::chrono::steady_clock::now();
    pNanosegundos = (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(fin - inicio).count();

    if (pEncontrado != nullptr){
        pEncontrado->incrementarConsultas();
    }
    return pEncontrado;
}


void Arbol::buscarSiguientePopular(Nodo *pNodo, const std::string &pCategoria,
                                   Nodo *pPrevio, Nodo *&pMejor) const{
    if (pNodo == nullptr) return;

    buscarSiguientePopular(pNodo->Izquierda(), pCategoria, pPrevio, pMejor);

    if (normalizar(pNodo->categoria()) == pCategoria){
        bool vaDespues = (pPrevio == nullptr) ||
                         pNodo->consultas() < pPrevio->consultas() ||
                         (pNodo->consultas() == pPrevio->consultas() && pNodo->Id() > pPrevio->Id());

        bool esMejor = (pMejor == nullptr) ||
                       pNodo->consultas() > pMejor->consultas() ||
                       (pNodo->consultas() == pMejor->consultas() && pNodo->Id() < pMejor->Id());

        if (vaDespues && esMejor){
            pMejor = pNodo;
        }
    }

    buscarSiguientePopular(pNodo->Derecha(), pCategoria, pPrevio, pMejor);
}


void Arbol::consultarPorCategoria(std::string pCategoria) const{
    std::string categoria = normalizar(pCategoria);
    Nodo *pPrevio = nullptr;
    int mostrados = 0;

    for (int posicion = 1; posicion <= 5; posicion++){
        Nodo *pMejor = nullptr;
        buscarSiguientePopular(apRaiz, categoria, pPrevio, pMejor);

        if (pMejor == nullptr) break;// ya no hay mas productos en la categoria

        if (posicion == 1){
            std::cout << std::endl << "Productos mas populares de \"" << pCategoria << "\":" << std::endl;
        }
        std::cout << std::endl << "#" << posicion << std::endl;
        mostrarProducto(pMejor);

        pPrevio = pMejor;
        mostrados++;
    }

    if (mostrados == 0){
        std::cout << "No hay productos en la categoria \"" << pCategoria << "\"." << std::endl;
    }
}