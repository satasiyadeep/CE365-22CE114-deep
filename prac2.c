#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STATES 100
#define MAX_SYMBOLS 10

int transition[MAX_STATES][MAX_SYMBOLS];

// Helper function to find the index of a symbol
int find_symbol_index(char symbols[], int num_symbols, char symbol) {
    for (int i = 0; i < num_symbols; i++) {
        if (symbols[i] == symbol) {
            return i;
        }
    }
    return -1; // Symbol not found
}
// Define the key structure
typedef struct {
    char first;
    int second;
} Key;

// Define the node for chaining
typedef struct Node {
    Key key;
    int value;
    struct Node* next;
} Node;

// Define the hash map structure
typedef struct {
    Node** buckets;
    size_t size;
} HashMap;

// Hash function
size_t hash_function(Key key, size_t size) {
    return ((size_t)key.first + key.second) % size;
}

// Create a hash map
HashMap* create_hash_map(size_t size) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->buckets = (Node**)calloc(size, sizeof(Node*));
    map->size = size;
    return map;
}

// Compare two keys
int compare_keys(Key key1, Key key2) {
    return (key1.first == key2.first && key1.second == key2.second);
}

// Insert into the hash map
void hash_map_insert(HashMap* map, Key key, int value) {
    size_t index = hash_function(key, map->size);
    Node* current = map->buckets[index];

    // Check if the key already exists
    while (current) {
        if (compare_keys(current->key, key)) {
            current->value = value; // Update value if key exists
            return;
        }
        current = current->next;
    }

    // Add a new node
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

// Get value from the hash map
int hash_map_get(HashMap* map, Key key, int* found) {
    size_t index = hash_function(key, map->size);
    Node* current = map->buckets[index];

    while (current) {
        if (compare_keys(current->key, key)) {
            *found = 1;
            return current->value;
        }
        current = current->next;
    }

    *found = 0;
    return 0; // Key not found
}

// Delete key from the hash map
void hash_map_delete(HashMap* map, Key key) {
    size_t index = hash_function(key, map->size);
    Node* current = map->buckets[index];
    Node* prev = NULL;

    while (current) {
        if (compare_keys(current->key, key)) {
            if (prev) {
                prev->next = current->next;
            } else {
                map->buckets[index] = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Free the hash map
void free_hash_map(HashMap* map) {
    for (size_t i = 0; i < map->size; i++) {
        Node* current = map->buckets[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}

// Test the hash map
int main() {
    HashMap* map = create_hash_map(8);

    int num_symbols, num_states, initial_state, num_accepting_states;
    char symbols[MAX_SYMBOLS];
    int accepting_states[MAX_STATES];

    // Input number of symbols
    printf("Enter number of input symbols: ");
    scanf("%d", &num_symbols);

    printf("Input symbols: ");
    for (int i = 0; i < num_symbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    // Input number of states
    printf("Enter number of states: ");
    scanf("%d", &num_states);

    // Input initial state
    printf("Initial state: ");
    scanf("%d", &initial_state);

    // Input number of accepting states
    printf("Number of accepting states: ");
    scanf("%d", &num_accepting_states);

    printf("Accepting states: ");
    for (int i = 0; i < num_accepting_states; i++) {
        scanf("%d", &accepting_states[i]);
    }

    // Input transition table
    printf("Transition table:\n");
    for (int i = 0; i < num_states * num_symbols; i++) {
        int from_state, to_state;
        char symbol;

        printf("From state, symbol, to state (e.g., 1 a 2): ");
        scanf("%d %c %d", &from_state, &symbol, &to_state);

        hash_map_insert(map, (Key){symbol, from_state}, to_state);
    }

    // Input string
    char input_string[100];
    printf("Input string: ");
    scanf("%s", input_string);

    int found;
    int current_state = initial_state;

    // Process the input string
    for (int i = 0; i < strlen(input_string); i++) {
        char current_symbol = input_string[i];
        current_state = hash_map_get(map, (Key){current_symbol, current_state}, &found);

        if (!found) {
            printf("Invalid String\n");
            free_hash_map(map);
            return 0;
        }
    }

    // Check if the final state is accepting
    int is_valid = 0;
    for (int i = 0; i < num_accepting_states; i++) {
        if (current_state == accepting_states[i]) {
            is_valid = 1;
            break;
        }
    }

    if (is_valid) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    free_hash_map(map);
    return 0;
}
