#include <table_utils.h>

void Utils::Gui::display_table(const char *title, bool *p_open, const std::vector<std::vector<float>> &data, const std::vector<std::string> &header, ImGuiWindowFlags flags)
{
    ImGui::Begin(title, p_open, flags);
    // Get the number of rows and columns in the data
    int numRows = data.size();
    int numCols = numRows > 0 ? data[0].size() : 0;

    // Create a table with the appropriate number of rows and columns
    ImGui::BeginTable("MyTable", numCols);

    // Add a header row with the column names
    for (std::string column_name : header)
    {
        ImGui::TableSetupColumn(column_name.c_str());
    }
    ImGui::TableHeadersRow();

    // Loop through the data and add each row to the table
    for (int i = 0; i < numRows - 1; i++)
    {
        ImGui::TableNextRow();
        for (int j = 0; j < numCols - 1; j++)
        {
            ImGui::TableSetColumnIndex(j);
            ImGui::Text("%f", data[i][j]);
        }
    }
    ImGui::EndTable();
    ImGui::End();
}
