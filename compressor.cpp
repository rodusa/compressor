// Compressor.cpp
#include "Compressor.h"
#include <fstream>
#include <iostream>
#include <bitset>

Compressor::Compressor(const std::string &arquivoTxt, 
                       const std::string &arquivoCompactado, 
                       const std::string &arquivoDescompactado, 
                       const std::string &convertedFile,
                       const std::string &arquivoEncriptado,
                       const std::string &arquivoDesencriptado
                       ) // Add this parameter
    : arquivoTxt(arquivoTxt), 
      arquivoCompactado(arquivoCompactado), 
      arquivoDescompactado(arquivoDescompactado), 
      arquivoBinario(convertedFile),
      arquivoEncriptado(arquivoEncriptado),
      arquivoDesencriptado(arquivoDesencriptado) // Initialize the member variable
{
    construirDicionarios();
}


void Compressor::comprimirBinario()
{
    //auto dadosBinarios = lerArquivoParaBinario(arquivoTxt);
    auto dadosBinarios = lerArquivoParaBinario(arquivoEncriptado);
    
    imprimirVetor16Bits(dadosBinarios);
    auto dadosComprimidos = compressData(dadosBinarios);
    escreverComprimidoParaArquivo(dadosComprimidos, arquivoCompactado);
}

void Compressor::descomprimirBinario()
{
    auto dadosComprimidos = readarquivoCompactado(arquivoCompactado);
    auto dadosDescomprimidos = descomprimirDados(dadosComprimidos);
    escreverBinarioEmArquivo(dadosDescomprimidos, arquivoDescompactado);
}

// Dicionário mapeado para 4 bits
void Compressor::construirDicionarios()
{
    bitsDictionary["0000"] = "A";
    bitsDictionary["0001"] = "B";
    bitsDictionary["0010"] = "C";
    bitsDictionary["0011"] = "D";
    bitsDictionary["0100"] = "E";
    bitsDictionary["0101"] = "F";
    bitsDictionary["0110"] = "G";
    bitsDictionary["0111"] = "H";
    bitsDictionary["1000"] = "I";
    bitsDictionary["1001"] = "J";
    bitsDictionary["1010"] = "K";
    bitsDictionary["1011"] = "L";
    bitsDictionary["1100"] = "M";
    bitsDictionary["1101"] = "N";
    bitsDictionary["1110"] = "O";
    bitsDictionary["1111"] = "P";

    // Build the decompression dictionary
    for (const auto &pair : bitsDictionary)
    {
        debitsDictionary[pair.second] = pair.first;
    }
}

std::vector<bool> Compressor::lerArquivoParaBinario(const std::string &nomeArquivo)
{
    std::vector<bool> dadosBinarios;
    std::ifstream file(nomeArquivo, std::ios::binary);
    if (!file)
    {
        std::cerr << "Erro ao abrir arquivo para leitura: " << nomeArquivo << std::endl;
        return {};
    }
    std::cout << "Arquivo " << nomeArquivo << " foi lido com sucesso." << std::endl;

    char buffer[2]; // Lê 2 bytes ou 16 bits por vez
    while (true)
    {
        file.read(buffer, 2);
        int bytesRead = file.gcount();

        if (bytesRead == 0)
            break;

        for (int i = 0; i < bytesRead; ++i)
        {
            for (int j = 7; j >= 0; --j)
            {
                dadosBinarios.push_back((buffer[i] >> j) & 1);
            }
        }
    }

    return dadosBinarios;
}

void Compressor::escreverBinarioEmArquivo(const std::vector<bool> &dadosBinarios, const std::string &nomeArquivo)
{
    std::ofstream file(nomeArquivo, std::ios::binary);
    if (!file)
    {
        std::cerr << "Erro ao abrir arquivo para escrita: " << nomeArquivo << std::endl;
        return;
    }

    // Escreve bytes completos (8 bits)
    size_t i = 0;
    for (; i + 7 < dadosBinarios.size(); i += 8)
    {
        char c = 0;
        for (int j = 0; j < 8; ++j)
        {
            c |= dadosBinarios[i + j] << (7 - j);
        }
        file.put(c);
    }

    // Trata os bits restantes se eles não completarem um byte inteiro
    if (i < dadosBinarios.size())
    {
        char c = 0;
        int bitCount = 0;
        for (; i < dadosBinarios.size(); ++i, ++bitCount)
        {
            c |= dadosBinarios[i] << (7 - bitCount);
        }
        file.put(c);
    }
}

