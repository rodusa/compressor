// main.cpp
#include "Compressor.h"
#include <string>
#include <iostream>

int main() {
    std::string folder = "/Users/rlueneberg/Documents/data/2023/gabi-c++/project/";
    //std::string folder = "./";
    
    std::string arquivoTxtEntradaPath = folder + "input.txt"; // Arquivo com texto
    std::string arquivoBinario = folder + "input.bin"; // Arquivo texto convertido para binário    
    std::string arquivoCompactadoPath = folder + "input.compressed"; // Arquivo binário compactado    
    std::string arquivoDescompactadoPath = folder + "input.decompressed"; // Arquivo binário compactado convertido para texto
    
    std::cout << "\n";
    std::cout << "###### PROGRAMA PARA COMPACTAR E CRIPTOGRAFAR CARACTERES (TEXTO) ######\n";
    // Display message and wait for Enter
    std::cout << "Este programa utiliza os sequintes arquivos para compressão e criptografia" << std::endl;    
    std::cout << "ARQUIVO TEXTO: input.txt" << std::endl;
    std::cout << "ARQUIVO TEXTO COMPACTADO: input.bin" << std::endl;
    std::cout << "ARQUIVO BINÁRIO COMPACTADO: input.compressed " << std::endl;
    std::cout << "ARQUIVO DESCOMPACTADO: decompressed.txt" << std::endl;
    std::cout << "\n";
    std::cout << "Antes de iniciar, modifique o texto do input.txt. Certifique que o arquivo esteja mesmo caminho do executável." << std::endl;
    std::cout << "Caso não exista, será necessário criar. Depois, modifique o texto do input.txt, salvando-o." << std::endl;
    std::cout << "Após Modificar o arquivo input.txt, salvando-o. Pressione ENTER para prosseguir." << std::endl;
    std::cin.get();


    // Update the constructor call to include the new argument
    Compressor compressor(arquivoTxtEntradaPath, arquivoCompactadoPath, arquivoDescompactadoPath, arquivoBinario);
    compressor.converterTextoParaBinario(); // Call this method to perform the conversion "input.bin"
    compressor.comprimirBinario(); // compressed.txt
    compressor.descomprimirBinario(); // decompressed.txt
    compressor.lerDescomprimido(); 
    
    return 0;
}