# Grafo Interactivo

Este proyecto implementa un programa interactivo en C++ para trabajar con grafos. El usuario puede realizar varias operaciones, como agregar vértices, agregar aristas, mostrar el grafo, trabajar con matrices de adyacencia, ejecutar algoritmos para encontrar el camino más corto y el árbol de expansión mínima, entre otras.

## Estructura del Código

El código está estructurado en un bucle do-while que continuará ejecutándose hasta que el usuario seleccione la opción de salida. Cada opción del menú se implementa como un caso dentro de una declaración switch, lo que facilita la navegación y la ejecución de las diferentes funcionalidades.

```cpp
do {
    // Lógica para mostrar el menú y obtener la opción del usuario
    switch (opcion) {
        case 1:
            // Lógica para agregar vértices
            break;
        case 2:
            // Lógica para agregar aristas
            break;
        case 3:
            // Lógica para mostrar el grafo
            break;
        // Otros casos para las diferentes funcionalidades
    }
} while (opcion != 9);

```



## Funcionalidades Principales

1. **Agregar Vértices**
   - Solicita al usuario ingresar el número de vértices y los valores para cada vértice.
   - Inserta los vértices en la estructura del grafo.
   - Guarda la representación del grafo en el archivo "vertice.txt".

  ```cpp
case 1: {
    ofstream vertice;
    vertice.open("vertice.txt", ios::out | ios::app);
    int n, dat[100];
    cout << "Ingrese el numero de vertices: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "Ingrese el valor de cada vertice " << i + 1 << ": ";
        cin >> dat[i];
        insertarVertice(dat[i]);
        vertice << dat[i] << "\n"; // Guardar el vértice en el archivo
    }
    vertice.close();
    break;
}
```

