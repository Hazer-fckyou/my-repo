module;
#include <vector>
#include <stdexcept>
#include <memory>
export module mastermind;
export import :generator;
import :evaluator;
export import :types;

export class MasterMindGame {
private:
    std::vector<Colors> answer;
    std::unique_ptr<IGenerator> generator;
    Evaluator evaluator;
    size_t field_size;
    size_t current_step;
    bool is_finished;

public:
    MasterMindGame(size_t size, std::unique_ptr<IGenerator> gen)
        : field_size(size), generator(std::move(gen)), current_step(0), is_finished(false)
    {
        create_answer();
    }

    // Запрет копирования, разрешение перемещения
    MasterMindGame(const MasterMindGame&) = delete;
    MasterMindGame& operator=(const MasterMindGame&) = delete;
    MasterMindGame(MasterMindGame&&) = default;
    MasterMindGame& operator=(MasterMindGame&&) = default;

private:
    void create_answer() {
        answer.reserve(field_size);
        for (size_t i = 0; i < field_size; ++i) {
            double p = generator->generate();
            // Исправлена логика вероятностей
            Colors c = (p <= 0.33) ? Colors::RED :
                (p <= 0.66) ? Colors::GREEN : Colors::BLUE;
            answer.push_back(c);
        }
    }

public:
    std::pair<int, int> make_guess(const std::vector<Colors>& guess) {
        if (is_finished) throw std::runtime_error("Игра уже завершена");
        if (guess.size() != field_size) throw std::invalid_argument("Неверный размер ввода");

        ++current_step;
        auto result = evaluator.evaluate(answer, guess);
        if (result.first == static_cast<int>(field_size)) {
            is_finished = true;
        }
        return result;
    }

    size_t get_current_step() const { return current_step; }
    bool get_is_finished() const { return is_finished; }
};