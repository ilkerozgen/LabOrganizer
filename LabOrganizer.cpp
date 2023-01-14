//Ýlker ÖZGEN - 21902719
/*
    When the tester file is run, it does not execute a particular part of the code.
    Then the program stops and it does not execute th rest of the code.
    I detected the problematic lines by commenting them out. These lines are 161 and 162.
    If they are commented out, the program runs properly but it loses its functionality of course.
    Thus, I left them uncommented, so my output is not proper.
    I tried to find the reason why this happens but I could not.
    Since there is no error given, I could not understand why the problem occurs.
    Since the problem is in addCabinet function and it is not possible to use other functions without adding a cabinet,
    I could not test the other functions. However, I believe they should work properly.
*/

#include <iostream>
#include "LabOrganizer.h"
#include <sstream>
using namespace std;

LabOrganizer::LabOrganizer()
{
    cabinetsSize = 0;
    rowLetters = new string[9];

    rowLetters[0] = "A";
    rowLetters[1] = "B";
    rowLetters[2] = "C";
    rowLetters[3] = "D";
    rowLetters[4] = "E";
    rowLetters[5] = "F";
    rowLetters[6] = "G";
    rowLetters[7] = "H";
    rowLetters[8] = "I";
}

LabOrganizer::~LabOrganizer()
{
    for (int i = 0; i < cabinetsSize; i++)
    {
        for (int j = 0; j < cabinetRows[i]; j++)
        {
            delete[] chemicals[i][j];
            delete[] chemicalTypes[i][j];
        }

        delete[] chemicals[i];
        delete[] chemicalTypes[i];
    }

    delete[] chemicals;
    delete[] chemicalTypes;

    delete [] cabinetIDs;
    delete [] cabinetRows;
    delete [] cabinetColumns;
    delete [] numberOfEmptySlots;
    delete [] rowLetters;
}

