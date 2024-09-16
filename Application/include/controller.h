/**
 * @file controller.h
 * @brief This file contains the Controller class definition.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */
#ifndef MLAB3_CONTROLLER_H
#define MLAB3_CONTROLLER_H

#include "visuals.h"
#include "../../include/service.h"
#include "../../include/player_types/forward.h"
#include "../../include/player_types/defender.h"
#include "../../include/player_types/goalkeeper.h"

/**
 * @class Controller
 * @brief The Controller class is responsible for controlling the flow of the program.
 *
 * This class contains a reference to a Service object and a Visuals object, and provides a method to run the program.
 */
class Controller {
public:
    /**
     * @brief Constructs a new Controller object with references to a Service object and a Visuals object.
     *
     * @param service The Service object to reference
     * @param visuals The Visuals object to reference
     */
    Controller(prog::Service& service, Visuals& visuals);

    /**
     * @brief Runs the program.
     */
    void run();

private:
    prog::Service& service_;    /**< The Service object referenced by the Controller object */
    Visuals& visuals_;          /**< The Visuals object referenced by the Controller object */
};

#endif //MLAB3_CONTROLLER_H
