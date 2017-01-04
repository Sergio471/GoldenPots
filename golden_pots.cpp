#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <string>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <cstring>
#include <sstream>

typedef std::vector<std::pair<int, bool>> row_t;
typedef std::vector<row_t> mem_t;
static mem_t mem;

static const float MISTAKE_EPS = 0.03;
static const float BALANCE_EPS = 0.05;

void print(const std::vector<int> &pots, int s, int e) {
    auto dig_cnt = [](int n) { int c = 0; while (n) { n /= 10; ++c; } return c;};
    std::stringstream ss;
    for (int i = 0; i < pots.size(); ++i) {
        if (i < s) ss << std::string(dig_cnt(pots[i]) + 1, ' ');
        else if (i >= s && i <= e) ss << " " << pots[i];
        else ss << std::string(dig_cnt(pots[i]) + 1, ' ');
    }
    std::string pref = "Current State: ";
    std::string gold_str = ss.str();
    std::cout << std::string(pref.size() + gold_str.size(), '-') << std::endl;
    std::cout << pref << gold_str << std::endl;
}

void clear_dp_memo() {
    for (auto &r : mem) {
        for (auto &p : r) {
            p.first = -1;
            p.second = false;
        }
    }
}

int predict_score(const std::vector<int>& pots, int s, int e, bool& left_move) {

    if (s > e) return 0;
    if (mem[s][e].first != -1) {
        left_move = mem[s][e].second;
        return mem[s][e].first;   
    }

    bool tmp = false;
    int left = pots[s] + std::min(predict_score(pots, s + 1, e - 1, tmp), predict_score(pots, s + 2, e, tmp));
    int right = pots[e] + std::min(predict_score(pots, s, e - 2, tmp), predict_score(pots, s + 1, e - 1, tmp));

    float eps = ((float)std::abs(left - right)) / std::max(left, right);
    left_move = (eps > MISTAKE_EPS ? left > right : std::rand() % 2);
    mem[s][e].second = left_move;

    return mem[s][e].first = std::max(left, right);
}

bool is_left_move(const std::vector<int>& pots, int& s, int& e, bool& player_turn) {
    if (player_turn) {
        std::cout << "Player is taking: ";
        std::string command;
        std::cin >> command;
        while (command != "left" && command != "right") {
            std::cout << "Correct commands: \"left\" or \"right\" without quotes." << std::endl;
            std::cout << "Player is taking: ";
            std::cin >> command;
        }
        return command == "left";
    } else {
        std::cout << "AI is taking: ";
        bool left_move = false;
        predict_score(pots, s, e, left_move);
        return left_move;
    } 
}

void play_round(const std::vector<int>& pots, int& s, int& e, bool& player_turn, int& score) {
    print(pots, s, e);

    bool left_move = is_left_move(pots, s, e, player_turn);
    if (!player_turn) std::cout << (left_move ? "left" : "right") << std::endl;

    if (left_move)
        score += pots[s++];
    else
        score += pots[e--];
    player_turn = !player_turn;
}

void play(const std::vector<int> &pots) {
    int player_score = 0;
    int ai_score = 0;

    int s = 0, e = pots.size() - 1;
    bool player_turn = std::rand() % 2;
    while (s <= e) {
        int &score = (player_turn ? player_score : ai_score);
        play_round(pots, s, e, player_turn, score);
    }
    std::cout << "Player score: " << player_score << std::endl;
    std::cout << "AI score: " << ai_score << std::endl;
}

bool well_balanced(const std::vector<int>& pots) {
    int sum = std::accumulate(pots.begin(), pots.end(), 0);
    bool tmp = false;
    int best_score = predict_score(pots, 0, pots.size() - 1, tmp);
    clear_dp_memo();
    float eps = ((float)std::abs(best_score * 2 - sum)) / std::max(best_score, sum);
    if (eps > BALANCE_EPS) return false;
    return true;
}

void generate(std::vector<int>& pots, int MAX) {
    for (auto &p : pots) p = std::rand() % MAX + 1;
}

int main(int argc, char* argv[])
{
    if (argc == 2 && std::strcmp("help", argv[1]) == 0) {
        std::cout << "Usage: ./program_name num_of_pots max_gold_in_pot." << std::endl;
        std::cout << "Params num_of_pots and max_gold_in_pot are optional." << std::endl;
        return 0;
    }

    std::cout << "There are pots with gold coins in them." << std::endl;
    std::cout << "In order to win, you should collect more gold than AI does." << std::endl;
    std::cout << "You and AI can collect gold only from left most or right most of the remaining pots." << std::endl;
    std::cout << "At each step, row of numbers represents number of gold coins in pots." << std::endl;

    std::srand(std::time(0));

    int N = 10;
    int MAX = 10;
    if (argc > 1) N = std::max(3, atoi(argv[1]));
    if (argc > 2) MAX = std::max(1, atoi(argv[2]));

    mem.resize(N, row_t(N, {-1, false}));

    std::vector<int> pots(N, 0);
    generate(pots, MAX);
    while (!well_balanced(pots)) generate(pots, MAX);

    play(pots);

    return 0;
}
