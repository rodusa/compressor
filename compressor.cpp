// Compressor.cpp
#include "Compressor.h"
#include <fstream>
#include <iostream>
#include <bitset>

Compressor::Compressor(const std::string &inputFile, const std::string &compressedFile, const std::string &decompressedFile, const std::string &convertedFile)
    : inputFile(inputFile), compressedFile(compressedFile), decompressedFile(decompressedFile), convertedFilePath(convertedFile)
{
    buildDictionaries();
}

void Compressor::comprimir()
{
    auto binaryData = readFileToBinary(inputFile);
    printBits(binaryData);
    auto compressedData = compressData(binaryData);
    writeCompressedToFile(compressedData, compressedFile);
}

void Compressor::descomprimir()
{
    auto compressedData = readCompressedFile(compressedFile);
    auto decompressedData = decompressData(compressedData);
    writeBinaryToFile(decompressedData, decompressedFile);
}

// Dicionário 4 bits
void Compressor::buildDictionaries()
{
    compressionDictionary["0000"] = "A";
    compressionDictionary["0001"] = "B";
    compressionDictionary["0010"] = "C";
    compressionDictionary["0011"] = "D";
    compressionDictionary["0100"] = "E";
    compressionDictionary["0101"] = "F";
    compressionDictionary["0110"] = "G";
    compressionDictionary["0111"] = "H";
    compressionDictionary["1000"] = "I";
    compressionDictionary["1001"] = "J";
    compressionDictionary["1010"] = "K";
    compressionDictionary["1011"] = "L";
    compressionDictionary["1100"] = "M";
    compressionDictionary["1101"] = "N";
    compressionDictionary["1110"] = "O";
    compressionDictionary["1111"] = "P";


    // Build the decompression dictionary
    for (const auto &pair : compressionDictionary)
    {
        decompressionDictionary[pair.second] = pair.first;
    }
}

std::vector<bool> Compressor::readFileToBinary(const std::string &fileName)
{
    std::vector<bool> binaryData;
    std::ifstream file(fileName, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error opening file for reading: " << fileName << std::endl;
        return {};
    }
    else
    {
        std::cout << "File " << fileName << " was read successfully." << std::endl;
    }

    char buffer[2];
    while (file.read(buffer, 2))
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 7; j >= 0; --j)
            {
                binaryData.push_back((buffer[i] >> j) & 1);
            }
        }
    }

    int lastReadCount = file.gcount();
    for (int i = 0; i < lastReadCount; ++i)
    {
        for (int j = 7; j >= 0; --j)
        {
            binaryData.push_back((buffer[i] >> j) & 1);
        }
    }

    return binaryData;
}

void Compressor::writeBinaryToFile(const std::vector<bool> &binaryData, const std::string &fileName) {
    std::ofstream file(fileName, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for writing: " << fileName << std::endl;
        return;
    }

    // Write full bytes (8 bits)
    size_t i = 0;
    for (; i + 7 < binaryData.size(); i += 8) {
        char c = 0;
        for (int j = 0; j < 8; ++j) {
            c |= binaryData[i + j] << (7 - j);
        }
        file.put(c);
    }

    // Handle the remaining bits if they don't make up a full byte
    if (i < binaryData.size()) {
        char c = 0;
        int bitCount = 0;
        for (; i < binaryData.size(); ++i, ++bitCount) {
            c |= binaryData[i] << (7 - bitCount);
        }
        file.put(c);
    }
}


std::vector<std::string> Compressor::compressData(const std::vector<bool> &data)
{
    std::vector<std::string> compressedData;
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
            if (compressionDictionary.find(bitSequence) != compressionDictionary.end())
            {
                compressedData.push_back(compressionDictionary[bitSequence]);
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

    // Debug: Imprimir o conteúdo de compressedData
    std::cout << "Dados Comprimidos:" << std::endl;
    for (const auto &code : compressedData)
    {
        std::cout << code << " ";
    }
    std::cout << std::endl;

    return compressedData;
}

std::vector<bool> Compressor::decompressData(const std::vector<std::string> &compressedData) {
    std::vector<bool> decompressedData;
    std::cout << "Decompressing data... " << std::endl;

    for (const auto &code : compressedData) {
        std::cout << "Code: " << code << " ";
        if (decompressionDictionary.find(code) != decompressionDictionary.end()) {
            std::string sequence = decompressionDictionary[code];
            std::cout << "Sequence: " << sequence << " ";
            for (char bit : sequence) {
                bool bitValue = (bit == '1');
                decompressedData.push_back(bitValue);
                std::cout << bitValue; // Print each bit as it's added
            }
        } else {
            std::cout << "Code not found in decompression dictionary";
        }
        std::cout << std::endl;
    }

    std::cout << "Decompression complete. Size of decompressed data: " << decompressedData.size() << " bits." << std::endl;

    // Additional debugging: print the entire decompressed binary sequence
    std::cout << "Decompressed Binary Data: ";
    for (bool bit : decompressedData) {
        std::cout << bit << "";
    }
    std::cout << std::endl;

    return decompressedData;
}


void Compressor::writeCompressedToFile(const std::vector<std::string> &compressedData, const std::string &fileName)
{
    std::ofstream file(fileName);
    if (!file)
    {
        std::cerr << "Error opening file for writing: " << fileName << std::endl;
        return;
    }

    // Imprimir o nome do arquivo e o tamanho do vetor de dados comprimidos
    std::cout << "Writing " << compressedData.size() << " compressed codes to file: " << fileName << std::endl;

    for (const auto &code : compressedData)
    {
        file << code << "";
    }
}

std::vector<std::string> Compressor::readCompressedFile(const std::string &fileName)
{
    std::vector<std::string> compressedData;
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
        if (decompressionDictionary.find(code) != decompressionDictionary.end())
        {
            compressedData.push_back(code);
            code.clear(); // Reset the code string for the next sequence
        }
    }

    return compressedData;
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

void Compressor::convertTextToBinary() {
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

