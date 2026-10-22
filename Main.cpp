#include <iostream>
#include <string>
#include "ArbolSplay.hpp"

std::string leerLinea(const std::string &pMensaje){
    std::cout << pMensaje;
    std::string linea;
    if (!std::getline(std::cin, linea)){
        linea = "";
    }
    return linea;
}

bool estaEnBlanco(const std::string &pTexto){
    for (int i = 0; i < (int)pTexto.size(); i++){
        if (pTexto[i] != ' ' && pTexto[i] != '\t') return false;
    }
    return true;
}

std::string leerTexto(const std::string &pMensaje){
    std::string texto = leerLinea(pMensaje);
    while (estaEnBlanco(texto) && std::cin){
        std::cout << "Este campo no puede quedar vacio." << std::endl;
        texto = leerLinea(pMensaje);
    }
    return texto;
}

bool convertirEntero(const std::string &pTexto, int &pValor){
    try {
        size_t usados = 0;
        pValor = std::stoi(pTexto, &usados);
        while (usados < pTexto.size() && (pTexto[usados] == ' ' || pTexto[usados] == '\t')) usados++;
        return usados == pTexto.size();
    } catch (...) {
        return false;
    }
}

bool convertirDecimal(const std::string &pTexto, double &pValor){
    try {
        size_t usados = 0;
        pValor = std::stod(pTexto, &usados);
        while (usados < pTexto.size() && (pTexto[usados] == ' ' || pTexto[usados] == '\t')) usados++;
        return usados == pTexto.size();
    } catch (...) {
        return false;
    }
}

int leerEntero(const std::string &pMensaje){
    int valor = 0;
    while (true){
        std::string texto = leerLinea(pMensaje);
        if (!std::cin) return 0;
        if (convertirEntero(texto, valor)) return valor;
        std::cout << "Debe ingresar un numero entero." << std::endl;
    }
}

double leerPrecio(const std::string &pMensaje){
    double valor = 0;
    while (true){
        std::string texto = leerLinea(pMensaje);
        if (!std::cin) return 0;
        if (convertirDecimal(texto, valor) && valor >= 0) return valor;
        std::cout << "Debe ingresar un precio valido (numero mayor o igual a 0)." << std::endl;
    }
}

void pausar(){
    leerLinea("\nPresione Enter para continuar...");
}

void agregarProducto(Arbol &pArbol){
    std::cout << std::endl << "Agregar producto" << std::endl;
    std::string nombre = leerTexto("Nombre: ");
    std::string categoria = leerTexto("Categoria (Muebles, Computadoras, Calzado, etc.): ");
    std::string marca = leerTexto("Marca: ");
    double precio = leerPrecio("Precio: ");
    std::string descripcion = leerTexto("Descripcion: ");

    int id = pArbol.agregar(nombre, categoria, marca, precio, descripcion);
    std::cout << "Producto agregado con el identificador " << id << "." << std::endl;
}

void eliminarProducto(Arbol &pArbol){
    std::cout << std::endl << "Eliminar producto" << std::endl;
    if (pArbol.estaVacio()){
        std::cout << "No hay productos registrados." << std::endl;
        return;
    }
    int id = leerEntero("Identificador del producto a eliminar: ");
    if (pArbol.eliminar(id)){
        std::cout << "Producto " << id << " eliminado." << std::endl;
    } else {
        std::cout << "No existe un producto con el identificador " << id << "." << std::endl;
    }
}

void modificarProducto(Arbol &pArbol){
    std::cout << std::endl << "Modificar producto" << std::endl;
    if (pArbol.estaVacio()){
        std::cout << "No hay productos registrados." << std::endl;
        return;
    }
    int id = leerEntero("Identificador del producto a modificar: ");
    Nodo *pProducto = pArbol.buscar(id);
    if (pProducto == nullptr){
        std::cout << "No existe un producto con el identificador " << id << "." << std::endl;
        return;
    }

    std::cout << std::endl << "Datos actuales:" << std::endl;
    Arbol::mostrarProducto(pProducto);
    std::cout << std::endl << "Ingrese los nuevos datos (deje vacio y presione Enter para conservar el valor actual)."
              << std::endl;

    std::string nombre = leerLinea("Nombre: ");
    if (estaEnBlanco(nombre)) nombre = pProducto->nombre();

    std::string categoria = leerLinea("Categoria: ");
    if (estaEnBlanco(categoria)) categoria = pProducto->categoria();

    std::string marca = leerLinea("Marca: ");
    if (estaEnBlanco(marca)) marca = pProducto->marca();

    double precio = pProducto->precio();
    while (true){
        std::string texto = leerLinea("Precio: ");
        if (estaEnBlanco(texto) || !std::cin) break;
        double valor = 0;
        if (convertirDecimal(texto, valor) && valor >= 0){
            precio = valor;
            break;
        }
        std::cout << "Debe ingresar un precio valido (numero mayor o igual a 0)." << std::endl;
    }

    std::string descripcion = leerLinea("Descripcion: ");
    if (estaEnBlanco(descripcion)) descripcion = pProducto->descripcion();

    pArbol.modificar(id, nombre, categoria, marca, precio, descripcion);
    std::cout << "Producto " << id << " modificado." << std::endl;
}

