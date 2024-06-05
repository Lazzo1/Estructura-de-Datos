#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <utility>
#include <sstream>
#include <limits>
#include <tuple>

using namespace std;

//Funciones de los arboles 

struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int k) : key(k), left(NULL), right(NULL) {}
};

struct AVLTreeNode : public TreeNode {
    int height;
    AVLTreeNode(int k) : TreeNode(k), height(1) {}
};

enum Color { RED, BLACK };

struct RBTreeNode : public TreeNode {
    Color color;
    RBTreeNode* parent;
    RBTreeNode(int k) : TreeNode(k), color(RED), parent(NULL) {}
};

// Inserción en Árbol Binario
TreeNode* insert(TreeNode* root, int key) {
    if (root == NULL) {
        return new TreeNode(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key){
        root->right = insert(root->right, key);
    }
    return root;
}

// Funciones AVL
int height(TreeNode* node) {
    if (node == NULL) return 0;
   return max(height(node->left), height(node->right)) + 1;
}

int getBalance(TreeNode* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
   static_cast<AVLTreeNode*>(y)->height = max(height(y->left), height(y->right)) + 1;
    static_cast<AVLTreeNode*>(x)->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
     static_cast<AVLTreeNode*>(x)->height = max(height(x->left), height(x->right)) + 1;
    static_cast<AVLTreeNode*>(y)->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

TreeNode* insertAVL(TreeNode* node, int key) {
    if (node == NULL) return new AVLTreeNode(key);
    if (key < node->key) {
        node->left = insertAVL(node->left, key);
    } else {
        node->right = insertAVL(node->right, key);
    }
    static_cast<AVLTreeNode*>(node)->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
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

// Funciones para Árbol Rojo-Negro
void rotateLeft(RBTreeNode*& root, RBTreeNode*& pt) {
    RBTreeNode* pt_right = static_cast<RBTreeNode*>(pt->right);
    pt->right = pt_right->left;
    if (pt->right != NULL) static_cast<RBTreeNode*>(pt->right)->parent = pt;
    pt_right->parent = pt->parent;
    if (pt->parent == NULL) root = pt_right;
    else if (pt == pt->parent->left) static_cast<RBTreeNode*>(pt->parent)->left = pt_right;
    else static_cast<RBTreeNode*>(pt->parent)->right = pt_right;
    pt_right->left = pt;
    pt->parent = pt_right;
}

void rotateRight(RBTreeNode*& root, RBTreeNode*& pt) {
    RBTreeNode* pt_left = static_cast<RBTreeNode*>(pt->left);
    pt->left = pt_left->right;
    if (pt->left != NULL)static_cast<RBTreeNode*>(pt->left)->parent = pt;
    pt_left->parent = pt->parent;
    if (pt->parent == NULL) root = pt_left;
    else if (pt == pt->parent->left) static_cast<RBTreeNode*>(pt->parent)->left = pt_left;
    else static_cast<RBTreeNode*>(pt->parent)->right = pt_left;
    pt_left->right = pt;
    pt->parent = pt_left;
}

void fixViolation(RBTreeNode*& root, RBTreeNode*& pt) {
    RBTreeNode* parent_pt = NULL;
    RBTreeNode* grand_parent_pt = NULL;
    while ((pt != root) && (pt->color != BLACK) && (static_cast<RBTreeNode*>(pt->parent)->color == RED)) {
         parent_pt = static_cast<RBTreeNode*>(pt->parent);
        grand_parent_pt = static_cast<RBTreeNode*>(pt->parent->parent);
        if (parent_pt == grand_parent_pt->left) {
            RBTreeNode* uncle_pt = static_cast<RBTreeNode*>(grand_parent_pt->right);
            if (uncle_pt != NULL && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->right) {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = static_cast<RBTreeNode*>(pt->parent);
                }
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        } else {
            RBTreeNode* uncle_pt = static_cast<RBTreeNode*>(grand_parent_pt->left);
            if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->left) {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt =  static_cast<RBTreeNode*>(pt->parent);
                }
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }
    root->color = BLACK;
}

void insertRBTree(RBTreeNode*& root, RBTreeNode*& pt) {
    if (root == NULL) {
        root = pt;
        pt->color = BLACK;
    } else {
        RBTreeNode* temp = root;
        while (true) {
            if (pt->key < temp->key) {
                if (temp->left == NULL) {
                    temp->left = pt;
                    pt->parent = static_cast<RBTreeNode*>(temp);
                    break;
                } else temp = static_cast<RBTreeNode*>(temp->left);
            } else {
                if (temp->right == NULL) {
                    temp->right = pt;
                      pt->parent = static_cast<RBTreeNode*>(temp);
                    break;
                } else temp = static_cast<RBTreeNode*>(temp->right);
            }
        }
        fixViolation(root, pt);
    }
}

// Declaración de la función generateDOTHelper
void generateDOTHelper(TreeNode* node, ofstream& outFile) {
    if (node != NULL) {
        if (node->left != NULL) {
            outFile << node->key << " -> " << node->left->key <<";\n";
            generateDOTHelper(node->left, outFile);
        }
        if (node->right != NULL) {
            outFile << node->key << " -> " << node->right->key << ";\n";
            generateDOTHelper(node->right, outFile);
        }
    }
}

// Definición de la función generateDOT
void generateDOT(TreeNode* root, ofstream& outFile) {
    outFile << "digraph finite_state_machine{\n";
    outFile << "rankdir=LR{\n";
    outFile << "node [shape = circle]{\n";
    generateDOTHelper(root, outFile);
    outFile << "}\n";
}


// Función para imprimir el árbol en formato nivel por nivel
void printLevelOrder(TreeNode* root) {
    if (root == NULL){ 
	return;
   }
   
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            TreeNode* current = q.front();
            q.pop();
            cout << current->key << " ";
            if (current->left != NULL) {
                q.push(current->left);
            }
            if (current->right != NULL) {
                q.push(current->right);
            }
    }
    cout << endl;
 } 
}

int getHeight(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
   return max(getHeight(node->left), getHeight(node->right)) + 1;
}

bool isAVL(TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (abs(leftHeight - rightHeight) > 1) {
        return false;
    }
    return isAVL(root->left) && isAVL(root->right);
}

void printTreeInfo(TreeNode* root) {
    cout << "Árbol Binario Inicial (nivel por nivel):\n";
    printLevelOrder(root);
    if (isAVL(root)) {
        cout << "El árbol es AVL.\n";
    } else {
        cout << "El árbol no es AVL.\n";
    }
}

//Funciones de grafo

// Estructura para representar el grafo
struct nodo {
    int dato;
    struct nodo* liga_vertice;
    struct nodo* liga_arista;
};

struct Arista {
    int origen, destino, peso;
};

typedef struct nodo* registro;
registro sig_ver, ant_ver, cab_ver, sig_ari, ant_ari, dir1, dir2;

// Funciones para la estructura del grafo
registro nuevo_vertice(int dat) {
    registro reg_ver = new(struct nodo);
    reg_ver->dato = dat;
    reg_ver->liga_vertice = NULL;
    reg_ver->liga_arista = NULL;
    return reg_ver;
}

void insertarVertice(int dat ) {
    ant_ver = cab_ver;
    sig_ver = cab_ver;

    while (sig_ver != NULL) {
        ant_ver = sig_ver;
        sig_ver = sig_ver->liga_vertice;
    }

    if (cab_ver == NULL) {
        cab_ver = nuevo_vertice(dat);
    }
    else {
        ant_ver->liga_vertice = nuevo_vertice(dat);
    }
    cout << "Vertice adicionado \n";
}

registro recorrer_vertice(int dat) {
    registro dir;
    dir = NULL;
    sig_ver = cab_ver;

    while (sig_ver != NULL) {
        if (sig_ver->dato == dat) {
            dir = sig_ver;
        }
        sig_ver = sig_ver->liga_vertice;
    }
    return dir;
}

registro nueva_arista(int pes) {
    registro reg_ari = new(struct nodo);
    reg_ari->dato = pes;
    reg_ari->liga_arista = NULL;
    reg_ari->liga_vertice = dir2;
    return reg_ari;
}

void insertarArista(int dato_destino, int peso) {
    ant_ari = dir1;
    sig_ari = dir1->liga_arista;

    while (sig_ari != NULL) {
        ant_ari = sig_ari;
        sig_ari = sig_ari->liga_arista;
    }

    ant_ari->liga_arista = nueva_arista(peso);
    cout << "Arista adicionada\n\n";
}

void crearGrafoDesdeMatrices(const vector<vector<vector<int>>>& listaDeMatrices) {
    for (const auto& matriz : listaDeMatrices) {
        for (const auto& fila : matriz) {
            if (fila.size() >= 2) {
                int origen = fila[0];
                int destino = fila[1];
                int peso = fila.size() == 3 ? fila[2] : 1; // Si no hay peso, se asume 1

                insertarVertice(origen);
                insertarVertice(destino);

                dir1 = recorrer_vertice(origen);
                dir2 = recorrer_vertice(destino);

                if (dir1 != NULL && dir2 != NULL) {
                    insertarArista(destino, peso);
                }
            }
        }
    }
}

void mostrarGrafo() {
    registro vertice = cab_ver;
    while (vertice != NULL) {
        cout << "Vertice " << vertice->dato << ":\n";
        registro arista = vertice->liga_arista;
        while (arista != NULL) {
            cout << "  -> " << arista->liga_vertice->dato << " (peso " << arista->dato << ")\n";
            arista = arista->liga_arista;
        }
        vertice = vertice->liga_vertice;
    }
}

void mostrarMatrices(const vector<vector<vector<int>>>& listaDeMatrices) {
    for (const auto& matriz : listaDeMatrices) {
        for (const auto& fila : matriz) {
            for (int val : fila) {
                cout << val << " ";
            }
            cout << "\n";
        }
    }
}

// Función para ingresar matrices
void ingresarMatrices(vector<vector<vector<int>>>& listaDeMatrices) {
    int numMatrices;
    cout << "Ingrese el numero de matrices: ";
    cin >> numMatrices;

    listaDeMatrices.resize(numMatrices);
    for (int i = 0; i < numMatrices; ++i) {
        int numFilas;
        cout << "Ingrese el numero de filas para la matriz " << i + 1 << ": ";
        cin >> numFilas;
        listaDeMatrices[i].resize(numFilas);

        for (int j = 0; j < numFilas; ++j) {
            int origen, destino, peso;
            cout << "Ingrese el nodo origen, nodo destino y el peso (opcional, presione 0 para usar peso 1): ";
            cin >> origen >> destino >> peso;

            if (peso == 0)
                peso = 1;

            listaDeMatrices[i][j] = {origen, destino, peso};
        }
    }
}

// Función para dibujar el grafo
void dibujarGrafo(const vector<vector<vector<int>>>& listaDeMatrices) {
    ofstream matriz;
    matriz.open("matriz.txt", ios::out | ios::app);

    if (matriz.is_open()) {
        matriz << "digraph finite_state_machine {\n";
        matriz << "    rankdir=LR;\n";
        matriz << "    node [shape = circle];\n";

        // Escribimos las aristas de cada matriz en el archivo
        for (const auto& matrizActual : listaDeMatrices) {
            for (const auto& edge : matrizActual) {
                int origen = edge[0];
                int destino = edge[1];
                int peso = edge[2];
                matriz << "    " << origen << " -> " << destino << " [label=\"" << peso << "\"];\n";
            }
        }

        matriz << "}\n";
        matriz<<"Copiar y pegar el codigo en http://www.webgraphviz.com"<<endl;
        matriz.close();
        cout << "El archivo 'matriz.txt' se ha generado correctamente.\n";
    } else {
        cerr << "No se pudo abrir el archivo para escribir.\n";
    }
}

void cargarMatricesDesdeArchivo(vector<vector<vector<int>>>& listaDeMatrices, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo\n";
        return;
    }

    listaDeMatrices.clear();
    string linea;
    while (getline(archivo, linea)) {
        vector<vector<int>> matriz;
        stringstream ss(linea);
        string fila;

        while (getline(ss, fila, ';')) {
            vector<int> valores;
            stringstream filaStream(fila);
            string valor;

            while (getline(filaStream, valor, ',')) {
                valores.push_back(stoi(valor));
            }

            matriz.push_back(valores);
        }

        listaDeMatrices.push_back(matriz);
    }

    archivo.close();
}

