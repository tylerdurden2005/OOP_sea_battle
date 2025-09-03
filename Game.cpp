#include "Game.h"
void Game::CheckValue(int &value) {
    std::string input;
    while(true){
        std::getline(std::cin, input);
        try{
            int v = std::stoi(input);
            std::string res = std::to_string(v);
            if (res.size() != input.size()) {
                throw std::invalid_argument("");
            }
            if (v>500){
                throw std::out_of_range("");
            }
            if (v <= 0){
                std::cout << "Wrong: value can't be <= 0. Try again:\n";
                std::cin.clear();
                std::cin.sync();
            }
            else{
                value = v;
                break;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Wrong: the type of your value are not int. Try again:\n";
            std::cin.clear();
            std::cin.sync();
        }
        catch (const std::out_of_range& e){
            std::cout << "Wrong: your value is too much for this game! Maximum = 1000. Try again:\n";
            std::cin.clear();
            std::cin.sync();
        }
    }
}

void Game::GenerateOpponentsCoord(std::vector<Coordinates> &ships_coord, TypeGenerateCoordinates flag) {
    size_t x, y;
    OrientationType orientation;
    for (size_t i=0; i<ships_coord.size(); ++i){
        orientation = game_status.user_manager->GetShip(i).GetOrientation();
        size_t len = game_status.user_manager->GetShip(i).Len();
        if (flag==TypeGenerateCoordinates::kRotateRightAngle){
            y = ships_coord[i].x;
            if (orientation == OrientationType::kHorizontal){
                x = game_status.user_field->GetVerticalLen() - ships_coord[i].y + 1;
            }
            else{
                x = game_status.user_field->GetVerticalLen() - (ships_coord[i].y + len -1) +1;
            }
        }
        else if (flag==TypeGenerateCoordinates::kRotateStraightAngle){
            if (orientation == OrientationType::kHorizontal){
                x = game_status.user_field->GetHorizontalLen() - (ships_coord[i].x + len - 1) +1;
                y = game_status.user_field->GetVerticalLen() - ships_coord[i].y + 1;
            }
            else{
                x = game_status.user_field->GetHorizontalLen()-ships_coord[i].x +1;
                y = game_status.user_field->GetVerticalLen() - (ships_coord[i].y + len -1) +1;
            }
        }
        else if (flag==TypeGenerateCoordinates::kInvertX){
            y = ships_coord[i].y;
            if (orientation == OrientationType::kHorizontal){
                x = game_status.user_field->GetHorizontalLen() - (ships_coord[i].x + len - 1) +1;
            }
            else{
                x = game_status.user_field->GetHorizontalLen() - ships_coord[i].x +1;
            }
        }
        else { //kInvertY
            x = ships_coord[i].x;
            if (orientation == OrientationType::kHorizontal){
                y = game_status.user_field->GetVerticalLen() - ships_coord[i].y +1;
            }
            else{
                y = game_status.user_field->GetVerticalLen() - (ships_coord[i].y + len -1) +1;
            }
        }
        ships_coord[i].x = x;
        ships_coord[i].y = y;
    }
}

void Game::CreateUser() {
    /*std::vector<Coordinates> ships_coord;
    game_status.user_field = new GamingField(3, 3);
    std::vector<size_t> lens = {1, 3};
    game_status.user_manager = new Manager(2, lens);
    game_status.user_field->AddShip(game_status.user_manager->GetShip(0), {1, 1}, OrientationType::kHorizontal);
    game_status.user_field->AddShip(game_status.user_manager->GetShip(1), {1, 3}, OrientationType::kHorizontal);
    //user_field->AddShip(user_manager->GetShip(2), {1, 4}, OrientationType::kVertical);
    ships_coord = {{1, 1}, {1, 3}};
    game_status.alive_user_ships = game_status.user_manager->GetNumsOfShips();
    std::vector<std::vector<Cell>>& user_cells = game_status.user_field->GetCells();
    for (size_t i=0; i<user_cells.size(); ++i){
        for (size_t j=0; j<user_cells[i].size(); ++j){
            game_status.user_cells_for_attack.push_back({j+1, i+1});
        }
    }*/

    int vertical_length;
    int horizontal_length;
    std::cout << "The first step. Please enter the width and height of the field.\n";
    std::cout << "  1) Enter the height of the field in the form: height\n";
    CheckValue(vertical_length);
    std::cout << "  2) Enter the width of the field in the form: width\n";
    CheckValue(horizontal_length);
    game_status.user_field = new GamingField(static_cast<size_t>(horizontal_length), static_cast<size_t>(vertical_length));
    std::cout << "Correct: Field has been created!\n\n";
    std::cout << "The second step. Let's go create ships. Enter the number of ships in form: number\n";
    int nums_of_ship;
    CheckValue(nums_of_ship);
    std::cout << "Correct. Now enter the sizes of the ships (size can be 1, 2, 3, 4) in form: one size in one row via enter\n";
    std::vector<size_t> lens_of_ships(static_cast<size_t>(nums_of_ship));
    for (size_t i = 0; i<static_cast<size_t>(nums_of_ship); ++i){
        int value;
        while(true){
            CheckValue(value);
            if (value <= 4){
                break;
            }
            else{
                std::cout<<"Warning: the impossible length of the ship! Try again:\n";
            }
        }
        lens_of_ships[i] = static_cast<size_t>(value);
        std::cout << "The ship #" << i+1 << " has been created.\n";
    }
    game_status.user_manager = new Manager(static_cast<size_t>(nums_of_ship), lens_of_ships);
    std::cout << "\nThe third step. Let's go arrange our ships. Enter coordinates and orientations.\n";
    std::cout << "Coordinates: {x, y} start from 1. Orientation can be 'Vertical' or 'Horizontal'.\n";
    size_t i =0;
    size_t attempt = 0;
    std::vector<Coordinates> ships_coord;
    while(i < nums_of_ship){
        Coordinates coord_of_ship{};
        int x, y;
        Ship& the_boat = game_status.user_manager->GetShip(i);
        std::cout << "| For the ship #" << i+1 << " his length: " << the_boat.Len()  <<" | enter coordinates in form: one value in one row via enter like width and height.\n";
        std::cout << "  Enter x:\n";
        CheckValue(x);
        coord_of_ship.x = x;
        std::cout << "  Enter y:\n";
        CheckValue(y);
        coord_of_ship.y = y;
        std::cout <<"  Enter orientation like word: 'Vertical' or 'Horizontal':\n ";
        std::string word;
        OrientationType ship_orientation;
        while (true){
            std::getline(std::cin, word);
            if (word == "Vertical" || word == "vertical"){
                ship_orientation = OrientationType::kVertical;
                break;
            }
            else if (word == "Horizontal" || word == "horizontal"){
                ship_orientation = OrientationType::kHorizontal;
                break;
            }
            else{
                std::cout << "Warning: it's not orientation. Try again:\n";
                std::cin.sync();
            }
        }
        try{
            game_status.user_field->AddShip(the_boat, coord_of_ship, ship_orientation);
            std::cout << "The ship #" << i+1 << " his length: " <<  the_boat.Len() <<" has been arranged, coordinates: {"<<coord_of_ship.x << ", " << coord_of_ship.y << "}, orientation: " << word << "\n";
            ships_coord.push_back(coord_of_ship);
            i++;
            attempt = 0;
        }
        catch (const ProgramErrors& e){
            if (attempt >= 2){
                attempt = 0;
                game_status.user_manager->DeleteShipById(i);
                if (i+1 < nums_of_ship){
                    std::cout << "\nThis ship can't add on field. Try next:\n\n";
                }
                nums_of_ship--;
            }
            else{
                std::cout << "Try again:\n";
                attempt++;
            }
        }
    }
    std::vector<std::vector<Cell>>& user_cells = game_status.user_field->GetCells();
    for (size_t id=0; id<user_cells.size(); ++id){
        for (size_t j=0; j<user_cells[i].size(); ++j){
            game_status.user_cells_for_attack.push_back({j+1, id+1});
        }
    }
    game_status.alive_user_ships = game_status.user_manager->GetNumsOfShips();
    game_status.user_ships_coords = ships_coord;
    game_status.opponent_ships_coords = game_status.user_ships_coords;
    std::cout << "\nAll object was create! You ready for game!\n";
}

void Game::CreateOpponent(AgeOpponent flag) {
    size_t num_opponent_ships = game_status.user_manager->GetNumsOfShips();
    game_status.alive_opponent_ships = num_opponent_ships;
    std::vector<size_t> lens_of_ships(num_opponent_ships);
    std::vector<OrientationType> user_orientations(num_opponent_ships);
    for (size_t i=0; i<num_opponent_ships; ++i){
        lens_of_ships[i] = game_status.user_manager->GetShip(i).Len();
        user_orientations[i] = game_status.user_manager->GetShip(i).GetOrientation();
    }
    game_status.opponent_manager = new Manager(num_opponent_ships, lens_of_ships);
    size_t weight_for_opponents_field = game_status.user_field->GetHorizontalLen();
    size_t height_for_opponents_field = game_status.user_field->GetVerticalLen();
    game_status.opponent_field = new GamingField(weight_for_opponents_field, height_for_opponents_field, OwnerField::kOpponentsField);
    std::srand(time(nullptr));
    size_t random_field;
    if (weight_for_opponents_field != 1 && height_for_opponents_field != 1){
        if (weight_for_opponents_field == height_for_opponents_field){
            random_field = std::rand() % 6;
            if (random_field==0){
                GenerateOpponentsCoord(game_status.opponent_ships_coords, TypeGenerateCoordinates::kRotateRightAngle);
            }
            else if (random_field==1){
                GenerateOpponentsCoord(game_status.opponent_ships_coords, TypeGenerateCoordinates::kRotateStraightAngle);
            }
            else if (random_field==2){
                GenerateOpponentsCoord(game_status.opponent_ships_coords, TypeGenerateCoordinates::kRotateStraightAngle);
                GenerateOpponentsCoord(game_status.opponent_ships_coords, TypeGenerateCoordinates::kRotateRightAngle);
            }
            else if (random_field==3){
                GenerateOpponentsCoord(game_status.opponent_ships_coords, TypeGenerateCoordinates::kInvertX);
            }
            else if (random_field==4){
                GenerateOpponentsCoord(game_status.opponent_ships_coords, TypeGenerateCoordinates::kInvertY);
            }
            if (random_field == 0 || random_field == 2){
                for (auto& i : user_orientations){
                    if (i==OrientationType::kVertical){
                        i = OrientationType::kHorizontal;
                    }
                    else i = OrientationType::kVertical;
                }
            }
        }
        else{
            random_field = std::rand() % 4;
            if (random_field==0){
                GenerateOpponentsCoord(game_status.opponent_ships_coords, TypeGenerateCoordinates::kRotateStraightAngle);
            }
            else if (random_field==1){
                GenerateOpponentsCoord(game_status.opponent_ships_coords, TypeGenerateCoordinates::kInvertX);
            }
            else if (random_field==2){
                GenerateOpponentsCoord(game_status.opponent_ships_coords, TypeGenerateCoordinates::kInvertY);
            }
        }
    }
    for (size_t i=0; i<game_status.opponent_ships_coords.size(); ++i){
        game_status.opponent_field->AddShip(game_status.opponent_manager->GetShip(i), game_status.opponent_ships_coords[i], user_orientations[i]);
    }
    if (flag == AgeOpponent::kNewOpponent){
        game_status.user_abilities = new AbilitiesManager(game_status.opponent_field, game_status.opponent_manager);
    }
    else game_status.user_abilities->ChangePointers(game_status.opponent_field, game_status.opponent_manager);
}

void Game::OpponentTurn() {
    //std::cout << "\nOpponent is playing...\n";
    size_t random_coord;
    std::srand(time(nullptr));
    bool flag_continued_attack = true;
    Coordinates coord_for_attack{};
    while(flag_continued_attack){
        random_coord = std::rand() % game_status.user_cells_for_attack.size();
        coord_for_attack = game_status.user_cells_for_attack[random_coord];
        if (game_status.user_field->GetCells()[coord_for_attack.y-1][coord_for_attack.x-1].status == StatusCellOnField::kShip){
            flag_continued_attack = true;
        }
        else{
            flag_continued_attack = false;
        }
        bool flag_destroy = game_status.user_field->Attack(coord_for_attack);
        if (flag_destroy){
            --game_status.alive_user_ships;
        }
        if (game_status.user_field->GetCells()[coord_for_attack.y-1][coord_for_attack.x-1].status == StatusCellOnField::kBoom){
            game_status.user_cells_for_attack.erase(game_status.user_cells_for_attack.begin() + random_coord);
        }
        if (flag_continued_attack && game_status.alive_user_ships==0){
            flag_continued_attack = false;
        }
    }
    //game_status.user_field->PrintField();
}

void Game::UserTurn() {
    //std::cout << "\nYour turn:\n";
    bool flag_continued_attack  = true;
    int x, y;
    Coordinates coord_for_attack{};
    while(flag_continued_attack){
        TypesAbility type = game_status.user_abilities->CurrentAbility();
        std::cout << "If you want simple attack: press enter, else write Use!\n";
        std::string input;
        std::getline(std::cin, input);
        while (!input.empty() && input != "Use" && input != "use"){
            std::cout << "You entered an unknown command: ";
            std::cout << input  << "\n";
            std::cin.clear();
            std::cin.sync();
            std::getline(std::cin, input);
        }
        if (input.empty()) {
            std::cout << "enter x:\n";
            CheckValue(x);
            std::cout << "enter y:\n";
            CheckValue(y);
            coord_for_attack.x = x;
            coord_for_attack.y = y;
            try {
                bool flag_destroy = game_status.opponent_field->Attack(coord_for_attack);
                if (flag_destroy) {
                    game_status.user_abilities->AddAbility();
                    --game_status.alive_opponent_ships;
                }
                if (game_status.opponent_field->GetCells()[coord_for_attack.y-1][coord_for_attack.x-1].status == StatusCellOnField::kEmpty){
                    flag_continued_attack  = false;
                }
                else flag_continued_attack  = true;
            }
            catch (ProgramErrors &e) {
                std::cout << e.what();
                std::cout << "Never done! Try again:\n";
            }
        }
        else {
            size_t nums_of_abilities_before = game_status.user_abilities->GetQueueSize();
            size_t nums_abilities_after;
            if (type == TypesAbility::kBombing) {
                game_status.user_abilities->UseSKill();
                flag_continued_attack = false;
            }
            else{
                std::cout << "enter x:\n";
                CheckValue(x);
                std::cout << "enter y:\n";
                CheckValue(y);
                coord_for_attack.x = x;
                coord_for_attack.y = y;
                try {
                    game_status.user_abilities->UseSKill(coord_for_attack);
                    flag_continued_attack = false;
                }
                catch (ProgramErrors &e) {
                    std::cout << "Ability didn`t work!\n";
                    std::cout << e.what();
                    std::cout << "Try again:\n";
                }
            }
            nums_abilities_after = game_status.user_abilities->GetQueueSize();
            if (nums_of_abilities_before!=0 && nums_abilities_after == nums_of_abilities_before){
                --game_status.alive_opponent_ships;
            }
        }
        if (flag_continued_attack && game_status.alive_opponent_ships==0){
            flag_continued_attack = false;
        }
        //game_status.opponent_field->PrintField();
    }
}

/*
UserChoice Game::UserTurn() {
    std::cout << "\nYour turn:\n";
    bool flag_continued_attack  = true;
    int x, y;
    Coordinates coord_for_attack{};
    while(flag_continued_attack){
        TypesAbility type = game_status.user_abilities->CurrentAbility();
        std::cout << "If you want simple attack: press enter, else write Use!\n";
        std::string input;
        std::getline(std::cin, input);
        while (!input.empty() && input != "Use" && input != "use" && input != "Save" && input != "Load"){
            std::cout << "You entered an unknown command: ";
            std::cout << input  << "\n";
            std::cin.clear();
            std::cin.sync();
            std::getline(std::cin, input);
        }
        if (input == "Save"){
            return UserChoice::kSave;
        }
        else if (input == "Load"){
            return UserChoice::kLoad;
        }
        else if (input.empty()) {
            std::cout << "enter x:\n";
            CheckValue(x);
            std::cout << "enter y:\n";
            CheckValue(y);
            coord_for_attack.x = x;
            coord_for_attack.y = y;
            try {
                bool flag_destroy = game_status.opponent_field->Attack(coord_for_attack);
                if (flag_destroy) {
                    game_status.user_abilities->AddAbility();
                    --game_status.alive_opponent_ships;
                }
                if (game_status.opponent_field->GetCells()[coord_for_attack.y-1][coord_for_attack.x-1].status == StatusCellOnField::kEmpty){
                    flag_continued_attack  = false;
                }
                else flag_continued_attack  = true;
            }
            catch (ProgramErrors &e) {
                std::cout << e.what();
                std::cout << "Never done! Try again:\n";
            }
        }
        else {
            size_t nums_of_abilities_before = game_status.user_abilities->GetQueueSize();
            size_t nums_abilities_after;
            if (type == TypesAbility::kBombing) {
                game_status.user_abilities->UseSKill();
                flag_continued_attack = false;
            }
            else{
                std::cout << "enter x:\n";
                CheckValue(x);
                std::cout << "enter y:\n";
                CheckValue(y);
                coord_for_attack.x = x;
                coord_for_attack.y = y;
                try {
                    game_status.user_abilities->UseSKill(coord_for_attack);
                    flag_continued_attack = false;
                }
                catch (ProgramErrors &e) {
                    std::cout << "Ability didn`t work!\n";
                    std::cout << e.what();
                    std::cout << "Try again:\n";
                }
            }
            nums_abilities_after = game_status.user_abilities->GetQueueSize();
            if (nums_of_abilities_before!=0 && nums_abilities_after == nums_of_abilities_before){
                --game_status.alive_opponent_ships;
            }
        }
        if (flag_continued_attack && game_status.alive_opponent_ships==0){
            flag_continued_attack = false;
        }
        game_status.opponent_field->PrintField();
    }
    return UserChoice::kContinue;
}
*/

/*
void Game::Rounds(TypeOfGame flag) {
    ResultOfRound status = ResultOfRound::kUserWin;
    while(status==ResultOfRound::kUserWin){
        status = NewRound();
        if (status==ResultOfRound::kUserWin){
            std::cout << "\nYou can Continue/End/Save/Load game!\n";
            std::cout << "Just write command: \n";
            std::string input;
            std::getline(std::cin, input);
            while (input != "Continue"  && input != "Save" && input != "Load" &&  input != "End"){
                std::cout << "You entered an unknown command: ";
                std::cout << input  << "\n";
                std::cin.clear();
                std::cin.sync();
                std::getline(std::cin, input);
            }
            if (input == "Continue"){
                game_status.opponent_ships_coords = game_status.user_ships_coords;
                game_status.ClearOpponent();
                CreateOpponent(AgeOpponent::kRestartOpponent);
                continue;
            }
            else if(input == "Save") status = ResultOfRound::kUserWantSave;
            else if (input == "Load") status = ResultOfRound::kUserWantLoad;
            else status = ResultOfRound::kEndGame;

            if (status == ResultOfRound::kUserWantSave){
                std::cout << "\nSaving....\n";
                SaveGame();
                std::cout << "\nYou can Continue/End!\n";
                std::cout << "Just write command: \n";
                while (input != "Continue" && input != "End"){
                    std::cout << "You entered an unknown command: ";
                    std::cout << input  << "\n";
                    std::cin.clear();
                    std::cin.sync();
                    std::getline(std::cin, input);
                }
                if (input == "Continue"){
                    game_status.opponent_ships_coords = game_status.user_ships_coords;
                    game_status.ClearOpponent();
                    CreateOpponent(AgeOpponent::kRestartOpponent);
                    status = ResultOfRound::kUserWin;
                }
                else status = ResultOfRound::kEndGame;
            }
        }
    }
    if (status==ResultOfRound::kUserWantLoad){
        LoadGame();
    }
    else if (status == ResultOfRound::kEndGame){
        Finish();
    }
    else if (status==ResultOfRound::kUserWantSave){
        std::string input;
        std::cout << "\nSaving....\n";
        SaveGame();
        std::cout << "\nYou can Continue/End!\n";
        std::cout << "Just write command: \n";
        while (input != "Continue" && input != "End"){
            std::cout << "You entered an unknown command: ";
            std::cout << input  << "\n";
            std::cin.clear();
            std::cin.sync();
            std::getline(std::cin, input);
        }
        if (input == "End"){
            Finish();
        }
        else{
            LoadGame();
        }
    }
    else{
        std::cout << "\nYOU LOSE!\n";
        Finish();
    }
}
*/
/*
ResultOfRound Game::NewRound() {
    std::cout << "\nNew Round!\n";
    UserChoice choice;
    while(true){
        //CreateOpponent();
        while(game_status.alive_opponent_ships!=0 && game_status.alive_user_ships!=0){
            choice = UserTurn();
            if (choice == UserChoice::kSave){
                return ResultOfRound::kUserWantSave;
            }
            else if (choice == UserChoice::kLoad){
                return ResultOfRound::kUserWantLoad;
            }
            if (game_status.alive_opponent_ships !=0 ) OpponentTurn();
        }
        break;
    }
    if (game_status.alive_opponent_ships == 0){
        VictoryText();
        return ResultOfRound::kUserWin;
    }
    else return ResultOfRound::kUserLose;
}
*/
void Game::VictoryText(){
    std::cout <<"____    ____  ______    __    __     ____    __    ____  __  .__   __.    .______        ______    __    __  .__   __.  _______   __  \n"
                "\\   \\  /   / /  __  \\  |  |  |  |    \\   \\  /  \\  /   / |  | |  \\ |  |    |   _  \\      /  __  \\  |  |  |  | |  \\ |  | |       \\ |  | \n"
                " \\   \\/   / |  |  |  | |  |  |  |     \\   \\/    \\/   /  |  | |   \\|  |    |  |_)  |    |  |  |  | |  |  |  | |   \\|  | |  .--.  ||  | \n"
                "  \\_    _/  |  |  |  | |  |  |  |      \\            /   |  | |  . `  |    |      /     |  |  |  | |  |  |  | |  . `  | |  |  |  ||  | \n"
                "    |  |    |  `--'  | |  `--'  |       \\    /\\    /    |  | |  |\\   |    |  |\\  \\----.|  `--'  | |  `--'  | |  |\\   | |  '--'  ||__| \n"
                "    |__|     \\______/   \\______/         \\__/  \\__/     |__| |__| \\__|    | _| `._____| \\______/   \\______/  |__| \\__| |_______/ (__) \n";
}

void Game::GameOverText() {
    std::cout<< "  _______      ___      .___  ___.  _______      ______   ____    ____  _______ .______       __  \n"
                " /  _____|    /   \\     |   \\/   | |   ____|    /  __  \\  \\   \\  /   / |   ____||   _  \\     |  | \n"
                "|  |  __     /  ^  \\    |  \\  /  | |  |__      |  |  |  |  \\   \\/   /  |  |__   |  |_)  |    |  | \n"
                "|  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|     |  |  |  |   \\      /   |   __|  |      /     |  | \n"
                "|  |__| |  /  _____  \\  |  |  |  | |  |____    |  `--'  |    \\    /    |  |____ |  |\\  \\----.|__| \n"
                " \\______| /__/     \\__\\ |__|  |__| |_______|    \\______/      \\__/     |_______|| _| `._____|(__) \n";
}

void Game::StartNewGame() {
    CreateUser();
    CreateOpponent(AgeOpponent::kNewOpponent);
    //Rounds();
}

/*
void Game::Finish() {
    std::cout << "\nYou can End/Load/Restart game!\n";
    std::cout << "Just write command: \n";
    std::string input;
    std::getline(std::cin, input);
    while (input != "Load" &&  input != "End" && input != "Restart"){
        std::cout << "You entered an unknown command: ";
        std::cout << input  << "\n";
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, input);
    }
    if (input == "End"){
        GameOverText();
    }
    else if (input=="Load"){
        LoadGame();
    }
    else{
        std::cout << "\nRestarting...\n";
        game_status.Clear();
        StartNewGame();
    }
}
*/
void Game::SaveGame() {
    try{
        game_status.Save();
        std::cout << "Saving....\n";
    }
    catch(ProgramErrors& e){
        //std::cout << e.what();
        throw ProgramErrors(e.what());
    }
}

void Game::LoadGame() {
    std::cout << "\nLoading....\n";
    try{
        game_status.Clear();
        game_status.Load();
        //Rounds(TypeOfGame::kLoadGame);
    }
    catch(ProgramErrors& e){
        //std::cout << e.what();
        throw ProgramErrors(e.what());
    }
}