void menuAdministrativo(Arbol &pArbol){
    int opcion = -1;
    while (opcion != 0 && std::cin){
        std::cout << std::endl << "====== OPCIONES ADMINISTRATIVAS ======" << std::endl;
        std::cout << "1. Agregar producto" << std::endl;
        std::cout << "2. Eliminar producto" << std::endl;
        std::cout << "3. Modificar producto" << std::endl;
        std::cout << "4. Visualizar arbol splay" << std::endl;
        std::cout << "0. Volver" << std::endl;
        opcion = leerEntero("Opcion: ");

        switch (opcion){
            case 1: agregarProducto(pArbol); pausar(); break;
            case 2: eliminarProducto(pArbol); pausar(); break;
            case 3: modificarProducto(pArbol); pausar(); break;
            case 4: pArbol.mostrarArbol(); pausar(); break;
            case 0: break;
            default: std::cout << "Opcion invalida." << std::endl;
        }
    }
}

void consultarPorId(Arbol &pArbol){
    std::cout << std::endl << "Consultar por identificador" << std::endl;
    if (pArbol.estaVacio()){
        std::cout << "No hay productos registrados." << std::endl;
        return;
    }
    int id = leerEntero("Identificador: ");
    long long nanosegundos = 0;
    Nodo *pProducto = pArbol.consultarPorId(id, nanosegundos);

    if (pProducto != nullptr){
        std::cout << std::endl << "Producto encontrado (ahora es la raiz del arbol):" << std::endl;
        Arbol::mostrarProducto(pProducto);
    } else {
        std::cout << "No existe un producto con el identificador " << id << "." << std::endl;
    }
    std::cout << std::endl << "Tiempo de busqueda: " << nanosegundos << " nanosegundos ("
              << (nanosegundos / 1000000.0) << " milisegundos)." << std::endl;
}

void consultarPorCategoria(Arbol &pArbol){
    std::cout << std::endl << "Consultar por categoria" << std::endl;
    if (pArbol.estaVacio()){
        std::cout << "No hay productos registrados." << std::endl;
        return;
    }
    std::string categoria = leerTexto("Categoria: ");
    pArbol.consultarPorCategoria(categoria);
}

void menuUsuario(Arbol &pArbol){
    int opcion = -1;
    while (opcion != 0 && std::cin){
        std::cout << std::endl << "====== OPCIONES DE USUARIO ======" << std::endl;
        std::cout << "1. Consultar producto por identificador" << std::endl;
        std::cout << "2. Consultar productos por categoria (5 mas populares)" << std::endl;
        std::cout << "0. Volver" << std::endl;
        opcion = leerEntero("Opcion: ");

        switch (opcion){
            case 1: consultarPorId(pArbol); pausar(); break;
            case 2: consultarPorCategoria(pArbol); pausar(); break;
            case 0: break;
            default: std::cout << "Opcion invalida." << std::endl;
        }
    }
}

int main(){
    Arbol arbol;
    int opcion = -1;

    while (opcion != 0 && std::cin){
        std::cout << std::endl << "========= SISTEMA DE PRODUCTOS =========" << std::endl;
        std::cout << "1. Opciones administrativas" << std::endl;
        std::cout << "2. Opciones de usuario" << std::endl;
        std::cout << "0. Salir" << std::endl;
        opcion = leerEntero("Opcion: ");

        switch (opcion){
            case 1: menuAdministrativo(arbol); break;
            case 2: menuUsuario(arbol); break;
            case 0: std::cout << "Hasta luego." << std::endl; break;
            default: std::cout << "Opcion invalida." << std::endl;
        }
    }
    return 0;
}