// Función para dibujar el grafo
void dibujarGrafo1(const vector<vector<vector<int>>>& listaDeMatrices, const string& nombreArchivoSalida) {
    ofstream matriz;
    matriz.open(nombreArchivoSalida, ios::out | ios::app);

    if (matriz.is_open()) {
        matriz << "digraph finite_state_machine {\n";
        matriz << "    rankdir=LR;\n";
        matriz << "    node [shape = circle];\n";

        // Escribimos las aristas de cada matriz en el archivo
        for (const auto& matrizActual : listaDeMatrices) {
            for (const auto& edge : matrizActual) {
                int origen = edge[0];
                int destino = edge[1];
                int peso = edge[2];
                matriz << "    " << origen << " -> " << destino << " [label=\"" << peso << "\"];\n";
            }
        }

        matriz << "}\n";
        matriz<<"Copiar y pegar el codigo en http://www.webgraphviz.com"<<endl;
        matriz.close();
        cout << "El archivo '" << nombreArchivoSalida << "' se ha generado correctamente.\n";
    } else {
        cerr << "No se pudo abrir el archivo para escribir.\n";
    }
}

// Algoritmo de Dijkstra para encontrar el camino más corto
vector<int> dijkstra(int origen, int numvertices) {
    vector<int> distancia(numvertices, numeric_limits<int>::max());
    vector<bool> visitado(numvertices, false);

    distancia[origen] = 0;

    for (int i = 0; i < numvertices - 1; ++i) {
        int minDistancia = numeric_limits<int>::max(), minIndex;

        for (int j = 0; j < numvertices; ++j) {
            if (!visitado[j] && distancia[j] <= minDistancia) {
                minDistancia = distancia[j];
                minIndex = j;
            }
        }

        visitado[minIndex] = true;

        registro verticeActual = recorrer_vertice(minIndex);
          if (verticeActual == NULL) continue;
        registro aristaActual = verticeActual->liga_arista;

        while (aristaActual != NULL) {
            int destino = aristaActual->liga_vertice->dato;
            int peso = aristaActual->dato;

            if (!visitado[destino] && distancia[minIndex] != numeric_limits<int>::max() && distancia[minIndex] + peso < distancia[destino])
                distancia[destino] = distancia[minIndex] + peso;

            aristaActual = aristaActual->liga_arista;
        }
    }

    return distancia;
}

