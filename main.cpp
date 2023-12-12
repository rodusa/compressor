// main.cpp
#include "Compressor.h"
#include <string>

int main() {
    std::string folder = "/Users/rlueneberg/Documents/data/2023/gabi-c++/project/";
    //std::string folder = "./";
    
    std::string arquivoEntradaPath = folder + "input.txt";
    std::string arquivoComprimidoPath = folder + "compressed.txt";    
    std::string arquivoDescomprimidoPath = folder + "decompressed.txt";
    std::string convertedFilePath = folder + "input.bin"; // Add this line

    // Update the constructor call to include the new argument
    Compressor compressor(arquivoEntradaPath, arquivoComprimidoPath, arquivoDescomprimidoPath, convertedFilePath);
    compressor.converterTextoParaBinario(); // Call this method to perform the conversion "input.bin"
    compressor.comprimir(); // compressed.txt
    compressor.descomprimir(); // decompressed.txt
    
    return 0;
}