void LabOrganizer::addCabinet(int id, int rows, int columns)
{
    bool isUnique;

    isUnique = true;

    // Check the collection of existing cabinets to make sure that the entered ID for the new cabinet is unique.
    for(int i = 0; i < cabinetsSize; i++)
    {
        if(cabinetIDs[i] == id)
        {
            isUnique = false;
            break;
        }
        else
        {
            isUnique = true;
        }
    }

    // If the ID is not unique display a warning message and don't allow to proceed.
    if(!isUnique)
    {
       cout << "Warning: The specified ID already exists." << endl;
    }
    else
    {
        // Check that the height and the width of the cabinet are not longer than 9.
        if(rows > 9 || columns > 9)
        {
            // Display a warning message if the dimensions are not suitable and don't allow to proceed.
            cout << "Warning: Rows and columns cannot be more than 9." << endl;
        }
        else
        {
            // If the inputs are suitable, add the cabinet.
            if(cabinetsSize == 0)
            {
                cabinetIDs = new int[1];
                cabinetRows = new int[1];
                cabinetColumns = new int[1];
                numberOfEmptySlots = new int[1];

                chemicals = new int** [1];
                chemicalTypes = new string** [1];

                chemicals[0] = new int* [rows];
                chemicalTypes[0] = new string* [rows];

                for(int i = 0; i < rows; i++)
                {
                    chemicals[0][i] = new int[columns];
                    chemicalTypes[0][i] = new string[columns];
                }

                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < columns; j++)
                    {
                        chemicalTypes[0][i][j] = "+"; // Assign all the chemical types to empty at the beginning.
                    }
                }

                cabinetIDs[0] = id;
                cabinetRows[0] = rows;
                cabinetColumns[0] = columns;
                numberOfEmptySlots[0] = rows * columns;

                cabinetsSize++;
            }
            else
            {
                int *tempIDs = new int[cabinetsSize + 1];
                int *tempRows = new int[cabinetsSize + 1];
                int *tempColumns = new int[cabinetsSize + 1];
                int *tempEmptySlots = new int[cabinetsSize + 1];
                int ***tempChemicals = new int** [cabinetsSize + 1];
                string ***tempChemicalTypes = new string** [cabinetsSize + 1];

                for(int i = 0; i < cabinetsSize + 1; i++)
                {
                    tempChemicals[i] = new int* [rows];
                    tempChemicalTypes[i] = new string* [rows];

                    for(int j = 0; j < rows; j++)
                    {
                        tempChemicals[i][j] = new int[columns];
                        tempChemicalTypes[i][j] = new string[columns];
                    }
                }

                for(int i = 0; i < cabinetsSize; i++)
                {
                    tempIDs[i] = cabinetIDs[i];
                    tempRows[i] = cabinetRows[i];
                    tempColumns[i] = cabinetColumns[i];
                    tempEmptySlots[i] = numberOfEmptySlots[i];

                    for(int j = 0; j < cabinetRows[i]; j++)
                    {
                        for(int k = 0; k < cabinetColumns[i]; k++)
                        {
                            tempChemicals[i][j][k] = chemicals[i][j][k]; // Problematic line
                            tempChemicalTypes[i][j][k] = chemicalTypes[i][j][k]; // Problematic line
                        }
                    }
                }

                tempIDs[cabinetsSize] = id;
                tempRows[cabinetsSize] = rows;
                tempColumns[cabinetsSize] = columns;
                tempEmptySlots[cabinetsSize] = rows * columns;

                tempChemicals[cabinetsSize] = new int* [rows];
                tempChemicalTypes[cabinetsSize] = new string* [rows];

                for(int i = 0; i < rows; i++)
                {
                    tempChemicals[cabinetsSize][i] = new int[columns];
                    tempChemicalTypes[cabinetsSize][i] = new string[columns];
                }

                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < columns; j++)
                    {
                        tempChemicalTypes[cabinetsSize][i][j] = "+"; // Assign all the chemical types to empty at the beginning.
                    }
                }

                cabinetsSize++;

                cabinetIDs = tempIDs;
                cabinetRows = tempRows;
                cabinetColumns = tempColumns;
                numberOfEmptySlots = tempEmptySlots;
                chemicals = tempChemicals;
                chemicalTypes = tempChemicalTypes;

                for (int i = 0; i < cabinetsSize - 1; i++)
                {
                    for (int j = 0; j < tempRows[i]; j++)
                    {
                        delete[] tempChemicals[i][j];
                        delete[] tempChemicalTypes[i][j];
                    }

                    delete[] tempChemicals[i];
                    delete[] tempChemicalTypes[i];
                }

                delete[] tempChemicals;
                delete[] tempChemicalTypes;

                delete[] tempIDs;
                delete[] tempRows;
                delete[] tempColumns;
                delete[] tempEmptySlots;
            }

            cout << "Cabinet is successfully added." << endl;
        }
    }
}

void LabOrganizer::removeCabinet(int id)
{
    bool doesExist;
    int index;

    doesExist = false;

    // Check if the specified ID exists.
    for(int i = 0; i < cabinetsSize; i++)
    {
        if(cabinetIDs[i] == id)
        {
            doesExist = true;
            index = i;
            break;
        }
        else
        {
            doesExist = false;
        }
    }

    if(!doesExist)
    {
        // If the ID does not exist, display a waring message.
        cout << "Warning: The specified ID does not exist." << endl;
    }
    else
    {
        // List the names of chemicals that were disposed of in the process.
        cout << "The chemicals that were disposed of: " << endl;

        for(int i = 0; i < cabinetRows[index]; i++)
        {
            for(int j = 0; j < cabinetColumns[index]; j++)
            {
                if(chemicalTypes[index][i][j] != "+")
                {
                    cout << "--------------------------" << endl;
                    cout << "Chemical ID: " << chemicals[index][i][j] << endl;
                    cout << "Chemical Type: " << chemicalTypes[index][i][j] << endl;
                }
            }
        }

        // Remove the cabinet.
        cabinetsSize--;

        for(int i = index; i < cabinetsSize; i++)
        {
            cabinetIDs[i] = cabinetIDs[i + 1];
            cabinetRows[i] = cabinetRows[i + 1];
            cabinetColumns[i] = cabinetColumns[i + 1];
            numberOfEmptySlots[i] = numberOfEmptySlots[i + 1];
            chemicals[i] = chemicals[i + 1];
            chemicalTypes[i] = chemicalTypes[i + 1];
        }

        // Display a message indicating that the cabinet has been removed.
        cout << "Cabinet is successfully removed." << endl;
    }
}

