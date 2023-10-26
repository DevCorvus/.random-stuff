#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class RomanNumberConverter {
  public:
    std::string decimal_to_roman(uint number) {
        if (number >= 4000) {
            throw std::logic_error("Roman numbers can only count up to 3999");
        }

        auto vec = decompose_decimal(number);

        std::string out;

        for (auto n : vec) {
            try {
                out += convert_to_exact_roman(n);
            } catch (std::logic_error _err) {
                auto subparts = decompose_decimal_subparts(n);
                for (uint sub_n : subparts) {
                    out += convert_to_exact_roman(sub_n);
                }
            }
        }

        return out;
    }

    uint roman_to_decimal(std::string roman) {
        std::reverse(roman.begin(), roman.end());

        uint out = 0;

        uint last = 0;
        for (char r : roman) {
            uint number = convert_to_exact_decimal(r);

            if (last > number) {
                out -= number;
            } else {
                out += number;
            }

            last = number;
        }

        return out;
    }

  private:
    char convert_to_exact_roman(uint number) {
        switch (number) {
        case 1: {
            return 'I';
        }
        case 5: {
            return 'V';
        }
        case 10: {
            return 'X';
        }
        case 50: {
            return 'L';
        }
        case 100: {
            return 'C';
        }
        case 500: {
            return 'D';
        }
        case 1000: {
            return 'M';
        }
        default: {
            throw std::logic_error("Could not convert to roman number");
        }
        }
    }

    uint convert_to_exact_decimal(char roman) {
        switch (roman) {
        case 'I': {
            return 1;
        }
        case 'V': {
            return 5;
        }
        case 'X': {
            return 10;
        }
        case 'L': {
            return 50;
        }
        case 'C': {
            return 100;
        }
        case 'D': {
            return 500;
        }
        case 'M': {
            return 1000;
        }
        default: {
            throw std::logic_error("Could not convert to decimal number");
        }
        }
    }

    std::vector<uint> decompose_decimal(uint number) {
        std::string num_str = std::to_string(number);
        std::reverse(num_str.begin(), num_str.end());

        std::vector<uint> vec;

        uint multiplier = 1;
        for (char c : num_str) {
            uint result = c - '0';

            result *= multiplier;

            if (result != 0) {
                vec.push_back(result);
            }

            multiplier *= 10;
        }

        std::reverse(vec.begin(), vec.end());
        return vec;
    }

    std::vector<uint> decompose_decimal_subparts(uint number) {
        std::vector<uint> vec;

        bool subtract = false;

        while (number > 0) {
            uint closest_roman = get_closest_roman(number);
            vec.push_back(closest_roman);

            if (closest_roman > number) {
                subtract = true;
                number = closest_roman - number;
            } else {
                number -= closest_roman;
            }
        }

        if (subtract) {
            std::reverse(vec.begin(), vec.end());
        }
        return vec;
    }

    uint deal_with_the_devil(uint number) {
        std::string num_str = std::to_string(number);

        if (num_str[0] == '8') {
            switch (num_str.size()) {
            case 1: {
                return 5;
            }
            case 2: {
                return 50;
            }
            case 3: {
                return 500;
            }
            }
        }

        throw std::logic_error("No devil to deal with");
    }

    uint get_closest_roman(uint number) {
        try {
            return deal_with_the_devil(number);
        } catch (std::logic_error _err) {
            std::vector<uint> vec = {1, 5, 10, 50, 100, 500, 1000};

            uint closest;
            uint prev_closest_roman;

            int last_result = std::numeric_limits<int>::max();
            for (uint v : vec) {
                int result = v - number;

                if (result < 0) {
                    result = -result; // Make it positive
                }

                if (result < last_result) {
                    closest = v;
                }

                last_result = result;
            }

            return closest;
        }
    }
};

int main(void) {
    auto converter = std::make_unique<RomanNumberConverter>();

    bool main_loop = true;
    while (main_loop) {
        char input;

        std::cout << '\n';
        std::cout << "What do you want to do?" << '\n';
        std::cout << '\n';
        std::cout << "[1] Convert from Decimal to Roman" << '\n';
        std::cout << "[2] Convert from Roman to Decimal" << '\n';
        std::cout << '\n';
        std::cout << "Choice: ";
        std::cin >> input;
        std::cout << '\n';

        switch (input) {
        case '1': {
            uint decimal_input;

            std::cout << "Input: ";
            std::cin >> decimal_input;

            std::cout << "Output: "
                      << converter->decimal_to_roman(decimal_input) << '\n';
            std::cout << '\n';
            break;
        }
        case '2': {
            std::string roman_input;

            std::cout << "Input: ";
            std::cin >> roman_input;

            std::cout << "Output: " << converter->roman_to_decimal(roman_input)
                      << '\n';
            std::cout << '\n';
            break;
        }
        }

        bool continue_loop = true;
        while (continue_loop) {
            std::cout << "Continue? [y/n]: ";
            std::cin >> input;

            switch (input) {
            case 'y': {
                continue_loop = false;
                break;
            }
            case 'n': {
                continue_loop = false;
                main_loop = false;
                break;
            }
            default: {
                break;
            }
            }
        }
    }
}
