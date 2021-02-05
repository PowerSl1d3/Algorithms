#include <iostream>
#include <cstdint>
#include <vector>
#include <utility>

//ID удачной посылки: 47961770

std::vector<uint32_t> get_street_from_cin() {

    uint32_t count;
    std::cin >> count;

    std::vector<uint32_t> houses(count);

    for (uint32_t& house : houses) {
        std::cin >> house;
    }

    return houses;

}


//[0, 1, 1, 1] -> [0, 1, 2, 3]
void fill_by_ascending(const std::pair<uint32_t, uint32_t>& range, std::vector<uint32_t>& street) {

    uint32_t filler = 1;
    for (size_t i = range.first + 1; i <= range.second; i++) {
        street[i] = filler++;
    }

}

//[1, 1, 1, 0] -> [3, 2, 1, 0]
void fill_by_descending(const std::pair<uint32_t, uint32_t>& range, std::vector<uint32_t>& street) {

    uint32_t filler = 1;
    for (size_t i = range.second; i >= range.first + 1; i--) {
        street[i - 1] = filler++;
    }

}

//[0, 1, 1, 1, 0] -> [0, 1, 2, 1, 0]
void fill_by_ascending_and_descending(const std::pair<uint32_t, uint32_t>& range, std::vector<uint32_t>& street) {

    if (range.second - range.first + 1 <= 2) {
        return;
    }

    size_t middle = range.first + (range.second - range.first) / 2;
    uint32_t filler = 1;
    for (size_t i = range.first + 1; i <= middle; i++) {
        street[i] = filler++;
    }
    filler = 1;
    for (size_t i = range.second - 1; i > middle; i--) {
        street[i] = filler++;
    }
}


void fill_distance_between_free_houses(std::pair<uint32_t, uint32_t> pair, std::vector<uint32_t>& street) {


        if (street[pair.first] == 0 && street[pair.second] == 0) {
            fill_by_ascending_and_descending(pair, street);
        } else if (street[pair.first] == 0) {
            fill_by_ascending(pair, street);
        } else {
            fill_by_descending(pair, street);
        }

}

//[1, 5, 0, 8, 0, 9, 10] -> [[1, 5, 0], [0, 8, 0], [0, 9, 10]] -> [2, 1, 0, 1, 0, 1, 2]
std::vector<uint32_t> compute_distance_between_free_houses(const std::vector<uint32_t>& street) {

    std::vector<uint32_t> street_with_distance_between_free_houses = street;

    uint32_t prev_zero_index = 0;
    for (size_t i = 1; i < street.size() - 1; i++ ) {
        if (street[i] == 0) {
            fill_distance_between_free_houses({prev_zero_index, i}, street_with_distance_between_free_houses);
            prev_zero_index = i;
        }
    }

    fill_distance_between_free_houses({prev_zero_index, street.size() - 1}, street_with_distance_between_free_houses);

    return street_with_distance_between_free_houses;


}

void print_street(const std::vector<uint32_t>& street) {

    for (const uint32_t house : street) {
        std::cout << house << ' ';
    }

}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const std::vector<uint32_t> street = get_street_from_cin();

    const std::vector<uint32_t> street_with_distance_between_free_houses = compute_distance_between_free_houses(street);

    print_street(street_with_distance_between_free_houses);

    return 0;
}