// Función para ejecutar el algoritmo de Dijkstra y mostrar el resultado
void ejecutarDijkstra(int origen) {
	int numVertices = 0;
	registro vertice = cab_ver;
	 while (vertice != NULL) {
        numVertices = max(numVertices, vertice->dato + 1);
        vertice = vertice->liga_vertice;
    }
	
    vector<int> distancias = dijkstra(origen,numVertices);
	int numDistancias = 0;
    cout << "Distancias desde el vertice " << origen << ":\n";
    for (size_t i = 0; i < distancias.size(); ++i) {
        if (distancias[i] != numeric_limits<int>::max()){
            cout << "Vertice"<< i << ": " << distancias[i] << "\n";
             numDistancias++;
		}
	}
        cout << "Cantidad de distancias calculadas:" << numDistancias << endl;
    }
  
// Algoritmo de Floyd-Warshall para encontrar el camino más corto entre todos los pares de vértices
vector<vector<int>> floydWarshall(int numVertices) {
    vector<vector<int>> distancias(numVertices, vector<int>(numVertices, numeric_limits<int>::max()));

    for (int i = 0; i < numVertices; ++i) {
        distancias[i][i] = 0;
    }

    registro vertice = cab_ver;
    while (vertice != NULL) {
        registro arista = vertice->liga_arista;
        while (arista != NULL) {
            int u = vertice->dato;
            int v = arista->liga_vertice->dato;
            int peso = arista->dato;
            distancias[u][v] = peso;
            arista = arista->liga_arista;
        }
        vertice = vertice->liga_vertice;
    }

    for (int k = 0; k < numVertices; ++k) {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                if (distancias[i][k] != numeric_limits<int>::max() && distancias[k][j] != numeric_limits<int>::max() && distancias[i][k] + distancias[k][j] < distancias[i][j]) {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                }
            }
        }
    }

    return distancias;
}

