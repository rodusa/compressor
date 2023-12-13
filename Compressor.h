// Compressor.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Compressor {
public:
Compressor(const std::string &arquivoTxtEntrada, 
               const std::string &arquivoCompactado, 
               const std::string &arquivoDescompactado, 
               const std::string &convertedFile,
               const std::string &arquivoEncriptado);

    void imprimirVetor16Bits(const std::vector<bool> &bits);

    void converterTextoParaBinario();
    void comprimirBinario();
    void descomprimirBinario();
    void lerDescomprimido();
    void encriptarArquivoTexto();

private:
    std::string arquivoTxtEntrada;
    std::string arquivoCompactado;
    std::string arquivoDescompactado;
    std::string arquivoBinario;
    std::string arquivoEncriptado;


    std::unordered_map<std::string, std::string> bitsDictionary;
    std::unordered_map<std::string, std::string> debitsDictionary;

    void construirDicionarios();
    std::vector<bool> lerArquivoParaBinario(const std::string &nomeArquivo);
    void escreverBinarioEmArquivo(const std::vector<bool> &dadosBinarios, const std::string &nomeArquivo);
    std::vector<std::string> compressData(const std::vector<bool> &data);
    std::vector<bool> descomprimirDados(const std::vector<std::string> &dadosComprimidos);
    void escreverComprimidoParaArquivo(const std::vector<std::string> &dadosComprimidos, const std::string &nomeArquivo);
    std::vector<std::string> readarquivoCompactado(const std::string &nomeArquivo);

    // New private method to write each character as binary to a file
    //void writeCharAsBinaryToFile(const std::string &nomeArquivo);
    void writeCharAsBinaryToFile(const std::string &inputFilePath, const std::string &outputFilePath);
};
