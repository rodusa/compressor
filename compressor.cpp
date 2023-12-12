// Compressor.cpp
#include "Compressor.h"
#include <fstream>
#include <iostream>
#include <bitset>

Compressor::Compressor(const std::string &inputFile, const std::string &compressedFile, const std::string &decompressedFile, const std::string &convertedFile)
    : inputFile(inputFile), compressedFile(compressedFile), decompressedFile(decompressedFile), convertedFilePath(convertedFile)
{
    construirDicionarios();
}

void Compressor::comprimir()
{
    auto dadosBinarios = lerArquivoParaBinario(inputFile);
    printBits(dadosBinarios);
    auto dadosComprimidos = compressData(dadosBinarios);
    escreverComprimidoParaArquivo(dadosComprimidos, compressedFile);
}

void Compressor::descomprimir()
{
    auto dadosComprimidos = readCompressedFile(compressedFile);
    auto dadosDescomprimidos = descomprimirDados(dadosComprimidos);
    writeBinaryToFile(dadosDescomprimidos, decompressedFile);
}

// Dicionário 4 bits
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

std::vector<bool> Compressor::lerArquivoParaBinario(const std::string &fileName)
{
    std::vector<bool> dadosBinarios;
    std::ifstream file(fileName, std::ios::binary);
    if (!file)
    {
        std::cerr << "Erro ao abrir arquivo para leitura: " << fileName << std::endl;
        return {};
    }
    else
    {
        std::cout << "Arquivo " << fileName << " foi lido com sucesso." << std::endl;
    }

    char buffer[2];
    while (file.read(buffer, 2))
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 7; j >= 0; --j)
            {
                dadosBinarios.push_back((buffer[i] >> j) & 1);
            }
        }
    }

    int lastReadCount = file.gcount();
    for (int i = 0; i < lastReadCount; ++i)
    {
        for (int j = 7; j >= 0; --j)
        {
            dadosBinarios.push_back((buffer[i] >> j) & 1);
        }
    }

    return dadosBinarios;
}

void Compressor::writeBinaryToFile(const std::vector<bool> &dadosBinarios, const std::string &fileName) {
    std::ofstream file(fileName, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for writing: " << fileName << std::endl;
        return;
    }

    // Write full bytes (8 bits)
    size_t i = 0;
    for (; i + 7 < dadosBinarios.size(); i += 8) {
        char c = 0;
        for (int j = 0; j < 8; ++j) {
            c |= dadosBinarios[i + j] << (7 - j);
        }
        file.put(c);
    }

    // Handle the remaining bits if they don't make up a full byte
    if (i < dadosBinarios.size()) {
        char c = 0;
        int bitCount = 0;
        for (; i < dadosBinarios.size(); ++i, ++bitCount) {
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
                index = i + 1; // Update index to the position after the matched sequence
                matchFound = true;
                break;
            }
        }

        if (!matchFound)
        {
            index++; // Increment index if no match is found
        }

        // Debug: Show progress
        // std::cout << "Current index: " << index << ", Match found: " << matchFound << std::endl;
    }

    // Debug: Imprimir o conteúdo de dadosComprimidos
    std::cout << "Dados Comprimidos:" << std::endl;
    for (const auto &code : dadosComprimidos)
    {
        std::cout << code << " ";
    }
    std::cout << std::endl;

    return dadosComprimidos;
}

std::vector<bool> Compressor::descomprimirDados(const std::vector<std::string> &dadosComprimidos) {
    std::vector<bool> dadosDescomprimidos;
    std::cout << "Decompressing data... " << std::endl;

    for (const auto &code : dadosComprimidos) {
        std::cout << "Code: " << code << " ";
        if (debitsDictionary.find(code) != debitsDictionary.end()) {
            std::string sequence = debitsDictionary[code];
            std::cout << "Sequence: " << sequence << " ";
            for (char bit : sequence) {
                bool bitValue = (bit == '1');
                dadosDescomprimidos.push_back(bitValue);
                std::cout << bitValue; // Print each bit as it's added
            }
        } else {
            std::cout << "Code not found in decompression dictionary";
        }
        std::cout << std::endl;
    }

    std::cout << "Decompression complete. Size of decompressed data: " << dadosDescomprimidos.size() << " bits." << std::endl;

    // Additional debugging: print the entire decompressed binary sequence
    std::cout << "Decompressed Binary Data: ";
    for (bool bit : dadosDescomprimidos) {
        std::cout << bit << "";
    }
    std::cout << std::endl;

    return dadosDescomprimidos;
}


void Compressor::escreverComprimidoParaArquivo(const std::vector<std::string> &dadosComprimidos, const std::string &fileName)
{
    std::ofstream file(fileName);
    if (!file)
    {
        std::cerr << "Error opening file for writing: " << fileName << std::endl;
        return;
    }

    // Imprimir o nome do arquivo e o tamanho do vetor de dados comprimidos
    std::cout << "Writing " << dadosComprimidos.size() << " compressed codes to file: " << fileName << std::endl;

    for (const auto &code : dadosComprimidos)
    {
        file << code << "";
    }
}

std::vector<std::string> Compressor::readCompressedFile(const std::string &fileName)
{
    std::vector<std::string> dadosComprimidos;
    std::ifstream file(fileName);
    if (!file)
    {
        std::cerr << "Error opening file for reading: " << fileName << std::endl;
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


void Compressor::printBits(const std::vector<bool> &bits)
{
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
}

void Compressor::converterTextoParaBinario() {
    writeCharAsBinaryToFile(convertedFilePath);
}

void Compressor::writeCharAsBinaryToFile(const std::string &fileName) {
    std::ifstream inputFile(this->inputFile);
    std::ofstream outputFile(fileName, std::ios::binary);

    if (!inputFile || !outputFile) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    char character;
    while (inputFile.get(character)) {
        std::bitset<8> binary(character);
        outputFile << binary;
    }
}