std::vector<std::string> Compressor::compressData(const std::vector<bool> &data)
{
    std::vector<std::string> dadosComprimidos;
    size_t index = 0;

    // Debug: Imprimir o tamanho dos dados de entrada
    std::cout << "Tamanho dos dados de entrada: " << data.size() << " bits." << std::endl;

    while (index < data.size())
    {
        std::string bitSequence;
        bool matchFound = false;

        for (size_t i = index; i < data.size(); ++i)
        {
            bitSequence.push_back(data[i] ? '1' : '0');
            if (bitsDictionary.find(bitSequence) != bitsDictionary.end())
            {
                dadosComprimidos.push_back(bitsDictionary[bitSequence]);
                index = i + 1; // "Atualiza índice para posição após a sequência correspondente
                matchFound = true;
                break;
            }
        }

        if (!matchFound)
        {
            index++; // Incrementa Índice caso nenhum caso nenhuma sequencia corresponden seja encontrada.
        }

        // Debug: Show progress
        // std::cout << "Current index: " << index << ", Match found: " << matchFound << std::endl;
    }

    // Debug: Imprimir o conteúdo de dadosComprimidos
    std::cout << "--------------- DADOS COMPRIMIDOS (input.compressed): ---------------------" << std::endl;
    for (const auto &code : dadosComprimidos)
    {
        std::cout << code << "";
    }
    std::cout << std::endl;
    std::cout << "------------------------------- ||  ----------------------------------------" << std::endl;
    return dadosComprimidos;
}

