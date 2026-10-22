#ifndef ARBOLSPLAY_HPP
#define ARBOLSPLAY_HPP
#include <string>
#include "Nodo.hpp"

class Arbol{
private:
    Nodo *apRaiz;
    int aSiguienteId; // generador automatico de identificadores

    void rotarIzquierda(Nodo *pNodo);
    void rotarDerecha(Nodo *pNodo);
    void ajustarArbol(Nodo *pNodo);// ube pNodo a la raiz
    Nodo *buscarYAjustar(int pId);// busca y hace splay (sin contar consulta)
    Nodo *maximo(Nodo *pNodo) const;
    void liberar(Nodo *pNodo);
    void buscarSiguientePopular(Nodo *pNodo, const std::string &pCategoria,
                                Nodo *pPrevio, Nodo *&pMejor) const;
    void mostrarLateral(Nodo *pNodo, int pNivel) const;
    void mostrarNivel(Nodo *pNodo, int pNivelActual, int pNivelObjetivo) const;
    int altura(Nodo *pNodo) const;
    static std::string normalizar(const std::string &pTexto);

public:
    Arbol();
    ~Arbol();

    // Opciones administrativas
    int agregar(std::string pNombre, std::string pCategoria, std::string pMarca,
                double pPrecio, std::string pDescripcion);   // retorna el id generado
    bool eliminar(int pId);
    Nodo *buscar(int pId);   // para administracion: no cuenta como consulta
    bool modificar(int pId, std::string pNombre, std::string pCategoria,
                   std::string pMarca, double pPrecio, std::string pDescripcion);
    void mostrarArbol() const;//usando std::cout

    // Opciones de usuario
    Nodo *consultarPorId(int pId, long long &pNanosegundos);//mostrar toda la informacion del producto y queda de raiz
    //mostar el tiempo que tardo buscando
    void consultarPorCategoria(std::string pCategoria) const;// muestar los 5 mas populares

    bool estaVacio() const;
    static void mostrarProducto(const Nodo *pNodo);
};

#endif