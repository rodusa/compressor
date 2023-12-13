// main.cpp
#include "Compressor.h"
#include <string>
#include <iostream>

int main() {
    std::string folder = "/Users/rlueneberg/Documents/data/2023/gabi-c++/project/";
    //std::string folder = "./";
    
    std::string arquivoTxtPath = folder + "input.txt"; // Arquivo com texto
    std::string arquivoBinario = folder + "input.bin"; // Arquivo texto convertido para binário    
    std::string arquivoCompactadoPath = folder + "input.compressed"; // Arquivo binário compactado    
    std::string arquivoDescompactadoPath = folder + "input.decompressed"; // Arquivo binário compactado convertido para texto
    std::string arquivoEncriptadoPath = folder + "input.encrypted"; // Arquivo encriptado
    std::string arquivoDesencriptadoPath = folder + "outupt.decrypted"; // Arquvivo desencriptado
    
    std::cout << "\n";
    std::cout << "###### PROGRAMA PARA COMPACTAR E CRIPTOGRAFAR CARACTERES (TEXTO) ######\n";
    // Display message and wait for Enter
    std::cout << "Este programa utiliza os sequintes arquivos para compressão e criptografia: " << std::endl;    
    std::cout << "\n";
    std::cout << "ARQUIVO TEXTO: input.txt" << std::endl;
    std::cout << "ARQUIVO ENCRIPTDADO: input.encrypted" << std::endl;
    std::cout << "ARQUIVO COMPACTADO: input.bin" << std::endl;
    std::cout << "ARQUIVO BINÁRIO COMPACTADO: input.compressed " << std::endl;
    std::cout << "ARQUIVO DESCOMPACTADO: decompressed.txt" << std::endl;
    std::cout << "\n";
    std::cout << "Antes de iniciar, modifique o texto do arquivo input.txt. Certifique-se que este arquivo esteja mesmo caminho do executável." << std::endl;
    std::cout << "Caso não exista, será necessário criá-lo." << std::endl;
    std::cout << "Após Modificar o arquivo input.txt e salvá-lo, pressione ENTER para prosseguir." << std::endl;
    std::cin.get();


    // Update the constructor call to include the new argument
    Compressor compressor(arquivoTxtPath, arquivoCompactadoPath, arquivoDescompactadoPath, arquivoBinario, arquivoEncriptadoPath, arquivoDesencriptadoPath);
    compressor.encriptarArquivoTexto(); // Encripta arquivo texto (input.encrypted)
    compressor.converterTextoParaBinario(); // Converte arquivo encriptado para binário (input.bin)
    compressor.comprimirBinario(); // Comprime arquivo encriptado para binário (compressed.txt)
    compressor.descomprimirBinario(); // Descomprime arquivo binário encriptado (decompressed.txt)
    compressor.lerDescomprimido(); 
    compressor.desencriptarComprimido(); // New method call
    
    return 0;
}