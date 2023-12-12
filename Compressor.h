// Compressor.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Compressor {
public:
    Compressor(const std::string &inputFile, const std::string &compressedFile, const std::string &decompressedFile, const std::string &convertedFile);


    void printBits(const std::vector<bool> &bits);


    void comprimir();
    void descomprimir();
    void displayIntermediateResults();

    // New method to convert text to binary
    void converterTextoParaBinario();

private:
    std::string inputFile;
    std::string compressedFile;
    std::string decompressedFile;
    std::string convertedFilePath;

    std::unordered_map<std::string, std::string> bitsDictionary;
    std::unordered_map<std::string, std::string> debitsDictionary;

    void construirDicionarios();
    std::vector<bool> lerArquivoParaBinario(const std::string &fileName);
    void writeBinaryToFile(const std::vector<bool> &dadosBinarios, const std::string &fileName);
    std::vector<std::string> compressData(const std::vector<bool> &data);
    std::vector<bool> descomprimirDados(const std::vector<std::string> &dadosComprimidos);
    void escreverComprimidoParaArquivo(const std::vector<std::string> &dadosComprimidos, const std::string &fileName);
    std::vector<std::string> readCompressedFile(const std::string &fileName);

    // New private method to write each character as binary to a file
    void writeCharAsBinaryToFile(const std::string &fileName);
};