std::vector<bool> Compressor::descomprimirDados(const std::vector<std::string> &dadosComprimidos)
{
    std::vector<bool> dadosDescomprimidos;
    std::cout << "--------------- USANDO DICIONÁRIO DE SÍMBOLOS PARA DESCOMPACTAR DADOS : ---------" << std::endl;    
    //std::cout << "Descompactando dados... " << std::endl;
 
    for (const auto &code : dadosComprimidos)
    {
        std::cout << "Code: " << code << " ";
        if (debitsDictionary.find(code) != debitsDictionary.end())
        {
            std::string sequence = debitsDictionary[code];
            std::cout << "Sequencia: " << sequence << " ";
            
            for (char bit : sequence)
            {
                bool bitValue = (bit == '1');
                dadosDescomprimidos.push_back(bitValue);
                //std::cout << bitValue; // Print each bit as it's added
            }
        }
        else
        {
            std::cout << "Símbolo não encontrado no dicionário para descompressão";
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------- ||  ----------------------------" << std::endl;

    std::cout << "Descompactação completa. Tamanho da descompressão de dados: " << dadosDescomprimidos.size() << " bits." << std::endl;

    // Additional debugging: print the entire decompressed binary sequence
    std::cout << "--------------- DESCOMPRESSÃO DOS DADOS BINÁRIOS : ---------" << std::endl;    
    for (bool bit : dadosDescomprimidos)
    {
        std::cout << bit << "";
    }
    std::cout << std::endl;
    std::cout << "----------------------- ||  ----------------------------" << std::endl;

    return dadosDescomprimidos;
}

void Compressor::escreverComprimidoParaArquivo(const std::vector<std::string> &dadosComprimidos, const std::string &nomeArquivo)
{
    std::ofstream file(nomeArquivo);
    if (!file)
    {
        std::cerr << "Erro ao abrir arquivo para escrita: " << nomeArquivo << std::endl;
        return;
    }

    // Imprimir o nome do arquivo e o tamanho do vetor de dados comprimidos
    std::cout << "Escrevendo " << dadosComprimidos.size() << " símbolos em arquivo compactado: " << nomeArquivo << std::endl;

    for (const auto &code : dadosComprimidos)
    {
        file << code << "";
    }
}

std::vector<std::string> Compressor::readarquivoCompactado(const std::string &nomeArquivo)
{
    std::vector<std::string> dadosComprimidos;
    std::ifstream file(nomeArquivo);
    if (!file)
    {
        std::cerr << "Erro ao abrir arquivo para leitura: " << nomeArquivo << std::endl;
        return {};
    }

    char ch;
    std::string code;
    while (file.get(ch))
    {
        code.push_back(ch);
        // Check if this sequence of characters matches any code in the decompression dictionary
        if (debitsDictionary.find(code) != debitsDictionary.end())
        {
            dadosComprimidos.push_back(code);
            code.clear(); // Reset the code string for the next sequence
        }
    }

    return dadosComprimidos;
}

void Compressor::imprimirVetor16Bits(const std::vector<bool> &bits)
{
    std::cout << "\n";
    std::cout << "--------------- LEITURA DO VETOR (16 BITS): ---------------------" << std::endl;
    for (size_t i = 0; i < bits.size(); ++i)
    {
        std::cout << bits[i]; // Imprime o bit atual

        if ((i + 1) % 16 == 0)
        {
            std::cout << std::endl; // Quebra de linha a cada 16 bits
        }
    }

    if (bits.size() % 16 != 0)
    {
        std::cout << std::endl; // Certifica-se de terminar com uma quebra de linha se não for múltiplo de 16
    }
    std::cout << "--------------------------- || ----------------------------------" << std::endl;
}

void Compressor::converterTextoParaBinario()
{
    //writeCharAsBinaryToFile(arquivoBinario);
    writeCharAsBinaryToFile(arquivoEncriptado, arquivoBinario); // Updated call
}

void Compressor::writeCharAsBinaryToFile(const std::string &inputFilePath, const std::string &outputFilePath) {
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    std::ofstream outputFile(outputFilePath, std::ios::binary);

    if (!inputFile || !outputFile) {
        std::cerr << "Erro abrindo arquivos." << std::endl;
        return;
    }

    char character;
    while (inputFile.get(character)) {
        std::bitset<8> binary(character);
        outputFile << binary;
    }
}

void Compressor::lerDescomprimido() {
    std::cout << "--------------- CONTEÚDO DO ARQUIVO DESCOMPACTADO : ---------------------" << std::endl;    
    std::ifstream decompressedFile(this->arquivoDescompactado);  // Use the member variable for the file path
    if (!decompressedFile) {        
        std::cerr << "Erro ao abrir o arquivo descompactado para leitura: " << this->arquivoDescompactado << std::endl;
    } else {
        std::cout << "\nConteúdo do Arquivo Descompactado (" << this->arquivoDescompactado << "):\n";
        std::string line;
        while (std::getline(decompressedFile, line)) {
            std::cout << line << std::endl;
        }
    }
    std::cout << "--------------------------- || ----------------------------------" << std::endl;
}

void Compressor::encriptarArquivoTexto() {
    char key = 'X'; // Chave simples de encriptação usando o XOR
    std::ifstream inputFile(this->arquivoTxt, std::ios::binary);
    std::ofstream outputFile(this->arquivoEncriptado, std::ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files for encryption." << std::endl;
        return;
    }

    char ch;
    while (inputFile.get(ch)) {
        char encryptedChar = ch ^ key; // XOR encryption
        outputFile.put(encryptedChar);
    }

    inputFile.close();
    outputFile.close();
}

void Compressor::desencriptarComprimido() {
    std::cout << "--------------- ARQUIVO DESCRIPTOGRAFADO : ---------------------" << std::endl;    
    char key = 'X'; // Mesma Chave simples de encriptação usando o XOR
    std::ifstream inputFile(this->arquivoDescompactado, std::ios::binary);
    std::ofstream outputFile(this->arquivoDesencriptado, std::ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files for decryption." << std::endl;
        return;
    }

    char ch;
    while (inputFile.get(ch)) {
        char decryptedChar = ch ^ key; // XOR decryption
        outputFile.put(decryptedChar);
        std::cout << decryptedChar;
    }

    inputFile.close();
    outputFile.close();
    
    std::cout << "--------------------------- || ----------------------------------" << std::endl;
}


void Compressor::writeUserInputToFile() {
    std::ofstream file(this->arquivoTxt);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo para escrita: " << this->arquivoTxt << std::endl;
        return;
    }

    std::cout << "Digite o texto a ser salvo em input.txt (pressione ENTER para concluir): \n";
    std::string line;
    std::getline(std::cin, line);
    file << line;

    file.close();
}