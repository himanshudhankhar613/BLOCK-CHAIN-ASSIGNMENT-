#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>

struct Validator {
    std::string name;
    int power;
    int stake;
};

int main() {
    srand(time(0));

    // PoW Simulation
    std::vector<Validator> miners = {
        {"MinerA", rand() % 100, 0},
        {"MinerB", rand() % 100, 0}
    };
    Validator powWinner = miners[0].power > miners[1].power ? miners[0] : miners[1];
    std::cout << "🔧 PoW Winner: " << powWinner.name << " with power " << powWinner.power << "\n";
    std::cout << "Logic: Validator with highest computational power is chosen.\n\n";

    // PoS Simulation
    std::vector<Validator> stakers = {
        {"StakerA", 0, rand() % 100},
        {"StakerB", 0, rand() % 100}
    };
    Validator posWinner = stakers[0].stake > stakers[1].stake ? stakers[0] : stakers[1];
    std::cout << "💰 PoS Winner: " << posWinner.name << " with stake " << posWinner.stake << "\n";
    std::cout << "Logic: Validator with highest stake is chosen.\n\n";

    // DPoS Simulation
    std::map<std::string, int> voteCount = {
        {"DelegateA", 2},
        {"DelegateB", 1},
        {"DelegateC", 0}
    };

    std::string topDelegate;
    int maxVotes = 0;
    for (auto& [name, votes] : voteCount) {
        if (votes > maxVotes) {
            maxVotes = votes;
            topDelegate = name;
        }
    }

    std::cout << "🗳️ DPoS Winner: " << topDelegate << " with " << maxVotes << " votes\n";
    std::cout << "Logic: Most-voted delegate is selected to validate.\n";

    return 0;
}
