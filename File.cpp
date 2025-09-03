#include "File.h"
#include "GameStatus.h"

class GameStatus;
File::File(const std::string &file_name, std::ios::openmode mode) {
    file_stream.open(file_name, mode);
    if (!file_stream.is_open()){
        throw CannotOpenFileError("Something wrong this file!\n");
    }

}
File::~File() noexcept {
    file_stream.close();
}

File &File::operator<<(GameStatus &game_status) {
    file_stream << "not empty\n";
    WriteDlcData(game_status);
    size_t vertical_len = game_status.user_field->GetVerticalLen();
    size_t horizontal_len = game_status.user_field->GetHorizontalLen();
    file_stream << horizontal_len << "\n" << vertical_len << "\n";
    WriteField(game_status.user_field);
    WriteField(game_status.opponent_field);
    size_t nums_user_ships = game_status.user_manager->GetNumsOfShips();
    file_stream << nums_user_ships << "\n";
    WriteManager(game_status.user_manager);
    WriteManager(game_status.opponent_manager);
    WriteAbilities(game_status.user_abilities);
    return *this;
}

File &File::operator>>(GameStatus &game_status) {
    std::string read_file;
    std::getline(file_stream, read_file);
    if (read_file == "empty"){
        throw CannotOpenFileError("File is empty!\n");
    }
    ReadDlcData(game_status);
    size_t vertical_len, horizontal_len;
    horizontal_len = ReadNum();
    vertical_len = ReadNum();
    game_status.user_field = new GamingField(horizontal_len, vertical_len);
    game_status.opponent_field = new GamingField(horizontal_len, vertical_len, OwnerField::kOpponentsField);
    std::vector<std::vector<StatusCellOnField>> user_cells_for_change;
    user_cells_for_change = ReadField(OwnerField::kMyField, vertical_len);
    std::vector<std::vector<StatusCellOnField>> opponent_cells_for_change;
    opponent_cells_for_change = ReadField(OwnerField::kOpponentsField, vertical_len);
    ReadManagers(game_status);
    game_status.user_field->ChangeStatusCells(user_cells_for_change);
    game_status.opponent_field->ChangeStatusCells(opponent_cells_for_change);
    ReadAbilities(game_status);
    return *this;
}
void File::WriteAbilities(AbilitiesManager *abilities_manager) {
    std::vector<TypesAbility> abilities_to_write = abilities_manager->GetAbilities();
    for (auto i : abilities_to_write){
        file_stream << static_cast<size_t>(i);
    }
    if (abilities_to_write.empty()){
        file_stream << static_cast<size_t>(TypesAbility::kNothing);
    }
    file_stream << "\n";
}
void File::WriteDlcData(GameStatus &game_status) {
    file_stream << game_status.alive_user_ships << "\n";
    file_stream << game_status.alive_opponent_ships << "\n";
    WriteCoordinates(game_status.user_ships_coords);
    WriteCoordinates(game_status.opponent_ships_coords);
    WriteCoordinates(game_status.user_cells_for_attack);
}

void File::WriteField(GamingField *someone_field) {
    for (size_t i = 0; i<someone_field->GetVerticalLen(); ++i){
        for (size_t j=0; j<someone_field->GetHorizontalLen(); ++j){
            file_stream << static_cast<char>(someone_field->GetCells()[i][j].status);
        }
        file_stream << "\n";
    }
}

void File::WriteManager(Manager *someone_manager) {
    for (size_t i=0; i<someone_manager->GetNumsOfShips(); ++i){
        Ship& user_boat = someone_manager->GetShip(i);
        file_stream << user_boat.Len() << "\n";
        file_stream << static_cast<char>(user_boat.GetOrientation()) << "\n";
        for (size_t j=0; j<user_boat.Len(); ++j){
            file_stream << static_cast<size_t>(user_boat.GetStatus(j));
        }
        file_stream << "\n";
    }
}
void File::WriteCoordinates(std::vector<Coordinates> &data) {
    file_stream << data.size() << "\n";
    for (auto& i : data){
        file_stream << i.x << " " << i.y << "\n";
    }
}
size_t File::ReadNum() {
    std::string read_file;
    std::getline(file_stream, read_file);
    return static_cast<size_t>(std::stoi(read_file));
}

