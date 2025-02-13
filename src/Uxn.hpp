#ifndef UXN_H
#define UXN_H
#include <glm/glm.hpp>

#include "Resource.hpp"

#define UXN_RAM_SIZE 65536
#define UXN_STACK_SIZE 256
#define UXN_DEV_SIZE 256

typedef struct uxn_memory {
    glm::uint pc;
    glm::uint ram[UXN_RAM_SIZE];
    glm::uint wst[UXN_STACK_SIZE];  // working stack
    glm::uint pWst;
    glm::uint rst[UXN_STACK_SIZE];  // return stack
    glm::uint pRst;
    glm::uint dev[UXN_DEV_SIZE];
    glm::uint consoleFlag;

    uxn_memory();
} UxnMemory;


class Uxn {
public:
    UxnMemory* memory;

    explicit Uxn(const char* program_path);

    ~Uxn();

    void reset();

    void outputToFile(const char* output_file_name) const;

    void handleUxnIO();

private:
    UxnMemory* original_memory;
    std::string program_path;
    std::vector<char> program_rom;
    std::string console_buffer;
};

#endif //UXN_H