// Función para ejecutar el algoritmo de Floyd-Warshall y mostrar el resultado
void ejecutarFloydWarshall() {
	int numVertices = 0;
	 registro vertice = cab_ver;
    while (vertice != NULL) {
        numVertices = max(numVertices, vertice->dato + 1);
        vertice = vertice->liga_vertice;
    }
	
    vector<vector<int>> distancias = floydWarshall(numVertices);
    cout << "Distancias minimas entre todos los pares de vertices:\n";
    for (size_t i = 0; i < distancias.size(); ++i) {
        for (size_t j = 0; j < distancias[i].size(); ++j) {
            if (distancias[i][j] == numeric_limits<int>::max())
                cout << "INF\t";
            else
                cout << distancias[i][j] << "\t";
        }
        cout << endl;
    }
}

// Función de ayuda para Kruskal
int find(vector<int>& parent, int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void unionSet(vector<int>& parent, vector<int>& rank, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Algoritmo de Kruskal para encontrar el árbol de expansión mínima
vector<Arista>obtenerAristas() {
    vector<Arista> aristas;
    registro vertice = cab_ver;
    while (vertice != NULL) {
        registro arista = vertice->liga_arista;
        while (arista != NULL) {
            aristas.push_back({vertice->dato, arista->liga_vertice->dato, arista->dato});
            arista = arista->liga_arista;
        }
        vertice = vertice->liga_vertice;
    }

     return aristas;
 }
 
 vector<pair<int, pair<int, int>>> kruskal(int numVertices) {
    vector<Arista> aristas = obtenerAristas();
    vector<pair<int, pair<int, int>>> MST;

    sort(aristas.begin(), aristas.end(), [](Arista a, Arista b) {
        return a.peso < b.peso;
    });

    vector<int> parent(numVertices);
    vector<int> rank(numVertices, 0);

    for (int i = 0; i < numVertices; ++i) {
        parent[i] = i;
    }

    for (auto& arista : aristas) {
        int u = arista.origen;
        int v = arista.destino;
        int peso = arista.peso;

        int rootU = find(parent, u);
        int rootV = find(parent, v);

        if (rootU != rootV) {
            MST.push_back({peso, {u, v}});
            unionSet(parent, rank, rootU, rootV);
        }
    }

    return MST;
}

    
// Función para ejecutar el algoritmo de Kruskal y mostrar el resultado
void ejecutarKruskal() {
	int numVertices = 0;
	 registro vertice = cab_ver;
	 while (vertice != NULL) {
        numVertices = max(numVertices, vertice->dato + 1);
        vertice = vertice->liga_vertice;
    }
	 
    vector<pair<int, pair<int, int>>> MST = kruskal(numVertices);
    cout << "Aristas del arbol de expansion minima (Kruskal):\n";
    for (const auto& arista : MST) {
        cout << arista.second.first << " - " << arista.second.second << " : " << arista.first << "\n";
    }
}

// Algoritmo de Prim para encontrar el árbol de expansión mínima
vector<pair<pair<int,int>,int>> prim(int numVertices) {
    vector<pair<pair<int,int>,int>> MST;
    vector<int> clave(numVertices, numeric_limits<int>::max());
    vector<int> padre(numVertices, -1);
    vector<bool> enMST(numVertices, false);

    clave[0] = 0;

    for (int i = 0; i < numVertices - 1; ++i) {
        int min = numeric_limits<int>::max(), u;

        for (int v = 0; v < numVertices; ++v) {
            if (!enMST[v] && clave[v] < min) {
                min = clave[v];
                u = v;
            }
        }

        enMST[u] = true;

        registro verticeActual = recorrer_vertice(u);
         if (verticeActual == NULL) continue;
         
        registro aristaActual = verticeActual->liga_arista;

        while (aristaActual != NULL) {
            int v = aristaActual->liga_vertice->dato;
            int peso = aristaActual->dato;

            if (!enMST[v] && peso < clave[v]) {
                clave[v] = peso;
                padre[v] = u;
            }

            aristaActual = aristaActual->liga_arista;
        }
    }

    for (int i = 1; i < numVertices; ++i) {
        MST.push_back({{padre[i], i},clave[i]});
    }

    return MST;
}

// Función para ejecutar el algoritmo de Prim y mostrar el resultado
void ejecutarPrim() {
	int numVertices = 0;
	registro vertice = cab_ver;
    while (vertice != NULL) {
        numVertices = max(numVertices, vertice->dato + 1);
        vertice = vertice->liga_vertice;
    }
	
    vector<pair<pair<int,int>,int>> MST = prim(numVertices);
    cout << "Aristas del arbol de expansion minima (Prim):\n";
    for (const auto& arista : MST) {
        cout <<"(" <<arista.first.first << " - " << arista.first.second << ") - "<<arista.second<< "\n";
    }
}


void menuPrincipal();
void menuArboles();
void menuGrafos();

int main() {
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int op;
    do {
        cout << "\n BIENVENIDO \n";
        cout << "1- Arboles \n";
        cout << "2- Grafos \n";
        cout << "3- Saliendo \n";
        cout << "Ingrese la opcion: ";
        cin >> op;
        system("cls");
        switch (op) {
            case 1:
                menuArboles();
                break;
            case 2:
                menuGrafos();
                break;
            case 3:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo.\n";
                break;
        }
    } while (op != 3);
}

void menuArboles() {
    vector<int> nodes;
    int choice;
    do {
        cout << "Menu Arboles:\n";
        cout << "1. Ingresar lista de nodos\n";
        cout << "2. Mostrar arbol inicial\n";
        cout << "3. Convertir en AVL y mostrar\n";
        cout << "4. Convertir en arbol Rojo-Negro y mostrar\n";
        cout << "5. Volver al Menú Principal\n";
        cout << "Ingrese su eleccion: ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1: {
                nodes.clear();
                int n, key;
                cout << "Ingrese el numero de nodos: ";
                cin >> n;
                for (int i = 0; i < n; ++i) {
                    cout << "Ingrese el valor del nodo " << i + 1 << ": ";
                    cin >> key;
                    nodes.push_back(key);
                }
                system("cls");
                break;
            }
            case 2: {
                TreeNode* binaryTree = NULL;
                for (int key : nodes) {
                    binaryTree = insert(binaryTree, key);
                }
                printTreeInfo(binaryTree);

                ofstream outFile("arboles.dot");
                generateDOT(binaryTree, outFile);
                outFile.close();
                cout << "Archivo arboles.dot generado para visualizacion.\n";
                break;
            }
            case 3: {
                TreeNode* avlTree = NULL;
                for (int key : nodes) {
                    avlTree = insertAVL(avlTree, key);
                }
                cout << "arbol AVL (nivel por nivel):\n";
                printLevelOrder(avlTree);

                ofstream outFile("arbolesAVL.dot");
                generateDOT(avlTree, outFile);
                outFile.close();
                cout << "Archivo arbolesAVL.dot generado para visualizacion.\n";
                break;
            }
            case 4: {
                RBTreeNode* rbTree = NULL;
                for (int key : nodes) {
                    RBTreeNode* newNode = new RBTreeNode(key);
                    insertRBTree(rbTree, newNode);
                }
                cout << "arbol Rojo-Negro (nivel por nivel):\n";
                printLevelOrder(rbTree);

                ofstream outFile("arbolesRB.dot");
                generateDOT(rbTree, outFile);
                outFile.close();
                cout << "Archivo arbolesRB.dot generado para visualizacion.\n";
                break;
            }
            case 5:
                // Volver al Menú Principal
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo.\n";
                break;
        }
    } while (choice != 5);
    system("cls");
}

