// main.cpp
#include "Compressor.h"
#include <string>

int main() {
    std::string folder = "/Users/rlueneberg/Documents/data/2023/gabi-c++/project/";
    //std::string folder = "./";
    
    std::string arquivoTxtEntradaPath = folder + "input.txt";
    std::string arquivoCompactadoPath = folder + "compressed.txt";    
    std::string arquivoDescompactadoPath = folder + "decompressed.txt";
    std::string arquivoBinario = folder + "input.bin"; // Add this line

    // Update the constructor call to include the new argument
    Compressor compressor(arquivoTxtEntradaPath, arquivoCompactadoPath, arquivoDescompactadoPath, arquivoBinario);
    compressor.converterTextoParaBinario(); // Call this method to perform the conversion "input.bin"
    compressor.comprimir(); // compressed.txt
    compressor.descomprimir(); // decompressed.txt
    
    return 0;
}