void File::ReadCoordinates(std::vector<Coordinates> &coords) {
    coords.clear();
    std::string read_file;
    Coordinates coord_for_add{};
    size_t data_size = ReadNum();
    for (size_t i=0; i<data_size; ++i){
        std::getline(file_stream, read_file);
        size_t pos = read_file.find(' ');
        coord_for_add.x = static_cast<size_t>(std::stoi(read_file.substr(0, pos)));
        coord_for_add.y = static_cast<size_t>(std::stoi(read_file.substr(pos+1)));
        coords.push_back(coord_for_add);
    }
}

void File::ReadDlcData(GameStatus &game_status) {
    game_status.alive_user_ships = ReadNum();
    game_status.alive_opponent_ships = ReadNum();
    ReadCoordinates(game_status.user_ships_coords);
    ReadCoordinates(game_status.opponent_ships_coords);
    ReadCoordinates(game_status.user_cells_for_attack);
}

void File::ReadAbilities(GameStatus &game_status) {
    std::string file_read;
    std::getline(file_stream, file_read);
    std::vector<TypesAbility> abilities_for_load;
    for (char i : file_read){
        abilities_for_load.push_back(static_cast<TypesAbility>(i - '0'));
    }
    game_status.user_abilities = new AbilitiesManager(abilities_for_load, game_status.opponent_field, game_status.opponent_manager);
}

void File::ReadManagers(GameStatus &game_status) {
    std::vector<std::vector<SegmentStatus>> user_ship_segments;
    std::vector<std::vector<SegmentStatus>> opponent_ship_segments;
    std::string read_file;
    std::vector<SegmentStatus> segments;
    size_t nums_of_ship;
    std::vector<size_t> lens;
    std::vector<OrientationType> user_orientations;
    std::vector<OrientationType> opponent_orientations;
    nums_of_ship = ReadNum();
    size_t boat_len;
    OrientationType orientation;
    for (size_t i=0; i<nums_of_ship; ++i){
        segments.clear();
        boat_len = ReadNum();
        lens.push_back(boat_len);
        char sym;
        std::getline(file_stream, read_file);
        sym = read_file[0];

        orientation = static_cast<OrientationType>(sym);
        user_orientations.push_back(orientation);
        std::getline(file_stream, read_file);
        for (char j : read_file){
            segments.push_back(static_cast<SegmentStatus>(j-'0'));
        }
        user_ship_segments.push_back(segments);
    }
    game_status.user_manager = new Manager(nums_of_ship, lens);
    for (size_t i=0; i<nums_of_ship; ++i){
        game_status.user_field->AddShip(game_status.user_manager->GetShip(i), game_status.user_ships_coords[i],user_orientations[i]);
    }
    lens.clear();
    for (size_t i=0; i<nums_of_ship; ++i){
        boat_len = ReadNum();
        lens.push_back(boat_len);
        char sym;
        std::getline(file_stream, read_file);
        sym = read_file[0];
        //std::cout << sym << "\n";
        orientation = static_cast<OrientationType>(sym);
        opponent_orientations.push_back(orientation);
        std::getline(file_stream, read_file);
        segments.clear();
        for (char j : read_file){
            segments.push_back(static_cast<SegmentStatus>(j-'0'));
        }
        opponent_ship_segments.push_back(segments);
    }

    game_status.opponent_manager = new Manager(nums_of_ship, lens);
    for (size_t i=0; i<nums_of_ship; ++i){
        game_status.opponent_field->AddShip(game_status.opponent_manager->GetShip(i), game_status.opponent_ships_coords[i],opponent_orientations[i]);
    }
    game_status.user_manager->SetSegments(user_ship_segments);
    game_status.opponent_manager->SetSegments(opponent_ship_segments);
}

std::vector<std::vector<StatusCellOnField>> File::ReadField(OwnerField owner, size_t vertical_len) {
    std::vector<std::vector<StatusCellOnField>> cells;
    std::vector<StatusCellOnField> horizontal;
    std::string str_for_field;
    for (size_t i=0; i<vertical_len; ++i){
        std::getline(file_stream, str_for_field);
        for (char sym : str_for_field){
            horizontal.push_back(static_cast<StatusCellOnField>(sym));
        }
        cells.push_back(horizontal);
        horizontal.clear();
    }
    return cells;
}

/*
void File::Clear(GameStatus& game_status) {
    file_stream.close();
    // Открываем файл в режиме записи с обрезкой
    file_stream.open(game_status.file_name,  std::ios::trunc);
    if (!file_stream.is_open()) {
        throw CannotOpenFileError("Failed to clear the file!\n");
    }
}
 */