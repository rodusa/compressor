// Compressor.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Compressor {
public:
Compressor(const std::string &arquivoTxt, 
               const std::string &arquivoCompactado, 
               const std::string &arquivoDescompactado, 
               const std::string &convertedFile,
               const std::string &arquivoEncriptado,
               const std::string &arquivoDesencriptado
               );

    void imprimirVetor16Bits(const std::vector<bool> &bits);

    void solicitarDadosDoUsuario();
    void converterTextoParaBinario();
    void comprimirBinario();
    void descomprimirBinario();
    void lerDescomprimido();
    void encriptarArquivoTexto();
    void desencriptarComprimido();    

private:
    std::string arquivoTxt;
    std::string arquivoCompactado;
    std::string arquivoDescompactado;
    std::string arquivoBinario;
    std::string arquivoEncriptado;
    std::string arquivoDesencriptado;
    
    std::unordered_map<std::string, std::string> bitsDictionary;
    std::unordered_map<std::string, std::string> debitsDictionary;

    void construirDicionarios();
    std::vector<bool> lerArquivoParaBinario(const std::string &nomeArquivo);
    void escreverBinarioEmArquivo(const std::vector<bool> &dadosBinarios, const std::string &nomeArquivo);
    std::vector<std::string> comprimirDados(const std::vector<bool> &data);
    std::vector<bool> descomprimirDados(const std::vector<std::string> &dadosComprimidos);
    void escreverEncriptadoParaBinario(const std::vector<std::string> &dadosComprimidos, const std::string &nomeArquivo);
    std::vector<std::string> readarquivoCompactado(const std::string &nomeArquivo);

    // New private method to write each character as binary to a file
    //void writeCharAsBinaryToFile(const std::string &nomeArquivo);
    void writeCharAsBinaryToFile(const std::string &inputFilePath, const std::string &outputFilePath);
};
