#include "main.h"

int main() {
    Watched userMovies;
    std::string movieName;

    std::cout << "Enter a movie name to search: ";
    std::getline(std::cin, movieName);

    int movieID = userMovies.searchMovies(movieName);

    if (movieID != -1) {
        userMovies.getRecs(movieID);
    }

    return 0;
}
