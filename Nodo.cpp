#include "Nodo.hpp"

Nodo::Nodo(int pId, std::string pNombre,
           std::string pCategoria, std::string pMarca, double pPrecio,
           std::string pDescripcion)
    : apPadre(nullptr), apIzquierda(nullptr), apDerecha(nullptr),
      aId(pId), aNombre(pNombre), aCategoria(pCategoria), aMarca(pMarca),
      aPrecio(pPrecio), aDescripcion(pDescripcion), aConsultas(0) {}

Nodo *Nodo::Izquierda() const {
    return apIzquierda;
}
Nodo *Nodo::Derecha() const { 
    return apDerecha; 
}
Nodo *Nodo::padre() const { 
    return apPadre; 
}

void Nodo::asignarIzquierda(Nodo *pNodo) { 
    apIzquierda = pNodo; 
}
void Nodo::asignarDerecha(Nodo *pNodo) { 
    apDerecha = pNodo; 
}
void Nodo::asignarPadre(Nodo *pNodo) { 
    apPadre = pNodo; 
}

int Nodo::Id() const { 
    return aId; 
}
std::string Nodo::nombre() const { 
    return aNombre; 
}
std::string Nodo::categoria() const { 
    return aCategoria; 
}
std::string Nodo::marca() const { 
    return aMarca; 
}
double Nodo::precio() const { 
    return aPrecio;
}
std::string Nodo::descripcion() const { 
    return aDescripcion; 
}
int Nodo::consultas() const { 
    return aConsultas; 
}

void Nodo::asignarNombre(std::string pNombre) { 
    aNombre = pNombre; 
}
void Nodo::asignarCategoria(std::string pCategoria) {
    aCategoria = pCategoria; 
}
void Nodo::asignarMarca(std::string pMarca) { 
    aMarca = pMarca; 
}
void Nodo::asignarPrecio(double pPrecio) { 
    aPrecio = pPrecio; 
}
void Nodo::asignarDescripcion(std::string pDescripcion) { 
    aDescripcion = pDescripcion; 
}
void Nodo::incrementarConsultas() { 
    aConsultas++; 
}