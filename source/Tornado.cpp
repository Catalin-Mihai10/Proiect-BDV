#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "../headers/headers.hpp"

Tornado *parseData(std::fstream &inputFile)
{
    Tornado *temp = (Tornado *)malloc(DATASET_SIZE * (sizeof *temp));

    if (temp == NULL)
    {
        printf("Error allocating dataset buffer!\n");
        exit(1);
    }

    std::string lineBuffer;
    u32 delimiterIndex,
        datasetIndex = 0;
    bool firstLine = true;
    while (std::getline(inputFile, lineBuffer, '\n'))
    {
        if (!firstLine)
        {
            temp[datasetIndex].year = std::stoi(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].month = std::stoi(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].day = std::stoi(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            strcpy(temp[datasetIndex].date, lineBuffer.substr(0, lineBuffer.find_first_of(',')).c_str());
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            strcpy(temp[datasetIndex].state, lineBuffer.substr(0, lineBuffer.find_first_of(',')).c_str());
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].magnitude = std::stoi(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].injuries = std::stoi(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].fatalities = std::stoi(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].beginningLatitude = std::stod(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].beginningLongitude = std::stod(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].endLatitude = std::stod(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].endLongitude = std::stod(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].tornadoLength = std::stod(lineBuffer.substr(0, lineBuffer.find_first_of(',')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            temp[datasetIndex].tornadoWidth = std::stoi(lineBuffer.substr(0, lineBuffer.find_first_of('\n')));
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            strcpy(temp[datasetIndex].lengthCat, lineBuffer.substr(0, lineBuffer.find_first_of(',')).c_str());
            delimiterIndex = lineBuffer.find_first_of(',') + 1;
            lineBuffer.erase(0, delimiterIndex);

            strcpy(temp[datasetIndex].widthCat, lineBuffer.substr(0, lineBuffer.find_first_of(',')).c_str());

            lineBuffer.clear();
            ++datasetIndex;
        }
        firstLine = false;
    }

    return temp;
}
#define MAX_LINE_LENGTH 1000
void converterCsvToGml()
{
    char csvFileName[] = "E:\\Master\\Anul 1\\BDV\\ProiectBDV\\dataset\\Length_Width_Magnitude.csv";
    char gmlFileName[] = "E:\\Master\\Anul 1\\BDV\\ProiectBDV\\dataset\\Length_Width_Magnitude_generated.gml";

    FILE *csvFile = fopen(csvFileName, "r");
    FILE *gmlFile = fopen(gmlFileName, "w");

    if (csvFile == NULL || gmlFile == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    fprintf(gmlFile, "graph [\n");

    char line[MAX_LINE_LENGTH];

    fgets(line, MAX_LINE_LENGTH, csvFile);
    int flag = -1;

    while (fgets(line, MAX_LINE_LENGTH, csvFile) != NULL)
    {
        char *token = strtok(line, ",");
        char t1[MAX_LINE_LENGTH];
        strcpy(t1, token);

        token = strtok(NULL, ",");
        char t1_month[MAX_LINE_LENGTH];
        strcpy(t1_month, token);

        token = strtok(NULL, ",");
        float t1_mag = atof(token);

        token = strtok(NULL, ",");
        char t1_state[MAX_LINE_LENGTH];
        strcpy(t1_state, token);

        token = strtok(NULL, ",");
        char t2[MAX_LINE_LENGTH];
        strcpy(t2, token);

        token = strtok(NULL, ",");
        int edge = atoi(token);

        if (flag != atoi(t1))
        {
            fprintf(gmlFile, "\tnode [\n");
            fprintf(gmlFile, "\t\tid \"%s\"\n", t1);
            fprintf(gmlFile, "\t\tlabel \"%s\"\n", t1);
            fprintf(gmlFile, "\t\tt1_month \"%s\"\n", t1_month);
            fprintf(gmlFile, "\t\tt1_mag %.2f\n", t1_mag);
            fprintf(gmlFile, "\t\tt1_state \"%s\"\n", t1_state);
            fprintf(gmlFile, "\t]\n");
            flag = atoi(t1);
        }
    }

    // lazy solution instead of moving cursor to begining
    fclose(csvFile);
    csvFile = fopen(csvFileName, "r");

    while (fgets(line, MAX_LINE_LENGTH, csvFile) != NULL)
    {
        char *token = strtok(line, ",");
        char t1[MAX_LINE_LENGTH];
        strcpy(t1, token);

        token = strtok(NULL, ",");
        char t1_month[MAX_LINE_LENGTH];
        strcpy(t1_month, token);

        token = strtok(NULL, ",");
        float t1_mag = atof(token);

        token = strtok(NULL, ",");
        char t1_state[MAX_LINE_LENGTH];
        strcpy(t1_state, token);

        token = strtok(NULL, ",");
        char t2[MAX_LINE_LENGTH];
        strcpy(t2, token);

        token = strtok(NULL, ",");
        int edge = atoi(token);

        fprintf(gmlFile, "\tedge [\n");
        fprintf(gmlFile, "\t\tsource \"%s\"\n", t1);
        fprintf(gmlFile, "\t\ttarget \"%s\"\n", t2);
        fprintf(gmlFile, "\t\tedge %d\n", edge);
        fprintf(gmlFile, "\t]\n");
    }

    fprintf(gmlFile, "]\n");

    fclose(csvFile);
    fclose(gmlFile);

    printf("Conversion completed successfully.\n");
}

int main()
{
    Tornado *tornados;

    std::fstream inputFile,
        outputFile,
        violentOutputFile;

    inputFile.open("E:\\Master\\Anul 1\\BDV\\ProiectBDV\\dataset\\Full_Dataset.csv", std::fstream::in | std::ifstream::binary);
    outputFile.open("E:\\Master\\Anul 1\\BDV\\ProiectBDV\\dataset\\Length_Width_Magnitude.csv", std::fstream::out | std::ifstream::binary);
    // violentOutputFile.open("D:\\ProiectBDV\\dataset\\mostViolentTornados.csv", std::fstream::out | std::ifstream::binary);

    if (!inputFile.is_open() && !outputFile.is_open())
    {
        std::cout << "Error while opening dataset!" << std::endl;
        exit(1);
    }

    tornados = parseData(inputFile);
    inputFile.close();

    // tornadoMG *magnitudeGraph = (tornadoMG *)malloc((sizeof *magnitudeGraph));

    // u32 counter = 0;
    //      totalCounter = 0,
    //      violentCounter = 0;

    Tornado *temp = (Tornado *)malloc(DATASET_SIZE * (sizeof *temp));
    memcpy(temp, tornados, DATASET_SIZE * (sizeof *temp));

    //*mostViolentTornados = (Tornado *)malloc(DATASET_SIZE * (sizeof *mostViolentTornados));
    char csvLineBuffer[MAX_LINE_SIZE];
    char columns[] = "t1,month,magnitude,t2,edge\n";
    outputFile.write(columns, strlen(columns));
    for (u32 index = 0; index < DATASET_SIZE - 1; ++index)
    {
        char widthOuter[7];
        for (u32 inner_index = index + 1; inner_index < DATASET_SIZE; ++inner_index)
        {
            u8 edgeWeight = 0;
            char widthInner[7];
            strcpy(widthInner, temp[inner_index].widthCat);
            strcpy(widthOuter, tornados[index].widthCat);

            if ((strcmp(tornados[index].lengthCat, "long") == 0) && (strcmp(tornados[inner_index].lengthCat, "long") == 0))
            {
                edgeWeight += 2;
            }
            if ((strcmp(widthOuter, "long") == 0) && (strcmp(widthInner, "long") == 0))
            {
                edgeWeight += 1;
            }
            if ((strcmp(tornados[index].state, "TX") == 0) && (strcmp(tornados[inner_index].state, "TX") == 0))
            {
                edgeWeight += 1;
            }
            if (tornados[index].month == tornados[inner_index].month)
            {
                edgeWeight += 1;
            }

            if (edgeWeight > 4)
            {
                // printf("Gasit caz index: %d\n", index);
                u32 snprintfValue = snprintf(csvLineBuffer, MAX_LINE_SIZE, "%d,%d,%d,%s,%d,%d\n",
                                             index,
                                             tornados[index].month,
                                             tornados[index].magnitude,
                                             tornados[index].state,
                                             inner_index,
                                             edgeWeight);

                if (snprintfValue < 0)
                {
                    perror("An Error has ocurred while writing to the output file!\n");
                    exit(1);
                }
                outputFile.write(csvLineBuffer, snprintfValue);

                if (outputFile.bad())
                {
                    perror("An Error has ocurred while writing to the output file!\n");
                    exit(1);
                }
            }
        }

        // printf("Injuries and Fatalities over 0 counter: %d\n", counter);
        // printf("Total dataset size: %d\n", totalCounter);

        // outputFile.write(columns, strlen(columns));
        // // violentOutputFile.write(columns, strlen(columns));
        // for (u32 index = 0; index < DATASET_SIZE; ++index)
        // {
        //     u32 snprintfValue = snprintf(csvLineBuffer, MAX_LINE_SIZE, "%d,%d\n",
        //                                  tornados[index].year,
        //                                  tornados[index].month);

        //     if (snprintfValue < 0)
        //     {
        //         perror("An Error has ocurred while writing to the output file!\n");
        //         exit(1);
        //     }
        //     outputFile.write(csvLineBuffer, snprintfValue);

        //     if (outputFile.bad())
        //     {
        //         perror("An Error has ocurred while writing to the output file!\n");
        //         exit(1);
        //     }

        // snprintfValue = snprintf(csvViolentBuffer, MAX_LINE_SIZE, "%d,%d,%d,%s,%s,%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%d\n",
        //                          mostViolentTornados[violentIndex].year,
        //                          mostViolentTornados[violentIndex].month,
        //                          mostViolentTornados[violentIndex].day,
        //                          mostViolentTornados[violentIndex].date,
        //                          mostViolentTornados[violentIndex].state,
        //                          (mostViolentTornados[violentIndex].magnitude < 0) ? 5 : mostViolentTornados[violentIndex].magnitude,
        //                          mostViolentTornados[violentIndex].injuries,
        //                          mostViolentTornados[violentIndex].fatalities,
        //                          mostViolentTornados[violentIndex].beginningLatitude,
        //                          mostViolentTornados[violentIndex].beginningLongitude,
        //                          mostViolentTornados[violentIndex].endLatitude,
        //                          mostViolentTornados[violentIndex].endLongitude,
        //                          mostViolentTornados[violentIndex].tornadoLength,
        //                          mostViolentTornados[violentIndex].tornadoWidth);

        // if (snprintfValue < 0)
        // {
        //     perror("An Error has ocurred while writing to the output file!\n");
        //     exit(1);
        // }

        // // printf("%s", csvLineBuffer);
        // violentOutputFile.write(csvViolentBuffer, snprintfValue);

        // if (outputFile.bad())
        // {
        //     perror("An Error has ocurred while writing to the output file!\n");
        //     exit(1);
        // }
        // memset(csvLineBuffer, 0, snprintfValue);
    }
    outputFile.close();
    // violentOutputFile.close();
    if (outputFile.bad())
    {
        perror("An Error has ocurred while closing output file!\n");
        exit(1);
    }
    // for (u32 index = 0; index < DATASET_SIZE; ++index)
    // {
    //     if ((tornados[index].magnitude > 3) && (tornados[index].injuries))
    // }

    // free(magnitudeGraph->edge);
    // magnitudeGraph->edge = NULL;
    // free(magnitudeGraph);
    // magnitudeGraph = NULL;
    free(tornados);
    tornados = NULL;
    converterCsvToGml();
    return 0;
}