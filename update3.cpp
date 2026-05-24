#include <iostream>
#include <string>

const int man = 0;
const int fem = 1;

const char* words[3][10][2] = {
    {
        {"", ""},
        {"один", "одна"},
        {"два", "две"},
        {"три", "три"},
        {"четыре", "четыре"},
        {"пять", "пять"},
        {"шесть", "шесть"},
        {"семь", "семь"},
        {"восемь", "восемь"},
        {"девять", "девять"}
    },
    {
        {"", ""},
        {"", ""},
        {"двадцать", "двадцать"},
        {"тридцать", "тридцать"},
        {"сорок", "сорок"},
        {"пятьдесят", "пятьдесят"},
        {"шестьдесят", "шестьдесят"},
        {"семьдесят", "семьдесят"},
        {"восемьдесят", "восемьдесят"},
        {"девяносто", "девяносто"}
    },
    {
        {"", ""},
        {"сто", "сто"},
        {"двести", "двести"},
        {"триста", "триста"},
        {"четыреста", "четыреста"},
        {"пятьсот", "пятьсот"},
        {"шестьсот", "шестьсот"},
        {"семьсот", "семьсот"},
        {"восемьсот", "восемьсот"},
        {"девятьсот", "девятьсот"}
    }
};

const char* teens[] = {
    "десять", "одиннадцать", "двенадцать", "тринадцать",
    "четырнадцать", "пятнадцать", "шестнадцать",
    "семнадцать", "восемнадцать", "девятнадцать"
};

const char* suffixes[3][3] = {
    {"миллион", "миллиона", "миллионов"},
    {"тысяча", "тысячи", "тысяч"},
    {"", "", ""}
};

const int divs[] = {1000000, 1000, 1};
const bool feminine[] = {false, true, false};
const int ending[] = {2, 0, 1, 1, 1, 2, 2, 2, 2, 2};

inline int ending_idx(int n) {
    int m = n % 100;
    return (m >= 11 && m <= 14) ? 2 : ending[n % 10];
}

std::string num_to_words(int n) {
    if (n == 0) return "ноль";
    if (n < 0) return "минус " + num_to_words(-n);

    std::string out;

    for (int i = 0; i < 3; ++i) {
        int chunk = n / divs[i];
        if (chunk) {
            if (!out.empty()) out += ' ';

            int h = chunk / 100;
            int t = (chunk / 10) % 10;
            int u = chunk % 10;
            int gender = feminine[i] ? fem : man;

            if (h) out += std::string(words[2][h][man]) + ' ';

            if (t == 1) {
                out += std::string(teens[u]) + ' ';
            } else {
                if (t) out += std::string(words[1][t][man]) + ' ';
                if (u) out += std::string(words[0][u][gender]) + ' ';
            }

            if (out.back() == ' ') out.pop_back();

            out += ' ' + std::string(suffixes[i][ending_idx(chunk)]);

            n %= divs[i];
        }
    }

    while (!out.empty() && out.back() == ' ') out.pop_back();
    return out;
}

int main() {
    int n;
    std::cout << "число: ";
    std::cin >> n;
    std::cout << "ответ: " << num_to_words(n) << std::endl;
    return 0;
}