module;
#include <random>
#include <memory>
export module mastermind:generator;

export class IGenerator {
public:
    virtual ~IGenerator() = default;
    virtual double generate() = 0;
};

export class RandomGenerator final : public IGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<double> dist;
public:
    RandomGenerator() : gen(rd()), dist(0.0, 1.0) {}
    double generate() override { return dist(gen); }
};