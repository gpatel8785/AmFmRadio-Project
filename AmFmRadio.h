// AmFmRadio.h
// Header file for the AmFmRadio class.
// Defines the class structure, private data members, and public member functions.
// Also, includes the definition of the Freqs structure used in the class.

#ifndef _AMFMRADIO_H
#define _AMFMRADIO_H

struct Freqs
{
    int AMFreq;
    float FMFreq;
};

class AmFmRadio
{
private:
    Freqs button[5];
    double current_station;
    char band[3];
    int volume;
    bool on;

    double previousAMStation; // New data member for the previous AM station
    float previousFMStation;  // New data member for the previous FM station
    int previousVolume;       // New data member for the previous volume level

    bool displayOutput; // New private boolean data member

public:
    // sets the each button to the lowest frequency, sets the current station, sets the
    // frequency to AM, sets the volume to 0 and sets on to false
    AmFmRadio();

    // Constructor with a bool parameter indicating whether the radio should be on
    // (default is false)
    AmFmRadio(bool initialOn);

    // Constructor with a bool parameter indicating whether the radio should be on
    // (default is false) and an array of 5 struct Freqs for initial radio preset values
    AmFmRadio(bool initialOn, Freqs initialPresets[5]);

    // Destructor
    ~AmFmRadio();

    // sets on to true
    void PowerToggle();

    // returns a true if the radio is currently powered on, and false if the radio is in
    // the off position
    bool IsRadioOn();

    // toggles frequency between AM and FM and sets current station
    void ToggleBand();

    // sets button (radio preset) with current station by being passed a button number
    int SetPresetButton(int button_num);

    // sets current station to radio preset by being passed a button number
    int SelectPresetButton(int button_num);

    // sets volume
    int SetVolume(); // Existing SetVolume method

    int SetVolume(int newVolume); // New version of SetVolume taking a parameter

    // New mutator for displayOutput
    void SetDisplayOutput(bool display);

    // New methods to toggle displayOutput
    void EnableOutput();
    void DisableOutput();

    // shows volume, button settings, current station, AM or FM
    void ShowCurrentSettings();

    // Mutator for current_station
    void setCurrentStation(double station);

    // changes frequency up in increments of .2 for FM, 10 for AM
    void ScanUp();

    // changes frequency down in increments of .2 for FM, 10 for AM
    void ScanDown();

    // Accessor for current_station
    double getCurrentStation() const;

    // Accessor for volume
    int getCurrentVolume() const;

    // Accessor for radio presets
    Freqs getRadioPresets() const;

    // Accessor for current band
    const char* getCurrentBand() const;

    // Accessor for displayOutput
    bool getDisplayOutput() const;
};
#endif