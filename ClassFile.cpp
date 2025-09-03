/*#include "Manager.h"
#include "GamingField.h"
#include "AbilitiesManager.h"
#include <fstream>
class File {
    std::fstream file_stream;
public:
    explicit File(const std::string& file_name, std::ios::openmode mode){
        file_stream.open(file_name, mode);
        if (!file_stream.is_open()){
            throw CannotOpenFileError("");
        }
    }
    ~File() noexcept {
        file_stream.close();
    }
    void WriteManager(Manager* someone_manager){
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
    void WriteField(GamingField* someone_field){
        for (size_t i = 0; i<someone_field->GetVerticalLen(); ++i){
            for (size_t j=0; j<someone_field->GetHorizontalLen(); ++j){
                file_stream << static_cast<char>(someone_field->GetCells()[i][j].status);
            }
            file_stream << "\n";
        }
        file_stream << "\n";
    }
    void WriteAbilities(AbilitiesManager* abilities_manager){
        std::vector<TypesAbility> abilities_to_write = abilities_manager->GetAbilities();
        for (auto i : abilities_to_write){
            file_stream << static_cast<size_t>(i);
        }
        if (abilities_to_write.empty()){
            file_stream << static_cast<size_t>(TypesAbility::kNothing);
        }
        file_stream << "\n";
    };
    void WriteCoordinates(std::vector<Coordinates>& data){
        file_stream << data.size() << "\n";
        for (auto& i : data){
            file_stream << i.x << " " << i.y << "\n";
        }
    }
    void WriteDlcData(GameStatus& game_status){
        file_stream << game_status.alive_user_ships << "\n";
        file_stream << game_status.alive_opponent_ships << "\n";
        WriteCoordinates(game_status.user_ships_coords);
        WriteCoordinates(game_status.opponent_ships_coords);
        WriteCoordinates(game_status.user_cells_for_attack);
    }
    std::vector<std::vector<StatusCellOnField>> ReadField(OwnerField owner, size_t vertical_len){
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
    size_t ReadNum(){
        std::string read_file;
        std::getline(file_stream, read_file);
        return static_cast<size_t>(std::stoi(read_file));
    }
    void ReadCoordinates(std::vector<Coordinates>& coords){
        coords.clear();
        std::string read_file;
        Coordinates coord_for_add{};
        size_t data_size = ReadNum();
        for (size_t i=0; i<data_size; ++i){
            file_stream >> coord_for_add.x >> coord_for_add.y;
            coords.push_back(coord_for_add);
        }
    }

    void ReadManagers(GameStatus& game_status){
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
            char sym = (char)ReadNum();
            orientation = static_cast<OrientationType>(sym);
            user_orientations.push_back(orientation);
            std::getline(file_stream, read_file);
            for (char j : read_file){
                segments.push_back(static_cast<SegmentStatus>(j));
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
            char sym = (char)ReadNum();
            orientation = static_cast<OrientationType>(sym);
            opponent_orientations.push_back(orientation);
            std::getline(file_stream, read_file);
            segments.clear();
            for (char j : read_file){
                segments.push_back(static_cast<SegmentStatus>(j));
            }
            opponent_ship_segments.push_back(segments);
        }

        game_status.opponent_manager = new Manager(nums_of_ship, lens);

        for (size_t i=0; i<nums_of_ship; ++i){
            game_status.opponent_field->AddShip(game_status.opponent_manager->GetShip(i), game_status.opponent_ships_coords[i],user_orientations[i]);
        }
        game_status.user_manager->SetSegments(user_ship_segments);
        game_status.opponent_manager->SetSegments(opponent_ship_segments);
    }
    void ReadDlcData(GameStatus& game_status){
        game_status.alive_user_ships = ReadNum();
        game_status.alive_opponent_ships = ReadNum();
        ReadCoordinates(game_status.user_ships_coords);
        ReadCoordinates(game_status.opponent_ships_coords);
        ReadCoordinates(game_status.user_cells_for_attack);
    }
    void ReadAbilities(GameStatus& game_status){
        std::string file_read;
        std::getline(file_stream, file_read);
        std::vector<TypesAbility> abilities_for_load;
        for (char i : file_read){
            abilities_for_load.push_back(static_cast<TypesAbility>(i));
        }
        game_status.user_abilities = new AbilitiesManager(abilities_for_load, game_status.opponent_field, game_status.opponent_manager);
    }
    File& operator >> (GameStatus& game_status){
        ReadDlcData(game_status);
        std::string read_file;
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
    File& operator << (GameStatus& game_status){
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
};
*/