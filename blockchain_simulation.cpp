#include <iostream>
#include <string>
#include <ctime>
#include "picosha2.h"

class Block {
public:
    int index;
    std::string timestamp;
    std::string data;
    std::string previousHash;
    std::string hash;
    int nonce;

    Block(int idx, const std::string& data, const std::string& prevHash)
        : index(idx), data(data), previousHash(prevHash), nonce(0) {
        timestamp = currentTime();
        hash = calculateHash();
    }

    std::string calculateHash() const {
        std::string input = std::to_string(index) + timestamp + data + previousHash + std::to_string(nonce);
        return picosha2::hash256_hex_string(input);
    }

    void printBlock() const {
        std::cout << "Block #" << index << "\n"
                  << "Data: " << data << "\n"
                  << "Hash: " << hash << "\n"
                  << "Previous Hash: " << previousHash << "\n\n";
    }

private:
    std::string currentTime() const {
        time_t now = time(0);
        char* dt = ctime(&now);
        return std::string(dt);
    }
};

int main() {
    Block genesis(0, "Genesis Block", "0");
    Block block1(1, "Block 1 Data", genesis.hash);
    Block block2(2, "Block 2 Data", block1.hash);

    genesis.printBlock();
    block1.printBlock();
    block2.printBlock();

    // Tamper with block1
    std::cout << "🔧 Tampering with Block 1...\n\n";
    block1.data = "Tampered Data";
    block1.hash = block1.calculateHash();

    block1.printBlock();
    block2.printBlock();

    if (block2.previousHash != block1.hash) {
        std::cout << "❌ Chain broken: Block 2's previousHash doesn't match Block 1's new hash!\n";
    } else {
        std::cout << "✅ Chain intact.\n";
    }

    return 0;
}
