//
// Created by nikita on 19.12.24.
//
#include "TerminalRender.h"

void TerminalRender::RenderField(GamingField *field) {
    if (field == nullptr){
        std::cout << "Error: Nothing to show!\n";
        return;
    }
    if (field->GetOwner() == OwnerField::kMyField) {
        std::cout << "Your Field:\n";
    }
    else{
        std::cout << "Opponent Field:\n";
    }
    for (size_t i = 0; i<field->GetHorizontalLen()+1; ++i){
        std::cout << "[" << i << "] ";
    }
    std::cout << "\n";
    size_t h_column = 1;
    size_t row = 1;
    for (std::vector<Cell>& i : field->GetCells()){
        if (h_column < 10) {
            std::cout << "[" << h_column++ << "] ";
        }
        else {
            std::cout << "[" << h_column++ << "]";
        }
        for (Cell& j : i){
            row++;
            if (row >=10) {
                std::cout << " " <<static_cast<char>(j.status) << "  ";
            }
            else {
                std::cout << " " <<static_cast<char>(j.status) << "  ";
            }
        }
        std::cout << '\n';
    }
    std::cout << "-----------------------------------\n";
}

void TerminalRender::RenderManager(Manager *manager, RenderObjectType type) {
    if (manager == nullptr){
        std::cout << "Error: Nothing to show!\n";
        return;
    }
    if (type == RenderObjectType::kUserManager) {
        std::cout << "Your ships: \n";
    }
    else if (type == RenderObjectType::kOpponentManager){
        std::cout << "Opponent ships: \n";
    }
    size_t nums_ships = manager->GetNumsOfShips();
    size_t boat_len;
    OrientationType orientation;
    for (size_t i=0; i<nums_ships; ++i){
       Ship& boat = manager->GetShip(i);
       boat_len = boat.Len();
       orientation = boat.GetOrientation();
       std::cout << "Length of ship: " << boat_len << "\n";
       if (orientation == OrientationType::kVertical){
          std::cout << "Orientation of ship: Vertical\n";
       }
       else if (orientation == OrientationType::kHorizontal){
          std::cout << "Orientation of ship: Horizontal\n";
       }
       std::cout << "Ship status: \n";
       for (size_t id_cells = 0; id_cells < boat_len; ++id_cells){
           if (boat.GetStatus(id_cells) ==SegmentStatus::kFullHealth) std::cout << "---- " << id_cells << " cell: Full Health\n";
           else if(boat.GetStatus(id_cells) == SegmentStatus::kHalfHealth) std::cout << "---- " << id_cells << " cell: Half Health\n";
           else std::cout << "---- " << id_cells << " cell: Destroyed\n";
       }
    }
}

void TerminalRender::GameOverText() {
    std::cout<< "  _______      ___      .___  ___.  _______      ______   ____    ____  _______ .______       __  \n"
                " /  _____|    /   \\     |   \\/   | |   ____|    /  __  \\  \\   \\  /   / |   ____||   _  \\     |  | \n"
                "|  |  __     /  ^  \\    |  \\  /  | |  |__      |  |  |  |  \\   \\/   /  |  |__   |  |_)  |    |  | \n"
                "|  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|     |  |  |  |   \\      /   |   __|  |      /     |  | \n"
                "|  |__| |  /  _____  \\  |  |  |  | |  |____    |  `--'  |    \\    /    |  |____ |  |\\  \\----.|__| \n"
                " \\______| /__/     \\__\\ |__|  |__| |_______|    \\______/      \\__/     |_______|| _| `._____|(__) \n";
}

void TerminalRender::VictoryText() {
    std::cout <<"____    ____  ______    __    __     ____    __    ____  __  .__   __.    .______        ______    __    __  .__   __.  _______   __  \n"
                "\\   \\  /   / /  __  \\  |  |  |  |    \\   \\  /  \\  /   / |  | |  \\ |  |    |   _  \\      /  __  \\  |  |  |  | |  \\ |  | |       \\ |  | \n"
                " \\   \\/   / |  |  |  | |  |  |  |     \\   \\/    \\/   /  |  | |   \\|  |    |  |_)  |    |  |  |  | |  |  |  | |   \\|  | |  .--.  ||  | \n"
                "  \\_    _/  |  |  |  | |  |  |  |      \\            /   |  | |  . `  |    |      /     |  |  |  | |  |  |  | |  . `  | |  |  |  ||  | \n"
                "    |  |    |  `--'  | |  `--'  |       \\    /\\    /    |  | |  |\\   |    |  |\\  \\----.|  `--'  | |  `--'  | |  |\\   | |  '--'  ||__| \n"
                "    |__|     \\______/   \\______/         \\__/  \\__/     |__| |__| \\__|    | _| `._____| \\______/   \\______/  |__| \\__| |_______/ (__) \n";
}

void TerminalRender::SignalMessage(OwnerField type) {
    if (type == OwnerField::kOpponentsField){
        std::cout << "\nOpponent is playing...\n";
    }
    else{
        std::cout << "\nYour turn:\n";
    }
}