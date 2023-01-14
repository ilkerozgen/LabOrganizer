//Ýlker ÖZGEN - 21902719

#include <string>
using namespace std;

class LabOrganizer
{
    public:
        LabOrganizer();
        ~LabOrganizer();

        void addCabinet(int id, int rows, int columns);
        void removeCabinet(int id);
        void listCabinets();
        void cabinetContents(int id);
        void placeChemical(int cabinetId, string location, string chemType, int chemID);
        void findChemical(int id);
        void removeChemical(int id);

        int cabinetsSize;
        int *cabinetIDs;
        int *cabinetRows;
        int *cabinetColumns;
        int *numberOfEmptySlots;
        string *rowLetters;
        int ***chemicals;
        string ***chemicalTypes;
};
