#include "main.h"

int main() {
    Watched userWatched;
    int choice;

    while (true) {
        std::cout << "\n🎬 Movie Recommendation System 🎬\n";
        std::cout << "1. Add a movie to watched list\n";
        std::cout << "2. Show most watched genre\n";
        std::cout << "3. Get recommendations\n";
        std::cout << "4. Show all watched movies\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Prevent input buffer issues

        if (choice == 1) {
            std::string title, genre;
            int rating;

            std::cout << "Enter movie title: ";
            std::getline(std::cin, title);
            std::cout << "Enter movie genre: ";
            std::getline(std::cin, genre);
            std::cout << "Enter your rating (0-100): ";
            std::cin >> rating;

            userWatched.add_movie(Movie(title, genre, rating));
            std::cout << "Movie added successfully!\n";

        } else if (choice == 2) {
            userWatched.count_most();

        } else if (choice == 3) {
            userWatched.getRecs();

        } else if (choice == 4) {
            if (userWatched.watched.empty()) {
                std::cout << "No movies in watchlist.\n";
            } else {
                std::cout << "\nYour Watched Movies:\n";
                for (const auto &movie : userWatched.watched) {
                    std::cout << "- " << movie.movie << " (" << movie.genre << ") - Rating: " << movie.rating << "/10\n";
                }
            }

        } else if (choice == 5) {
            std::cout << "Goodbye!\n";
            break;

        } else {
            std::cout << "Invalid choice. Try again!\n";
        }
    }

    return 0;
}
