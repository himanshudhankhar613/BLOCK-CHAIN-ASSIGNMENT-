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

    void mineBlock(int difficulty) {
        std::string target(difficulty, '0');
        std::cout << "⛏️ Mining block...\n";
        time_t start = time(0);
        while (hash.substr(0, difficulty) != target) {
            nonce++;
            hash = calculateHash();
        }
        time_t end = time(0);
        std::cout << "✅ Block mined: " << hash << "\n";
        std::cout << "Attempts: " << nonce << "\n";
        std::cout << "⏱️ Time taken: " << end - start << " seconds\n";
    }

private:
    std::string currentTime() const {
        time_t now = time(0);
        char* dt = ctime(&now);
        return std::string(dt);
    }
};

int main() {
    Block block(1, "Mining data", "0");
    block.mineBlock(4); // Adjust difficulty as needed
    return 0;
}
