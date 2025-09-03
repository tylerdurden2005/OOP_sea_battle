#ifndef OOPLABEL1_FILE_H
#define OOPLABEL1_FILE_H
#include <fstream>
#include "GameStatus.h"
class GameStatus;
class File {
    std::fstream file_stream;
public:
    explicit File(const std::string& file_name, std::ios::openmode mode);
    ~File() noexcept;
    void WriteManager(Manager* someone_manager);
    void WriteField(GamingField* someone_field);
    void WriteAbilities(AbilitiesManager* abilities_manager);
    void WriteCoordinates(std::vector<Coordinates>& data);
    void WriteDlcData(GameStatus& game_status);
    std::vector<std::vector<StatusCellOnField>> ReadField(OwnerField owner, size_t vertical_len);
    size_t ReadNum();
    void ReadCoordinates(std::vector<Coordinates>& coords);
    void Clear(GameStatus& game_status);
    void ReadManagers(GameStatus& game_status);
    void ReadDlcData(GameStatus& game_status);
    void ReadAbilities(GameStatus& game_status);
    File& operator >> (GameStatus& game_status);
    File& operator << (GameStatus& game_status);
};
#endif //OOPLABEL1_FILE_H
