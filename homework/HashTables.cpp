#include <vector>
#include <string>

using namespace std;

// Nodo de la lista enlazada para manejar colisiones
template<typename T>
struct Nodo {
    T data;
    Nodo* next;

    Nodo(T d) : data(d), next(nullptr) {}
};

// Lista enlazada para manejar colisiones
template<typename T>
class List {
private:
    Nodo<T>* head;

public:
    List() : head(nullptr) {}

    // Insertar si no existe (evitar duplicados)
    bool insert(T value) {
        Nodo<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {  // Si el valor ya existe (transformación Morse)
                return false;  // No se inserta de nuevo
            }
            current = current->next;
        }
        // Insertar un nuevo nodo al frente
        Nodo<T>* newNode = new Nodo<T>(value);
        newNode->next = head;
        head = newNode;
        return true;  // Se inserta con éxito
    }

    // Destructor para liberar memoria
    ~List() {
        Nodo<T>* current = head;
        while (current != nullptr) {
            Nodo<T>* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Tabla Hash con chaining
template<typename T>
class HashTable {
private:
    vector<List<T>> table;
    int capacity;

    // Función hash simple basada en el módulo
    int hashFunction(T key) {
        int hashValue = 0;
        for (char ch : key) {
            hashValue = (hashValue + ch) % capacity;  // Suma los caracteres y aplica módulo
        }
        return hashValue;
    }

public:
    // Constructor
    HashTable(int cap) : capacity(cap) {
        table.resize(capacity);
    }

    // Insertar si no existe (para evitar duplicados)
    bool insert(T value) {
        int index = hashFunction(value);
        return table[index].insert(value);
    }
};

class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        // Mapeo del código Morse para cada letra del alfabeto
        vector<string> morseCode = {
            ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
            ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
            "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
        };

        // Crear la tabla hash con capacidad 100 para almacenar las transformaciones Morse
        HashTable<string> hashTable(100);
        int uniqueCount = 0;

        // Insertar las transformaciones Morse en la tabla hash y contar las únicas
        for (const string& word : words) {
            string morse = "";
            for (char ch : word) {
                morse += morseCode[ch - 'a'];  // Convertir la palabra en Morse
            }
            if (hashTable.insert(morse)) {  // Solo incrementamos si la transformación es nueva
                uniqueCount++;
            }
        }

        return uniqueCount;  // Devolvemos el número de transformaciones Morse únicas
    }
};


#include <vector>
#include <string>
#include <algorithm>  // Para sort()
using namespace std;

// Nodo de la lista enlazada para manejar colisiones
template<typename T>
struct Nodo {
    T data;
    Nodo* next;

    Nodo(T d) : data(d), next(nullptr) {}
};

// Lista enlazada para manejar colisiones
template<typename T>
class List {
private:
    Nodo<T>* head;

public:
    List() : head(nullptr) {}

    // Insertar siempre al principio
    void insert(T value) {
        Nodo<T>* newNode = new Nodo<T>(value);
        newNode->next = head;
        head = newNode;
    }

    // Obtener todos los elementos de la lista
    vector<T> getElements() {
        vector<T> elements;
        Nodo<T>* current = head;
        while (current != nullptr) {
            elements.push_back(current->data);
            current = current->next;
        }
        return elements;
    }

    // Destructor para liberar memoria
    ~List() {
        Nodo<T>* current = head;
        while (current != nullptr) {
            Nodo<T>* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Tabla hash con chaining
template<typename K, typename V>
class HashTable {
private:
    vector<List<V>> table;
    int capacity;

    // Función hash que convierte la clave (cadena ordenada) en un índice
    int hashFunction(K key) {
        int hashValue = 0;
        for (char ch : key) {
            hashValue = (hashValue + ch) % capacity;  // Suma los caracteres y aplica módulo
        }
        return hashValue;
    }

public:
    // Constructor
    HashTable(int cap) : capacity(cap) {
        table.resize(capacity);
    }

    // Insertar el valor en la tabla hash con la clave ordenada
    void insert(K key, V value) {
        int index = hashFunction(key);
        table[index].insert(value);
    }

    // Obtener todos los grupos de anagramas
    vector<vector<V>> getAnagramGroups() {
        vector<vector<V>> result;
        for (List<V>& list : table) {
            vector<V> group = list.getElements();
            if (!group.empty()) {
                result.push_back(group);
            }
        }
        return result;
    }
};

// Solución para LeetCode
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // Crear la tabla hash con capacidad 100
        HashTable<string, string> hashTable(100);

        // Iterar sobre cada palabra en strs
        for (const string& word : strs) {
            string sortedWord = word;
            sort(sortedWord.begin(), sortedWord.end());  // Ordenar la palabra para que los anagramas tengan la misma clave
            hashTable.insert(sortedWord, word);  // Insertar la palabra en la tabla hash con la clave ordenada
        }

        // Obtener los grupos de anagramas desde la tabla hash
        return hashTable.getAnagramGroups();
    }
};
