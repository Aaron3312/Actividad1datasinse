#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>

// Definir los tipos de tokens como una enumeración
enum class TokenType {
    Entero,
    Real,
    Asignacion,
    Variable,
    Comentario,
    Operador,
    Multiplicacion,
    Division,
    Suma,
    Resta,
    Potencia,
    ParentesisOpen,
    ParentesisCierre
};

// Clase base para un token
class Token {
public:
    TokenType type;
    std::string value;
    Token(TokenType type, const std::string& value = "") : type(type), value(value) {}
};

// Función para imprimir un token (para demostración)
void printToken(const Token& token) {
    switch (token.type) {
        case TokenType::Entero: std::cout << "Entero\t\t" << token.value << "\n"; break;
        case TokenType::Real: std::cout << "Real\t\t" << token.value << "\n"; break;
        case TokenType::Variable: std::cout << "Variable\t" << token.value << "\n"; break;
        case TokenType::Comentario: std::cout << "Comentario\t" << token.value << "\n"; break;
        case TokenType::Asignacion: std::cout << "Asignacion\t" << token.value << "\n"; break;
        case TokenType::Operador: std::cout << "Operador\t" << token.value << "\n"; break;
        case TokenType::Multiplicacion: std::cout << "Multiplicacion\t" << token.value << "\n"; break;
        case TokenType::Division: std::cout << "Division\t" << token.value << "\n"; break;
        case TokenType::Suma: std::cout << "Suma\t\t" << token.value << "\n"; break;
        case TokenType::Resta: std::cout << "Resta\t\t" << token.value << "\n"; break;
        case TokenType::Potencia: std::cout << "Potencia\t" << token.value << "\n"; break;
        case TokenType::ParentesisOpen: std::cout << "ParentesisOpen\t" << token.value << "\n"; break;
        case TokenType::ParentesisCierre: std::cout << "ParentesisCierre\t" << token.value << "\n"; break;
    }
}

// Función auxiliar para determinar si un caracter es un operador
bool isOperator(char c) {
    return c == '=' || c == '+' || c == '-' || c == '/' || c == '*' || c == '^';
}

// Función auxiliar para determinar el tipo de operador (para simplificar)
TokenType getOperatorType(char c) {
    switch (c) {
        case '=': return TokenType::Asignacion;
        case '+': return TokenType::Suma;
        case '-': return TokenType::Resta;
        case '/': return TokenType::Division;
        case '*': return TokenType::Multiplicacion;
        case '^': return TokenType::Potencia;

        default: return TokenType::Operador;
    }
}


// Función para analizar números (enteros y reales)
std::vector<Token> lexNumber(const std::string& input, size_t& pos) {
    std::string number;
    bool isReal = false;
    while (pos < input.length() && (std::isdigit(input[pos]) || input[pos] == '.')) {
        if (input[pos] == '.') {
            isReal = true;
        }
        number += input[pos++];
    }
    std::vector<Token> result;
    result.emplace_back(isReal ? TokenType::Real : TokenType::Entero, number);
    return result;
}

// Función para analizar identificadores
std::vector<Token> lexIdentifier(const std::string& input, size_t& pos) {
    std::string identifier;
    while (pos < input.length() && (std::isalpha(input[pos]) || std::isdigit(input[pos]))) {
        identifier += input[pos++];
    }
    std::vector<Token> result;
    result.emplace_back(TokenType::Variable, identifier);
    return result;
}

// Función principal del lexer
std::vector<Token> lexer(const std::string& input) {
    std::vector<Token> tokens;
    for (size_t pos = 0; pos < input.length();) {
        if (std::isspace(input[pos])) {
            ++pos; // Ignorar espacios en blanco
        } else if (std::isdigit(input[pos]) || (input[pos] == '-' && std::isdigit(input[pos + 1]))) {
            auto numberTokens = lexNumber(input, pos);
            tokens.insert(tokens.end(), numberTokens.begin(), numberTokens.end());
        } else if (std::isalpha(input[pos])) {
            auto identifierTokens = lexIdentifier(input, pos);
            tokens.insert(tokens.end(), identifierTokens.begin(), identifierTokens.end());
        } else if (isOperator(input[pos])) {
            tokens.emplace_back(getOperatorType(input[pos]), std::string(1, input[pos]));
            ++pos;
        } else if (input[pos] == '(') {
            tokens.emplace_back(TokenType::ParentesisOpen, "(");
            ++pos;
        } else if (input[pos] == ')') {
            tokens.emplace_back(TokenType::ParentesisCierre, ")");
            ++pos;
        } else {
            ++pos; // Ignorar caracteres desconocidos
        }
    }
    return tokens;
}

// Función para imprimir todos los tokens
void printTokens(const std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        printToken(token);
    }
}

int main() {
    // Abre el archivo de entrada
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada." << std::endl;
        return 1;
    }

    // Leer el contenido del archivo de entrada
    std::string input((std::istreambuf_iterator<char>(inputFile)),
                      (std::istreambuf_iterator<char>()));
    inputFile.close(); // Cerrar el archivo de entrada después de leerlo

    // Procesar el contenido del archivo de entrada
    std::vector<Token> tokens = lexer(input);

    // Abre el archivo de salida
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return 1;
    }

    // Escribe los tokens al archivo de salida
    for (const auto& token : tokens) {
        // Aquí deberías convertir cada token a un string apropiado para imprimir
        // Este es un ejemplo, necesitarás adaptarlo según tu estructura y necesidades
        switch (token.type) {
            case TokenType::Entero: outputFile << "Entero\t\t\t" << token.value << "\n"; break;
            case TokenType::Real: outputFile << "Real\t\t\t" << token.value << "\n"; break;
            case TokenType::Variable: outputFile << "Variable\t\t" << token.value << "\n"; break;
            case TokenType::Comentario: outputFile << "Comentario\t\t" << token.value << "\n"; break;
            // Añade los casos para otros tipos de tokens según sea necesario
            default: outputFile << "Otro tipo de token\n"; break;
        }
    }

    outputFile.close(); // Cerrar el archivo de salida

    return 0;
}

