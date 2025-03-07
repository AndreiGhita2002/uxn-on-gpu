#ifndef UXN_H
#define UXN_H
#include <glm/glm.hpp>
#include "Resource.hpp"

// Uxn sizes
#define UXN_RAM_SIZE 65536
#define UXN_STACK_SIZE 256
#define UXN_DEV_SIZE 256
// Uxn deviceFlags
#define DEO_FLAG         0x001
#define DEO_CONSOLE_FLAG 0x002
#define DEO_CERROR_FLAG  0x004
#define DEI_CONSOLE_FLAG 0x010
#define DRAW_PIXEL_FLAG  0x100
#define DRAW_SPRITE_FLAG 0x200

//todo split into another buffer: pc, dev, flags
typedef struct uxn_memory {
    struct shared {
        glm::uint pc;
        glm::uint dev[UXN_DEV_SIZE];
        glm::uint flags;
    } shared;
    struct _private {
        glm::uint ram[UXN_RAM_SIZE];
        glm::uint wst[UXN_STACK_SIZE];  // working stack
        glm::uint pWst;
        glm::uint rst[UXN_STACK_SIZE];  // return stack
        glm::uint pRst;
    } _private;
    uxn_memory();
} UxnMemory;

enum class UXN_DEVICE: glm::uint {
    System = 0x0,
    Console = 0x10,
    Screen = 0x20,
    Audio = 0x30,
    Controller = 0x80,
    Mouse = 0x90,
    File = 0xA0,
    Datetime = 0xC0,
};
#define CALLBACK_DEVICES {UXN_DEVICE::Screen, UXN_DEVICE::Controller, UXN_DEVICE::Mouse}

char8_t from_uxn_mem(const glm::uint* p);

char16_t from_uxn_mem2(const glm::uint* p);

void to_uxn_mem(char8_t c, glm::uint* p);

void to_uxn_mem2(char16_t c, glm::uint* p);

bool mask(glm::uint x, glm::uint mask);

class Uxn {
public:
    UxnMemory* memory;
    std::unordered_map<UXN_DEVICE,uint16_t> deviceCallbackVectors;

    explicit Uxn(const char* program_path);

    ~Uxn();

    void reset();

    void outputToFile(const char* output_file_name, bool showRAM) const;

    void handleUxnIO();

    [[nodiscard]]
    bool programTerminated() const;

    bool maskFlag(glm::uint mask) const;
private:
    UxnMemory* original_memory;
    std::string program_path;
    std::vector<char> program_rom;
    std::string console_buffer;
    std::string cerror_buffer;
};

#endif //UXN_H
