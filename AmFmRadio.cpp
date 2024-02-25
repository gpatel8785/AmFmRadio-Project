/*
* File: AmFmRadio.cpp
* Program: OOP - Assignment 3
* Programmer: Gaurav Patel
* Date: 23/02/2024
* Description: This program simulates the functionality of a simple AM/FM radio controller.
*			 It allows users to interact with the radio through a menu-driven interface,
*			 providing options to toggle the power, set volume, toggle between AM and FM bands,
*			 set and select preset buttons, scan frequencies up and down, and display current settings.
*			 The program utilizes object-oriented principles to encapsulate the radio's state and behavior
*			 within the AmFmRadio class, providing a modular and maintainable design.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AmFmRadio.h"
#include <iostream>  // include for printing


// Implementation of the member functions for the AmFmRadio class.
// Includes the constructor, destructor, and various methods for controlling and displaying the radio.
// Also, contains the definition of the Freqs structure and relevant header files.

// Constructor with a boolean parameter indicating whether the radio should be initially on
AmFmRadio::AmFmRadio(bool initialRadioState)
{
    // Initialize all private data using provided parameters
    for (int i = 0; i < 5; ++i)
    {
        button[i].AMFreq = 530;
        button[i].FMFreq = 87.9;
    }

    current_station = 530;
    strcpy_s(band, "AM");
    volume = 0;
    on = initialRadioState;
}

// Constructor with a boolean parameter indicating whether the radio should be initially on
// and an array of 5 struct Freqs for initial radio preset values
AmFmRadio::AmFmRadio(bool initialRadioState, Freqs initialPresets[5])
{
    // Initialize all private data using provided parameters
    for (int i = 0; i < 5; ++i)
    {
        button[i] = initialPresets[i];
    }

    current_station = initialPresets[0].AMFreq;
    strcpy_s(band, "AM");
    volume = 0;
    on = initialRadioState;
}


// Destructor
AmFmRadio::~AmFmRadio()
{
    if (displayOutput) {
        printf("Destroying AmFmRadio\n");
    }
}

/*
* Function: PowerToggle
* Description: Toggles the power status of the radio.
* Parameters: None
* Returns: None
*/
// Method to toggle the power state of the radio
void AmFmRadio::PowerToggle()
{
    if (!on)  // If turning the radio on after being off
    {
        on = true;

        // Restore the previous volume level
        volume = previousVolume;

        if (strcmp(band, "AM") == 0)
        {
            // If the previous AM station is valid, set the current station to the previous AM station
            if (previousAMStation >= 530 && previousAMStation <= 1700)
            {
                current_station = previousAMStation;
                std::cout << "\nRadio is on. Tuned to previous AM station: " << current_station << " " << band << std::endl;
            }
            else
            {
                current_station = button[0].AMFreq;  // Go to the first AM preset if the previous AM station is not valid
                std::cout << "\nRadio is on. Tuned to default AM station: " << current_station << " " << band << std::endl;
            }
        }
        else
        {
            // If the previous FM station is valid, set the current station to the previous FM station
            if (previousFMStation >= 87.9 && previousFMStation <= 107.9)
            {
                current_station = previousFMStation;
                std::cout << "\nRadio is on. Tuned to previous FM station: " << current_station << " " << band << std::endl;
            }
            else
            {
                current_station = button[0].FMFreq;  // Go to the first FM preset if the previous FM station is not valid
                std::cout << "\nRadio is on. Tuned to default FM station: " << current_station << " " << band << std::endl;
            }
        }
    }
    else  // If turning the radio off
    {
        on = false;

        // Save the current volume level as the previous volume
        previousVolume = volume;
        volume = 0;  // Set the volume level to 0
        std::cout << "\nRadio is off. Volume turned down to 0." << std::endl;
    }
}

