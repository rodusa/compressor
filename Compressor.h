// Compressor.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Compressor {
public:
    Compressor(const std::string &arquivoTxtEntrada, const std::string &arquivoCompactado, const std::string &arquivoDescompactado, const std::string &convertedFile);
    void imprimirBits(const std::vector<bool> &bits);

    void comprimir();
    void descomprimir();
    void displayIntermediateResults();

    // New method to convert text to binary
    void converterTextoParaBinario();

private:
    std::string arquivoTxtEntrada;
    std::string arquivoCompactado;
    std::string arquivoDescompactado;
    std::string arquivoBinario;

    std::unordered_map<std::string, std::string> bitsDictionary;
    std::unordered_map<std::string, std::string> debitsDictionary;

    void construirDicionarios();
    std::vector<bool> lerArquivoParaBinario(const std::string &fileName);
    void escreverBinarioEmArquivo(const std::vector<bool> &dadosBinarios, const std::string &fileName);
    std::vector<std::string> compressData(const std::vector<bool> &data);
    std::vector<bool> descomprimirDados(const std::vector<std::string> &dadosComprimidos);
    void escreverComprimidoParaArquivo(const std::vector<std::string> &dadosComprimidos, const std::string &fileName);
    std::vector<std::string> readarquivoCompactado(const std::string &fileName);

    // New private method to write each character as binary to a file
    void writeCharAsBinaryToFile(const std::string &fileName);
};
