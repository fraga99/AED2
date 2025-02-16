#include <stdio.h>
#include <string.h>

#define HASH_SIZE 41  // Um número primo maior que 36 para minimizar colisões

// Estrutura para mapear caracteres para código Morse
typedef struct {
    char character;
    char *morse;
    int occupied;  // Indica se a posição está ocupada
} MorseCode;

// Tabela hash com endereçamento aberto
MorseCode hashTable[HASH_SIZE];

// Função hash simples
int hashFunction(char character) {
    return (character * 31) % HASH_SIZE;
}

// Inserção na tabela hash usando sondagem linear
void insertHash(char character, char *morse) {
    int index = hashFunction(character);
    while (hashTable[index].occupied) {
        index = (index + 1) % HASH_SIZE; // Sondagem linear
    }
    hashTable[index].character = character;
    hashTable[index].morse = morse;
    hashTable[index].occupied = 1;
}

// Busca na tabela hash usando sondagem linear
const char* getMorse(char character) {
    int index = hashFunction(character);
    while (hashTable[index].occupied) {
        if (hashTable[index].character == character) {
            return hashTable[index].morse;
        }
        index = (index + 1) % HASH_SIZE; // Sondagem linear
    }
    return ""; // Retorna string vazia para caracteres inválidos
}

// Inicializa a tabela hash com os valores do código Morse
void initializeHashTable() {
    char *morseCodes[100] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--..", // Letras a-z
        "-----", ".----", "..---", "...--", "....-", ".....", // Números 0-9
        "-·-·--", "·-··-·", "···-··-", "·-···", "-·--·", "-·--·-", "··--·-", "·-·-·", "-···-", "-····-", // Símbolos especiais
        "---···", "-·-·-·", "·--·-·", "·----·", "--··--", "·-·-·-", "-··-·", "··--··" // Outros símbolos
    };
    
    // Mapear letras
    for (int i = 0; i < 26; i++) {
        insertHash('a' + i, morseCodes[i]);
    }
    
    // Mapear números
    for (int i = 0; i < 10; i++) {
        insertHash('0' + i, morseCodes[26 + i]);
    }

    // Mapear símbolos especiais
    char specialChars[20] = {'?', '"', ';', '!', '+', '@', '=', '&', '#', '$', '_', '/', '{', '}', ',', ':', '(', ')'};
    for (int i = 0; i < 20; i++) {
        insertHash(specialChars[i], morseCodes[36 + i]);
    }
}

int main() {
    initializeHashTable();
    
    char palavra[100];
    printf("Digite uma palavra, número ou símbolo: ");
    scanf("%s", palavra);
    
    printf("Código Morse: ");
    for (int i = 0; i < strlen(palavra); i++) {
        const char *morse = getMorse(palavra[i]);
        if (*morse) {
            printf("%s ", morse);
        }
    }
    printf("\n");
    
    return 0;
}