/*
* Function: IsRadioOn
* Description: Checks if the radio is turned on.
* Parameters: None
* Returns: A boolean value indicating the power status of the radio.
*/
// Method to check if the radio is currently powered on
bool AmFmRadio::IsRadioOn()
{
    return on;
}

/*
* Function: SetVolume
* Description: Sets the volume level of the radio.
* Parameters: None
* Returns: An integer representing the status of volume setting:
*           0 - Volume set to 0
*           1 - Volume set successfully
*           2 - Volume set to maximum (100)
*/
// Method to set the volume level
int AmFmRadio::SetVolume() //original SetVolume method
{
    char buf[20] = "";

    printf("\nEnter the volume level (0 - 100). ");
    fgets(buf, sizeof buf, stdin);
    volume = atoi(buf);

    if (volume < 0) //if user enters volume less than 0, volume = 0
    {
        volume = 0;
        return 0;
    }

    if (volume > 100) //if user enters volume greater than 100, volume = 100
    {
        volume = 100;
        return 2;
    }
    return 1;


}


// Overloaded method to set the volume level with a parameter
int AmFmRadio::SetVolume(int newVolume) // New version of SetVolume taking a parameter
{
    if (newVolume < 0)
    {
        volume = 0;
        return 0;
    }
    else if (newVolume > 100)
    {
        volume = 100;
        return 2;
    }
    else
    {
        volume = newVolume;
        return 1;
    }
}

/*
* Function: ToggleBand
* Description: Toggles between AM and FM bands.
* Parameters: None
* Returns: None
*/
// Method to toggle between AM and FM bands
void AmFmRadio::ToggleBand()
{
    if (strcmp(band, "AM") == 0)
    {
        // Save the current station as the previous AM station
        previousAMStation = current_station;

        strcpy_s(band, "FM");
        current_station = button[0].FMFreq;  // Go to the first FM preset when switching
        std::cout << "\nSwitched to FM. Current station: " << current_station << " " << band << std::endl;
    }
    else
    {
        // Save the current station as the previous FM station
        previousFMStation = current_station;

        strcpy_s(band, "AM");
        current_station = button[0].AMFreq;  // Go to the first AM preset when switching
        std::cout << "\nSwitched to AM. Current station: " << current_station << " " << band << std::endl;
    }
}

/*
* Function: SetPresetButton
* Description: Sets a preset button with the current station.
* Parameters:
*  - button_num: The number of the preset button to set.
* Returns: An integer representing the status of button setting:
*           0 - Invalid button number
*           1 - Button set successfully
*/
// Method to set a preset button with the current station
int AmFmRadio::SetPresetButton(int button_num)
{
    if ((button_num >= 0) && (button_num <= 4))
    {
        if (strcmp("AM", band) == 0)
        {
            button[button_num].AMFreq = current_station;
        }
        else
        {
            button[button_num].FMFreq = current_station;
        }
        return 1;

    }
    return 0;

}

/*
* Function: SelectPresetButton
* Description: Selects a preset button and tunes to its frequency.
* Parameters:
*  - button_num: The number of the preset button to select.
* Returns: An integer representing the status of button selection:
*           0 - Invalid button number
*           1 - Button selected successfully
*/
// Method to select a preset button and tune the radio to the corresponding station
int AmFmRadio::SelectPresetButton(int button_num)
{
    if ((button_num >= 0) && (button_num <= 4))
    {
        if (strcmp("AM", band) == 0)
        {
            current_station = button[button_num].AMFreq;
        }
        else
        {
            current_station = button[button_num].FMFreq;
        }

        return 1;
    }
    return 0;


}

