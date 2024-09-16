#include <iostream>
#include "include/player_types/goalkeeper.h"
#include "include/service.h"
#include "map/map.h"
#include "include/player_types/forward.h"
#include "include/player_types/defender.h"
#include "Application/include/visuals.h"
#include "Application/include/controller.h"

int main() {
    prog::Team team("My Team", "John Doe");
    prog::Service service(team);
    Visuals visuals;
    Controller controller(service, visuals);
    controller.run();

    return 0;
}