void LabOrganizer::listCabinets()
{
    // For each cabinet, display the ID, dimensions, and the number of empty slots in the cabinet.
    if(cabinetsSize == 0)
    {
        cout << "No Cabinets Found." << endl;
    }
    else
    {
        for(int i = 0; i < cabinetsSize; i++)
        {
            cout << "********************" << endl;
            cout << "Cabinet " << i + 1 << endl;
            cout << "ID: " << cabinetIDs[i] << endl;
            cout << "Rows: " << cabinetRows[i] << endl;
            cout << "Columns: " << cabinetColumns[i] << endl;
            cout << "Number of Empty Slots: " << numberOfEmptySlots[i] << endl;
        }
    }
}

void LabOrganizer::cabinetContents(int id)
{
    bool doesExist;
    int index;

    doesExist = false;

    // Check if the specified ID exists.
    for(int i = 0; i < cabinetsSize; i++)
    {
        if(cabinetIDs[i] == id)
        {
            doesExist = true;
            index = i;
            break;
        }
        else
        {
            doesExist = false;
        }
    }

    if(!doesExist)
    {
        // If the ID does not exist, display a waring message.
        cout << "Warning: The specified ID does not exist." << endl;
    }
    else
    {
        // Display the ID, dimensions, the number of empty slots, and the list of chemicals in the cabinet.
        cout << "Cabinet ID: " << cabinetIDs[index] << endl;
        cout << "Rows: " << cabinetRows[index] << endl;
        cout << "Columns: " << cabinetColumns[index] << endl;
        cout << "Number of Empty Slots: " << numberOfEmptySlots[index] << endl;
        cout << "The Chemicals in the Cabinet: " << endl;

        cout << "  ";

        for(int i = 0; i < cabinetColumns[index]; i++)
        {
            cout << i + 1 << " ";
        }

        cout << endl;

        for(int i = 0; i < cabinetRows[index]; i++)
        {
            cout << rowLetters[i] << " ";

            for(int j = 0; j < cabinetColumns[index]; j++)
            {
                cout << chemicalTypes[i][j] << " ";
            }

            cout << endl;
        }
    }
}

void LabOrganizer::placeChemical(int cabinetId, string location, string chemType, int chemID)
{
    bool doesExist;
    bool canBePlaced;
    bool isUnique;
    int cabinetIndex;
    int rowIndex;
    int columnIndex;

    doesExist = false;
    isUnique = true;
    canBePlaced = true;

    // Check if the corresponding cabinet ID exists in the system.
    for(int i = 0; i < cabinetsSize; i++)
    {
        if(cabinetIDs[i] == cabinetId)
        {
            doesExist = true;
            cabinetIndex = i;
            break;
        }
        else
        {
            doesExist = false;
        }
    }

    if(!doesExist)
    {
        // If the ID does not exist, display a waring message.
        cout << "Warning: The specified ID does not exist." << endl;
    }
    else
    {
        // Check if the corresponding space in the cabinet is empty.
        for(int i = 0; i < 9; i++)
        {
            if(rowLetters[i] == string(1, location[0]))
            {
                rowIndex = i;
                break;
            }
        }

        stringstream intValue(string(1, location[1]));
        intValue >> columnIndex;

        if(chemicalTypes[cabinetIndex][rowIndex][columnIndex] != "+")
        {
            // If not, display a warning message.
            cout << "Warning: The corresponding space in the cabinet is not empty." << endl;
        }
        else
        {
            // Check if that type of chemical can be placed at that location.
            if(chemType[0] == 'r' || chemType[0] == 'R')
            {
                canBePlaced = true;
            }
            else
            {
                // Check all the spots that is close to the location.
                if(columnIndex != 0 && chemicalTypes[cabinetIndex][rowIndex][columnIndex - 1] == "c")
                {
                    canBePlaced = false;
                }
                else if(chemicalTypes[cabinetIndex][rowIndex][columnIndex + 1] == "c")
                {
                    canBePlaced = false;
                }
                else if(rowIndex != 0 && columnIndex != 0 && chemicalTypes[cabinetIndex][rowIndex - 1][columnIndex - 1] == "c")
                {
                    canBePlaced = false;
                }
                else if(rowIndex != 0 && chemicalTypes[cabinetIndex][rowIndex - 1][columnIndex] == "c")
                {
                    canBePlaced = false;
                }
                else if(rowIndex != 0 && chemicalTypes[cabinetIndex][rowIndex - 1][columnIndex + 1] == "c")
                {
                    canBePlaced = false;
                }
                else if(columnIndex != 0 && chemicalTypes[cabinetIndex][rowIndex + 1][columnIndex - 1] == "c")
                {
                    canBePlaced = false;
                }
                else if(chemicalTypes[cabinetIndex][rowIndex + 1][columnIndex] == "c")
                {
                    canBePlaced = false;
                }
                else if(chemicalTypes[cabinetIndex][rowIndex + 1][columnIndex + 1] == "c")
                {
                    canBePlaced = false;
                }
                else
                {
                    canBePlaced = true;
                }
            }

            if(!canBePlaced)
            {
                // If not, display a warning message.
                cout << "Warning: The specified chemical cannot be placed at that location." << endl;

                // TO DO - Provide the names of closest suitable locations.
            }
            else
            {
                // Check if the chemical ID is unique.
                for(int i = 0; i < cabinetsSize; i++)
                {
                    for(int j = 0; j < cabinetRows[i]; j++)
                    {
                        for(int k = 0; k < cabinetColumns[i]; k++)
                        {
                            if(chemicals[i][j][k] == chemID)
                            {
                                isUnique = false;
                                break;
                            }
                            else
                            {
                                isUnique = true;
                            }
                        }
                    }
                }

                if(!isUnique)
                {
                    // If not, display a warning message.
                    cout << "Warning: The chemical ID is not unique." << endl;
                }
                else
                {
                    // Place the chemical if all conditions are satisfied.
                    chemicals[cabinetIndex][rowIndex][columnIndex] = chemID;
                    chemicalTypes[cabinetIndex][rowIndex][columnIndex] = chemType[0];
                    numberOfEmptySlots[cabinetIndex] = numberOfEmptySlots[cabinetIndex] - 1;
                }
            }
        }
    }
}

