#ifndef NODO_HPP
#define NODO_HPP
#include <string>

class Nodo{
private:
   Nodo *apPadre;
   Nodo *apIzquierda;
   Nodo *apDerecha;
   int aId;
   std::string aNombre;
   std::string aCategoria;
   std::string aMarca;
   double aPrecio;
   std::string aDescripcion;
   int aConsultas;

public:
   Nodo(int pId, std::string pNombre,
        std::string pCategoria, std::string pMarca,
        double pPrecio, std::string pDescripcion);

   // Enlaces del arbol
   Nodo *Izquierda() const;
   Nodo *Derecha() const;
   Nodo *padre() const;
   void asignarIzquierda(Nodo *pNodo);
   void asignarDerecha(Nodo *pNodo);
   void asignarPadre(Nodo *pNodo);

   // Datos del producto
   int Id() const;
   std::string nombre() const;
   std::string categoria() const;
   std::string marca() const;
   double precio() const;
   std::string descripcion() const;
   int consultas() const;

   void asignarNombre(std::string pNombre);
   void asignarCategoria(std::string pCategoria);
   void asignarMarca(std::string pMarca);
   void asignarPrecio(double pPrecio);
   void asignarDescripcion(std::string pDescripcion);
   void incrementarConsultas();
};

#endif // NODO_HPP