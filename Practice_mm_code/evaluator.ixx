module;
#include <vector>
#include <stdexcept>
#include <algorithm>
export module mastermind:evaluator;
import :types;

export class Evaluator {
public:
    std::pair<int, int> evaluate(const std::vector<Colors>& answer, const std::vector<Colors>& guess) const {
        if (answer.size() != guess.size()) {
            throw std::invalid_argument("Размеры последовательностей не совпадают");
        }

        int black = 0, white = 0;
        std::vector<bool> answer_used(answer.size(), false);
        std::vector<bool> guess_used(guess.size(), false);

        // 1. Подсчёт точных совпадений (чёрные)
        for (size_t i = 0; i < answer.size(); ++i) {
            if (answer[i] == guess[i]) {
                ++black;
                answer_used[i] = true;
                guess_used[i] = true;
            }
        }

        // 2. Подсчёт совпадений по цвету, но не по позиции (белые)
        for (size_t i = 0; i < guess.size(); ++i) {
            if (guess_used[i]) continue;
            for (size_t j = 0; j < answer.size(); ++j) {
                if (answer_used[j]) continue;
                if (answer[j] == guess[i]) {
                    ++white;
                    answer_used[j] = true;
                    break; // Цвет использован, переходим к следующему элементу猜测
                }
            }
        }
        return { black, white };
    }
};