![image](https://github.com/Lazzo1/Estructura-de-Datos/assets/159094513/9465d69d-9225-48d8-98b5-daf49c896a33)

2. **Agregar Aristas**
   - Solicita al usuario ingresar el número de aristas y los nodos de origen y destino para cada una.
   - Opcionalmente, el usuario puede ingresar el peso de la arista.
   - Verifica la existencia de los nodos de origen y destino en el grafo.
   - Inserta las aristas en la estructura del grafo.
   - Guarda la representación del grafo en el archivo "grafo.txt".

 ```cpp
    case 2: {
    int dato_origen, dato_destino, peso;
    int n;
    cout << "Ingrese el número de aristas: ";
    cin >> n;
    ofstream arista;
    arista.open("grafo.txt", ios::out | ios::app);
    for (int i = 0; i < n; i++) {
        cout << "Ingrese el nodo de origen: ";
        cin >> dato_origen;
        cout << "Ingrese el nodo de destino: ";
        cin >> dato_destino;
        cout << "Ingrese el peso de la arista (opcional, ingrese 0 si no tiene peso): ";
        cin >> peso;
        insertarArista(dato_origen, dato_destino, peso);
        arista << dato_origen << " " << dato_destino << " " << peso << "\n"; // Guardar la arista en el archivo
    }
    arista.close();
    break;
}

 ```

![image](https://github.com/Lazzo1/Estructura-de-Datos/assets/159094513/31dfbed8-c684-438b-bc3c-99941f4ad200)



3. **Mostrar Grafo**
   - Muestra en la consola la representación actual del grafo.

```
case 3: {
    cout << "\nGrafo:\n";
    mostrarGrafo();
    // Lógica para mostrar el grafo en la consola
    break;
}
```
![image](https://github.com/Lazzo1/Estructura-de-Datos/assets/159094513/d4be709f-7c3d-40ab-b64f-43e2f918136b)

4. **Trabajar con Matrices**
   - Permite al usuario ingresar y visualizar matrices relacionadas con el grafo.
   - Muestra las matrices ingresadas por el usuario.
   - Carga matrices desde un archivo y las visualiza.

 ```cpp
case 4: {
    // Lógica para trabajar con matrices
    vector<vector<int>> matriz;
    int n;
    cout << "Ingrese el tamaño de la matriz: ";
    cin >> n;
    matriz.resize(n, vector<int>(n));
    cout << "Ingrese los elementos de la matriz:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matriz[i][j];
        }
    }
    cout << "Matriz ingresada:\n";
    for (const auto& fila : matriz) {
        for (int elem : fila) {
            cout << elem << " ";
        }
        cout << "\n";
    }
    break;
}
```
![image](https://github.com/Lazzo1/Estructura-de-Datos/assets/159094513/cee2345e-2ddf-4696-bd4a-a56af2d34e68)
![image](https://github.com/Lazzo1/Estructura-de-Datos/assets/159094513/3293f52c-cedf-44f9-af8a-35d2470dbd2e)
![image](https://github.com/Lazzo1/Estructura-de-Datos/assets/159094513/e4c1a3e0-15eb-422b-b1a4-93e00309c671)




5. **Algoritmos sobre Grafos**
   - Permite al usuario seleccionar entre los algoritmos de Dijkstra y Floyd-Warshall para encontrar el camino más corto en el grafo. Permite al usuario seleccionar entre los algoritmos de Kruskal y Prim para encontrar el árbol de expansión mínima en el grafo.

   - Camino más corto: Dijkstra y Floyd-Warshall

 ```cpp
case 7: {
    cout << "Seleccione el algoritmo:\n";
    cout << "1. Dijkstra\n";
    cout << "2. Floyd-Warshall\n";
    int alg;
    cin >> alg;
    if (alg == 1) {
        // Lógica para ejecutar algoritmo de Dijkstra
        dijkstra();
    } else if (alg == 2) {
        // Lógica para ejecutar algoritmo de Floyd-Warshall
        floydWarshall();
    } else {
        cout << "Opción no válida\n";
    }
    break;
}
```
![image](https://github.com/Lazzo1/Estructura-de-Datos/assets/159094513/d060a3f8-1ec7-4fdb-bd43-3cb564f3beb4)

Árbol de Expansión Mínima: Kruskal y Prim

```cpp
case 8: {
    cout << "Seleccione el algoritmo:\n";
    cout << "1. Kruskal\n";
    cout << "2. Prim\n";
    int alg;
    cin >> alg;
    if (alg == 1) {
        // Lógica para ejecutar algoritmo de Kruskal
        kruskal();
    } else if (alg == 2) {
        // Lógica para ejecutar algoritmo de Prim
        prim();
    } else {
        cout << "Opción no válida\n";
    }
    break;
}
```
![image](https://github.com/Lazzo1/Estructura-de-Datos/assets/159094513/7cddc9b3-8d76-4172-9104-1b2b9307c36e)


6. **Salir del Programa**
   - Permite al usuario salir del programa.

```cpp
case 9: {
    cout << "Saliendo del programa...\n";
    break;
}
```

# Árbol Binario

#### `TreeNode`

Estructura básica para un nodo de Árbol Binario.

```cpp
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int k) : key(k), left(NULL), right(NULL) {}
};
```

## Árbol AVL
`AVLTreeNode`
Estructura para un nodo de Árbol AVL, que hereda de TreeNode y añade la información de altura.

```cpp
struct AVLTreeNode : public TreeNode {
    int height;
    AVLTreeNode(int k) : TreeNode(k), height(1) {}
};
```

## Árbol Rojo-Negro
`RBTreeNode`
Estructura para un nodo de Árbol Rojo-Negro, que hereda de TreeNode y añade la información de color y puntero al nodo padre.

```cpp
enum Color { RED, BLACK };

struct RBTreeNode : public TreeNode {
    Color color;
    RBTreeNode* parent;
    RBTreeNode(int k) : TreeNode(k), color(RED), parent(NULL) {}
};
```
## Funciones Implementadas
**Árbol Binario**
Inserción
Inserta un nuevo nodo en el Árbol Binario.

```cpp
TreeNode* insert(TreeNode* root, int key) {
    if (root == NULL) {
        return new TreeNode(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    return root;
}
```

## Árbol AVL
**Altura**
Calcula la altura de un nodo.

```cpp
int height(TreeNode* node) {
    if (node == NULL) return 0;
    return max(height(node->left), height(node->right)) + 1;
}
```

**Balance**
Obtiene el factor de balance de un nodo.

```cpp
int getBalance(TreeNode* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}
```

**Rotaciones**
Rotación derecha para balancear el árbol.

```cpp
TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    static_cast<AVLTreeNode*>(y)->height = max(height(y->left), height(y->right)) + 1;
    static_cast<AVLTreeNode*>(x)->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
```

Rotación izquierda para balancear el árbol.

```cpp
TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    static_cast<AVLTreeNode*>(x)->height = max(height(x->left), height(x->right)) + 1;
    static_cast<AVLTreeNode*>(y)->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
```
**Inserción en AVL**
Inserta un nuevo nodo en el Árbol AVL y lo balancea.

```cpp
TreeNode* insertAVL(TreeNode* node, int key) {
    if (node == NULL) return new AVLTreeNode(key);
    if (key < node->key) {
        node->left = insertAVL(node->left, key);
    } else if (key > node->key) {
        node->right = insertAVL(node->right, key);
    } else {
        return node;
    }

    static_cast<AVLTreeNode*>(node)->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
```

## Ejemplos de Uso
En el `main()` se incluyen ejemplos de cómo usar las funciones de inserción en Árbol Binario y AVL.

```cpp
int main() {
    // Ejemplo de uso de las funciones
    TreeNode* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    
    // AVL
    TreeNode* avlRoot = NULL;
    avlRoot = insertAVL(avlRoot, 10);
    avlRoot = insertAVL(avlRoot, 20);
    avlRoot = insertAVL(avlRoot, 5);

    // Aquí se pueden añadir más pruebas y usos de las funciones

    return 0;
}
```

## Consideraciones

- El código hace uso de archivos de texto para guardar la representación del grafo y las matrices asociadas.
- Utiliza funciones auxiliares para realizar operaciones específicas, como insertar vértices y aristas, y ejecutar algoritmos sobre el grafo.
