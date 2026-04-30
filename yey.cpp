#include <iostream>
#include <string>
#include <vector>

const char* man[] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
const char* fem[] = {"", "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
const char* teens[] = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать",
                       "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
const char* tens[]  = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят",
                       "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
const char* hunds[] = {"", "сто", "двести", "триста", "четыреста", "пятьсот",
                       "шестьсот", "семьсот", "восемьсот", "девятьсот"};

const int ending[] = {2, 0, 1, 1, 1, 2, 2, 2, 2, 2};

inline int ending_idx(int n) {
    int m = n % 100;
    return (m >= 11 && m <= 14) ? 2 : ending[n % 10];
}

std::string chunk_to_words(int n, bool feminine) {
    int h = n / 100;
    int t = (n / 10) % 10;
    int u = n % 10;

    std::string res;
    if (h) res += std::string(hunds[h]) + ' ';
    
    if (t == 1) {
        res += std::string(teens[u]) + ' ';
    } else {
        if (t) res += std::string(tens[t]) + ' ';
        const char* word = (feminine && u <= 2) ? fem[u] : man[u];
        if (u) res += std::string(word) + ' ';
    }

    if (!res.empty() && res.back() == ' ') res.pop_back();
    return res;
}

std::string num_to_words(int n) {
    if (n == 0) return "ноль";
    if (n < 0) return "минус " + num_to_words(-n);

    std::string out;
    int mil  = n / 1000000;
    int thou = (n / 1000) % 1000;
    int end = n % 1000;

    const char* millions[]  = {"миллион", "миллиона", "миллионов"};
    const char* thousands[] = {"тысяча", "тысячи", "тысяч"};

    if (mil) {
        out += chunk_to_words(mil, false) + " " + millions[ending_idx(mil)];
    }
    if (thou) {
        if (!out.empty()) out += ' ';
        out += chunk_to_words(thou, true) + " " + thousands[ending_idx(thou)];
    }
    if (end) {
        if (!out.empty()) out += ' ';
        out += chunk_to_words(end, false);
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