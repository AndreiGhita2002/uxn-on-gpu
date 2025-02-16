#include <iostream>
#include <fstream>
#include "Uxn.hpp"
#include "DeviceController.hpp"

uxn_memory::uxn_memory() = default;

Uxn::Uxn(const char *program_path) {
    this->program_path = std::string(program_path);
    this->program_rom = readFile(program_path);

    if (program_rom.size() + 0x0100 * sizeof(glm::uint) > UXN_RAM_SIZE) {
        throw std::runtime_error("uxn program is bigger than uxn ram!");
    }

    // Padding the opcodes from 8-bit to 32-bit
    auto paddedProgram = std::vector<glm::uint>(program_rom.size());
    for (size_t i = 0; i < program_rom.size(); i++) {
        paddedProgram[i] = static_cast<glm::uint>(program_rom[i] << 24);
    }

    this->memory = new UxnMemory();
    // copy the program into memory
    memcpy(memory->ram + 0x0100, paddedProgram.data(), paddedProgram.size() * sizeof(glm::uint));
    // set the program counter to where the program starts from
    memory->pc = 0x0100;

    this->original_memory = new UxnMemory();
    memcpy(original_memory, memory, sizeof(UxnMemory));
}

Uxn::~Uxn() {
    delete memory;
    delete original_memory;
}

void Uxn::reset() {
    memory = original_memory;
}

void Uxn::outputToFile(const char* output_file_name) const {
    #define printValue(i, arr) if (arr[i]!=0x00000000) { outFile << "[0x" << i << "]: 0x" << arr[i] << "\n"; }

    std::ofstream outFile(output_file_name, std::ios::out | std::ios::app);
    // Check if the file opened successfully
    if (!outFile) {
        std::string message = "Failed to open file: ";
        message += output_file_name;
        throw std::runtime_error(message);
    }
    outFile << std::hex;
    outFile << "---Uxn Memory:---\n";
    outFile << "Program Counter: 0x" << memory->pc << "\n";
    outFile << "Flags: 0x" << memory->deviceFlags << "\n";
    outFile << "--RAM:--\n";
    for (int i = 0; i < UXN_RAM_SIZE; ++i) {
        printValue(i, memory->ram);
    }
    outFile << "--Working Stack:--\n";
    outFile << "wst pointer: " << memory->pWst << "\n";
    for (int i = 0; i < UXN_STACK_SIZE; ++i) {
        printValue(i, memory->wst);
    }
    outFile << "--Return Stack:--\n";
    outFile << "rst pointer: " << memory->pRst << "\n";
    for (int i = 0; i < UXN_STACK_SIZE; ++i) {
        printValue(i, memory->rst);
    }
    outFile << "--Device Data:--\n";
    for (int i = 0; i < UXN_DEV_SIZE; ++i) {
        printValue(i, memory->dev);
    }
    outFile << std::dec;

    outFile.close();
    std::cout << "Printed Uxn Memory to file: " << output_file_name << "\n";
}

void Uxn::handleUxnIO() {
    if (memory->deviceFlags) {
        char c = static_cast<char>(memory->dev[0x18] >> 24);
        console_buffer.push_back(c);
        if (c == 0x0a) {
            std::cout << "[CONSOLE] " << console_buffer;
            console_buffer.clear();
        }
    }
}

void Uxn::printConsoleBuffer(bool inHex) {
    std::cout << "[CONSOLE] ";
    if (inHex) {
        std::cout << std::hex;
        for (char c : console_buffer) {
            std::cout << "0x" << static_cast<int>(c) << " ";
        }
        std::cout << std::dec;
    } else {
        std::cout << console_buffer;
    }
    std::cout << "\n";

    console_buffer.clear();
}
