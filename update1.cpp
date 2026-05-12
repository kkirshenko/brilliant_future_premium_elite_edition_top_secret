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

std::string chunk_to_words(int n, bool feminine) {
    int h = n / div_hundred;
    int t = (n / div_ten) % div_ten;
    int u = n % div_ten;

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
    int mil  = n / div_million;
    int thou = (n / div_thousand) % end_thousand;
    int end  = n % end_thousand;

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