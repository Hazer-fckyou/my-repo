#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
import mastermind;
int main() {
    try {
        size_t field_size = 0;
        std::cout << "Введите размер поля: ";
        if (!(std::cin >> field_size) || field_size == 0) {
            throw std::invalid_argument("Некорректный размер поля");
        }

        size_t max_steps = 0;
        std::cout << "Введите максимальное количество шагов: ";
        if (!(std::cin >> max_steps) || max_steps == 0) {
            throw std::invalid_argument("Некорректное количество шагов");
        }

        // Инъекция зависимостей (DIP)
        auto game = std::make_unique<MasterMindGame>(
            field_size,
            std::make_unique<RandomGenerator>()
        );

        while (!game->get_is_finished() && game->get_current_step() < max_steps) {
            std::vector<Colors> guess(field_size);
            std::cout << "Шаг " << (game->get_current_step() + 1) << ". Введите последовательность (R G B): ";

            char input;
            for (size_t i = 0; i < field_size; ++i) {
                std::cin >> input;
                switch (input) {
                case 'R': guess[i] = Colors::RED; break;
                case 'G': guess[i] = Colors::GREEN; break;
                case 'B': guess[i] = Colors::BLUE; break;
                default: throw std::invalid_argument("Недопустимый символ цвета");
                }
            }

            auto [black, white] = game->make_guess(guess);
            std::cout << "Чёрные: " << black << ", Белые: " << white << "\n";

            if (black == static_cast<int>(field_size)) {
                std::cout << "Победа! Угадано за " << game->get_current_step() << " шагов.\n";
            }
        }

        if (!game->get_is_finished()) {
            std::cout << "Игра завершена. Превышен лимит шагов.\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}