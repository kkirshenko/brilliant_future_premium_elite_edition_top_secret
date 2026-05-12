#include <iostream>
#include <string>

const char* man[] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
const char* fem[] = {"", "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
const char* teens[] = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать",
                       "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
const char* tens[]  = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят",
                       "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
const char* hunds[] = {"", "сто", "двести", "триста", "четыреста", "пятьсот",
                       "шестьсот", "семьсот", "восемьсот", "девятьсот"};

const int ending[] = {2, 0, 1, 1, 1, 2, 2, 2, 2, 2};
const char* millions[]  = {"миллион", "миллиона", "миллионов"};
const char* thousands[] = {"тысяча", "тысячи", "тысяч"};

const int div_million = 1000000;
const int div_thousand = 1000;
const int end_thousand = 1000;
const int div_hundred = 100;
const int div_ten = 10;
const int exception_low = 11;
const int exception_high = 14;

inline int ending_idx(int n) {
    int m = n % 100;
    return (m >= exception_low && m <= exception_high) ? 2 : ending[n % div_ten];
}

std::string num_to_words(int n) {
    if (n == 0) return "ноль";
    if (n < 0) return "минус " + num_to_words(-n);

    std::string out;
    int divs[] = {div_million, div_thousand, 1};
    bool feminine[] = {false, true, false};

    for (int i = 0; i < 3; ++i) {
        int chunk = n / divs[i];
        if (chunk) {
            if (!out.empty()) out += ' ';

            int h = chunk / div_hundred;
            int t = (chunk / div_ten) % div_ten;
            int u = chunk % div_ten;

            if (h) out += std::string(hunds[h]) + ' ';
            if (t == 1) {
                out += std::string(teens[u]) + ' ';
            } else {
                if (t) out += std::string(tens[t]) + ' ';
                const char* word = (feminine[i] && u <= 2) ? fem[u] : man[u];
                if (u) out += std::string(word) + ' ';
            }

            if (out.back() == ' ') out.pop_back();

            if (i == 0) out += ' ' + std::string(millions[ending_idx(chunk)]);
            if (i == 1) out += ' ' + std::string(thousands[ending_idx(chunk)]);

            n %= divs[i];
        }
    }
    return out;
}

int main() {
    int n;
    std::cout << "число: ";
    std::cin >> n;
    std::cout << "ответ: " << num_to_words(n) << std::endl;
    return 0;
}