void menuGrafos() {
    // Asumiendo que cab_ver, insertarVertice, recorrer_vertice, insertarArista,
    // mostrarGrafo, ingresarMatrices, dibujarGrafo, cargarMatricesDesdeArchivo,
    // ejecutarDijkstra, ejecutarFloydWarshall, ejecutarKruskal, ejecutarPrim están definidos.
    vector<vector<vector<int>>> listaDeMatrices;
    int opcion;
    do {
        cout << "\n\t.:Menu Grafos:.\n" << endl;
        cout << "1- Crear vertice" << endl;
        cout << "2- Creacion de arista" << endl;
        cout << "3- Mostrar grafo" << endl;
        cout << "4- Ingresar matrices" << endl;
        cout << "5- Mostrar matrices" << endl;
        cout << "6- Cargar matrices desde archivo" << endl;
        cout << "7- Encontrar camino mas corto" << endl;
        cout << "8- Encontrar peso minimo" << endl;
        cout << "9- Volver al Menú Principal" << endl;
        cout << "\nOpcion:";
        cin >> opcion;
        system("cls");

        switch (opcion) {
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
                }
                vertice << "digraph finite_state_machine {\n";
                vertice << "    rankdir=LR;\n";
                vertice << "    node [shape = circle];\n";
                for (int i = 0; i < n; i++) {
                    vertice << dat[i] << endl;
                }
                vertice << "}\n";
                vertice << "grafo no ponderado y no dirigido\n";
                vertice << "Copiar y pegar el codigo en http://www.webgraphviz.com\n";
                cout << "grafo no ponderado y no dirigido\n";
                cout << "Se anexo al archivo vertice.txt\n";
                vertice.close();
                break;
            }
            case 2: {
                int dato_origen, dato_destino, peso;
                int n;
                cout << "Ingrese el número de aristas: ";
                cin >> n;
                ofstream arista;
                arista.open("grafo.txt", ios::out | ios::app);
                arista << "digraph finite_state_machine {\n";
                arista << "    rankdir=LR;\n";
                arista << "    node [shape = circle];\n";
                for (int i = 0; i < n; i++) {
                    cout << "Ingrese el nodo de origen: ";
                    cin >> dato_origen;
                    cout << "Ingrese el nodo de destino: ";
                    cin >> dato_destino;
                    cout << "Ingrese el peso de la arista (opcional, presione 0 para usar peso 1): ";
                    cin >> peso;
                    if (peso == 0)
                        peso = 1;

                    dir1 = recorrer_vertice(dato_origen);
                    dir2 = recorrer_vertice(dato_destino);

                    if (dir1 == NULL || dir2 == NULL) {
                        cout << "\n\tNodo origen o destino no existen, revise\n";
                    } else {
                        insertarArista(dato_destino, peso);
                    }
                    arista << "    " << dato_origen << "->" << dato_destino << "[label=" << peso << "];\n";
                }
                arista << "}\n";
                arista << "grafo ponderado y dirigido\n";
                arista << "Copiar y pegar el codigo en http://www.webgraphviz.com\n";
                cout << "grafo ponderado y dirigido\n";
                arista.close();
                break;
            }
            case 3: {
                cout << "\nGrafo:\n";
                mostrarGrafo();
                cout << "Se anexo al archivo grafo.txt\n";
                break;
            }
            case 4:
                ingresarMatrices(listaDeMatrices);
                dibujarGrafo(listaDeMatrices);
                break;
            case 5:
                mostrarMatrices(listaDeMatrices);
                break;
            case 6: {
                string nombreArchivo;
                cout << "Ingrese el nombre del archivo: ";
                cin >> nombreArchivo;
                cargarMatricesDesdeArchivo(listaDeMatrices, nombreArchivo);
                dibujarGrafo1(listaDeMatrices, "matrizcargada.txt");
                break;
            }
            case 7: {
                int opcionAlgoritmo;
                cout << "\nSeleccione el algoritmo para encontrar el camino mas corto:\n";
                cout << "1- Dijkstra\n";
                cout << "2- Floyd-Warshall\n";
                cout << "Opcion: ";
                cin >> opcionAlgoritmo;
                switch (opcionAlgoritmo) {
                    case 1: {
                        int origen;
                        cout << "Ingrese el vértice de origen: ";
                        cin >> origen;
                        ejecutarDijkstra(origen);
                        break;
                    }
                    case 2:
                        ejecutarFloydWarshall();
                        break;
                    default:
                        cout << "Opcion no valida\n";
                }
                break;
            }
            case 8: {
                int opcionAlgoritmo;
                cout << "\nSeleccione el algoritmo para encontrar el árbol de expansión mínima:\n";
                cout << "1- Kruskal\n";
                cout << "2- Prim\n";
                cout << "Opcion: ";
                cin >> opcionAlgoritmo;
                switch (opcionAlgoritmo) {
                    case 1:
                        ejecutarKruskal();
                        break;
                    case 2:
                        ejecutarPrim();
                        break;
                    default:
                        cout << "Opcion no valida\n";
                }
                break;
            }
            case 9:
                // Volver al Menú Principal
                break;
            default:
                cout << "Opción no válida. Inténtelo de nuevo.\n";
                break;
        }
    } while (opcion != 9);
    system("cls");
}

		