/*
* Function: ShowCurrentSettings
* Description: Displays the current settings of the radio.
* Parameters: None
* Returns: None
*/
// Method to show the current settings of the radio
void AmFmRadio::ShowCurrentSettings()
{

    if (on == true)
    {
        printf("\n\nRadio is on. \n");
    }
    else
    {
        printf("\n\nRadio is off. \n");
    }

    printf("\nRadio Band: %s\n", band);
    printf("Volume: %d\n", volume);
    printf("Current Station: %.1f %s\n", current_station, band);
    printf("AM Button Settings: ");
    for (int i = 0; i < 5; ++i)
    {
        printf("%d) %6d ", i + 1, button[i].AMFreq);
    }

    printf("\nFM Button Settings: ");
    for (int j = 0; j < 5; ++j)
    {
        printf("%d) %6.1f ", j + 1, button[j].FMFreq);
    }
}


// Mutator method for the current_station data member
void AmFmRadio::setCurrentStation(double station)
{
    // Check if the station is within valid ranges for AM and FM
    if ((strcmp(band, "AM") == 0 && (station >= 530 && station <= 1700)) ||
        (strcmp(band, "FM") == 0 && (station >= 87.9 && station <= 107.9)))
    {
        current_station = station;
        std::cout << "\nCurrent station set to: " << current_station << " " << band << std::endl;
    }
    else
    {
        std::cout << "\nInvalid station value or band. No changes made." << std::endl;
    }
}

// Mutator method for the displayOutput data member
void AmFmRadio::SetDisplayOutput(bool display)
{
    displayOutput = display;
}

// Method to enable output by setting displayOutput to true
void AmFmRadio::EnableOutput()
{
    displayOutput = true;
}
// Method to disable output by setting displayOutput to false
void AmFmRadio::DisableOutput()
{
    displayOutput = false;
}

/*
* Function: ScanUp
* Description: Scans to the next higher frequency.
* Parameters: None
* Returns: None
*/
// Method to change the frequency up in increments of 0.2 for FM, 10 for AM
void AmFmRadio::ScanUp()
{
    if (strcmp("AM", band) == 0)
    {
        // If current_station is the maximum frequency, set it to the minimum frequency
        if (current_station == 1700)
        {
            current_station = 530;
        }
        else
        {
            current_station = current_station + 10;
        }
    }
    else
    {
        // If the current_station is the maximum frequency, set it to the minimum frequency
        // Note:  AmFmradios jump 0.2 for the FM. That's how it's modeled here.
        if (current_station >= 107.9)
        {
            current_station = 87.9;
        }
        else
        {
            current_station = current_station + 0.2;
        }
    }

    if (displayOutput)
    {
        printf("\nCurrent station: %f %s\n", current_station, band);
    }
}

/*
* Function: ScanDown
* Description: Scans to the next lower frequency.
* Parameters: None
* Returns: None
*/
// Method to change the frequency down in increments of 0.2 for FM, 10 for AM
void AmFmRadio::ScanDown()
{
    if (strcmp("AM", band) == 0)
    {
        // If current_station is the minimum frequency, set it to the maximum frequency
        if (current_station == 530)
        {
            current_station = 1700;
        }
        else
        {
            current_station = current_station - 10;
        }
    }
    else
    {
        // If the current_station is the minimum frequency, set it to the maximum frequency
        // Note:AmFmradios jump 0.2 for the FM. That's how it's modeled here.
        if (current_station <= 87.9)
        {
            current_station = 107.9;
        }
        else
        {
            current_station = current_station - 0.2;
        }
    }

    if (displayOutput)
    {
        printf("\nCurrent station: %.1f %s\n", current_station, band);
    }
}


// Accessor for current_station
double AmFmRadio::getCurrentStation() const
{
    return current_station;
}

// Accessor for volume
int AmFmRadio::getCurrentVolume() const
{
    return volume;
}

// Accessor for radio presets
Freqs AmFmRadio::getRadioPresets() const
{
    return button[0];  // Return the first preset
}

// Accessor for current band
const char* AmFmRadio::getCurrentBand() const
{
    return band;
}

// Accessor for displayOutput
bool AmFmRadio::getDisplayOutput() const
{
    return displayOutput;
}
