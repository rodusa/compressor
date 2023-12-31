// main.cpp
#include "compressor.h"
#include <string>
#include <iostream>

int main() {
    std::string path;
    std::cout << "\n";
    std::cout << "###### PROGRAMA PARA COMPACTAR E CRIPTOGRAFAR CARACTERES (TEXTO) ######\n";
    std::cout << "Este programa utiliza os sequintes arquivos para compressao e criptografia: " << std::endl;    
    std::cout << "\n";
    std::cout << "ARQUIVO TEXTO: input.txt" << std::endl;
    std::cout << "ARQUIVO ENCRIPTADO: input.encrypted" << std::endl;
    std::cout << "ARQUIVO ENCRIPTADO P/ BINARIO: input.bin" << std::endl;
    std::cout << "ARQUIVO BINÁRIO COMPACTADO: input.compressed " << std::endl;
    std::cout << "ARQUIVO DESCOMPACTADO: decompressed.txt" << std::endl;
    std::cout << "ARQUIVO DESCRIPTOGRAFADO: outupt.decrypted" << std::endl;
    std::cout << "\n";
    std::cout << "Certifique-se que o arquivo input.txt existe e esta no mesmo local do executavel" << std::endl;
    std::cout << "Pressione ENTER para prosseguir." << std::endl;
    std::cin.get();

    // Este caminho deverá ser mudado para o caminho
    //std::string folder = "/Users/rlueneberg/Documents/data/2023/gabi-c++/project/";
    // In windows user C:\\Users\\gabriel\\Desktop\\ProjetoVersaoFinal

    std::string folder;
    std::cout << "Por favor, insira o caminho da pasta onde está o arquivo input.txt: ";
    std::getline(std::cin, folder);

    // Substituir todas as barras simples (\) por barras duplas (\\)
    //std::replace(folder.begin(), folder.end(), '\\', '/');
    // Substituir todas as barras simples '\' por barras duplas '\\'
    size_t pos = 0;
    while ((pos = path.find("\\", pos)) != std::string::npos) {
         path.replace(pos, 1, "\\\\");
         pos += 2; // Avançar a posição passando a barra dupla
    }

    
    std::string arquivoTxtPath = folder + "input.txt"; // Arquivo com texto
    std::string arquivoBinario = folder + "input.bin"; // Arquivo texto convertido para binário    
    std::string arquivoCompactadoPath = folder + "input.compressed"; // Arquivo binário compactado    
    std::string arquivoDescompactadoPath = folder + "input.decompressed"; // Arquivo binário compactado convertido para texto
    std::string arquivoEncriptadoPath = folder + "input.encrypted"; // Arquivo encriptado
    std::string arquivoDesencriptadoPath = folder + "outupt.decrypted"; // Arquvivo desencriptado
    

    // Atualize a chamada do construtor para incluir o novo argumento.
    Compressor compressor(arquivoTxtPath, arquivoCompactadoPath, arquivoDescompactadoPath, arquivoBinario, arquivoEncriptadoPath, arquivoDesencriptadoPath);
    compressor.solicitarDadosDoUsuario(); // Usuário entra com texto e salva no arquivo input.txt
    compressor.encriptarArquivoTexto(); // Encripta arquivo texto (input.encrypted)
    compressor.converterTextoParaBinario(); // Converte arquivo encriptado para binário (input.bin)
    compressor.comprimirBinario(); // Comprime arquivo encriptado para binário (compressed.txt)
    compressor.descomprimirBinario(); // Descomprime arquivo binário encriptado (decompressed.txt)
    compressor.desencriptarComprimido();
    
    return 0;
}