void LabOrganizer::findChemical(int id)
{
    bool doesExist;
    int cabinetIndex;
    int rowIndex;
    int columnIndex;

    doesExist = false;

    // Search for the specified ID.
    for(int i = 0; i < cabinetsSize; i++)
    {
        for(int j = 0; j < cabinetRows[i]; j++)
        {
            for(int k = 0; k < cabinetColumns[i]; k++)
            {
                if(chemicals[i][j][k] == id)
                {
                    doesExist = true;

                    cabinetIndex = i;
                    rowIndex = j;
                    columnIndex = k;

                    break;
                }
                else
                {
                    doesExist = false;
                }
            }
        }
    }

    if(!doesExist)
    {
        // If the ID does not exist display a warning message.
        cout << "Warning: The specified ID does not exist." << endl;
    }
    else
    {
        // If the chemical is found, display the cabinet ID and the location of the chemical.
        cout << "Chemical is found!" << endl;
        cout << "Cabinet ID: " << chemicals[cabinetIndex][rowIndex][columnIndex] << endl;
        cout << "The chemical is in the cabinet with ID: " << cabinetIDs[cabinetIndex] << endl;
        cout << "Location: " << rowLetters[rowIndex] << columnIndex + 1 << endl;
    }
}

void LabOrganizer::removeChemical(int id)
{
    bool doesExist;
    int cabinetIndex;
    int rowIndex;
    int columnIndex;

    doesExist = false;

    // Check if the corresponding ID exists in the system.

    for(int i = 0; i < cabinetsSize; i++)
    {
        for(int j = 0; j < cabinetRows[i]; j++)
        {
            for(int k = 0; k < cabinetColumns[i]; k++)
            {
                if(chemicals[i][j][k] == id)
                {
                    doesExist = true;

                    cabinetIndex = i;
                    rowIndex = j;
                    columnIndex = k;

                    break;
                }
                else
                {
                    doesExist = true;
                }
            }
        }
    }

    if(!doesExist)
    {
        // If not, display a warning message.
        cout << "Warning: The specified ID does not exist." << endl;
    }
    else
    {
        // If it exists, remove the chemical.
        chemicals[cabinetIndex][rowIndex][columnIndex] = 0;
        chemicalTypes[cabinetIndex][rowIndex][columnIndex] = "+";
        numberOfEmptySlots[cabinetIndex] = numberOfEmptySlots[cabinetIndex] + 1;
    }
}
