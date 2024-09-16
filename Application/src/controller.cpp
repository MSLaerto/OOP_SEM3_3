#include "../include/controller.h"

Controller::Controller(prog::Service& service, Visuals& visuals)
        : service_(service), visuals_(visuals) {}

void Controller::run() {
    while (true) {
        visuals_.displayMainMenu();
        int choice = visuals_.getUserChoice();

        try {
            switch (choice) {
                case 1: {
                    auto date = visuals_.getDate();
                    auto opponent = visuals_.getOpponentTeam();
                    auto quantity = visuals_.getQuantity();

                    std::vector<std::shared_ptr<prog::Player>> players;

                    for (std::size_t i = 0; i < quantity; ++i) {
                        auto playerType = visuals_.getPlayerType();
                        std::string fullName;
                        std::size_t gameTime, penaltyTime;

                        std::cout << "Enter full name for player " << i + 1 << ": ";
                        std::cin.ignore();
                        std::getline(std::cin, fullName);

                        std::cout << "Enter game time for player " << i + 1 << ": ";
                        gameTime = getNum<std::size_t>();

                        std::cout << "Enter penalty time for player " << i + 1 << ": ";
                        penaltyTime = getNum<std::size_t>();

                        if (playerType == "Defender") {
                            players.push_back(std::make_shared<prog::Defender>(fullName, gameTime, penaltyTime));
                        } else if (playerType == "Forward") {
                            std::size_t shotsOnTarget, shotsOffTarget;

                            std::cout << "Enter shots on target for player " << i + 1 << ": ";
                            shotsOnTarget = getNum<std::size_t>();

                            std::cout << "Enter shots off target for player " << i + 1 << ": ";
                            shotsOffTarget = getNum<std::size_t>();

                            players.push_back(std::make_shared<prog::Forward>(fullName, gameTime, penaltyTime, shotsOnTarget, shotsOffTarget));
                        } else if (playerType == "Goalkeeper") {
                            std::size_t saves, goalsConceded;

                            std::cout << "Enter saves for player " << i + 1 << ": ";
                            saves = getNum<std::size_t>();

                            std::cout << "Enter goals conceded for player " << i + 1 << ": ";
                            goalsConceded = getNum<std::size_t>();

                            players.push_back(std::make_shared<prog::Goalkeeper>(fullName, gameTime, penaltyTime, saves, goalsConceded));
                        } else {
                            throw std::runtime_error("Invalid player type");
                        }
                    }

                    service_.add_game(date, opponent, quantity, players);
                    break;
                }

                case 2: {
                    auto date = visuals_.getDate();
                    service_.remove_game(date);
                    break;
                }
                case 3: {
                    auto date = visuals_.getDate();
                    auto opponent = visuals_.getOpponentTeam();
                    auto quantity = visuals_.getQuantity();
                    service_.modify_game(date, opponent, quantity);
                    break;
                }
                case 4: {
                    auto date = visuals_.getDate();
                    auto penalty = service_.calculate_total_penalty_time(date);
                    std::stringstream ss;
                    auto t = std::chrono::system_clock::to_time_t(date);
                    ss << "Total penalty time on " << std::ctime(&t)
                       << " is " << penalty << " seconds.";
                    visuals_.displayServiceInfo(ss.str());
                    break;
                }
                case 5: {
                    visuals_.displayServiceInfo(service_.print_players_info());
                    break;
                }
                case 6: {
                    auto mostActivePlayers = service_.get_most_active_players_single_threaded();
                    visuals_.displayMostActivePlayers(mostActivePlayers, "Most active players (single-threaded)");
                    break;
                }
                case 7: {
                    auto mostActivePlayers = service_.get_most_active_players_multithreaded();
                    visuals_.displayMostActivePlayers(mostActivePlayers, "Most active players (multi-threaded)");
                    break;
                }
                case 0:
                    return;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}