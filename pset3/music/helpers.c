// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = atoi(&fraction[0]);
    int denominator = atoi(&fraction[2]);
    // printf("%i  %i\n", numerator, denominator);
    if (denominator == 8)
    {
        // printf("%i\n", numerator);
        // return numerator;
        ;
    }
    else if (denominator == 4)
    {
        numerator *= 2;
        // printf("%i\n", numerator);
        // return numerator;
    }
    else if (denominator == 2)
    {
        numerator *= 4;
        // printf("%i\n", numerator);
        // return numerator;
    }
    else if (denominator == 16)
    {
        numerator /= 2;
        // printf("%i\n", numerator);
        // return numerator;
    }

    return numerator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char letter;
    char acc;
    int octave;
    int noteLen = strlen(note);
    // natural note or accidental
    if (noteLen == 2)
    {
        // obtain "A or B etc"
        letter = note[0];
        // obtain octave
        octave = note[1] - '0';
    }
    else //if (strlen(note) == 3)
    {
        // obtain "A or B etc"
        letter = note[0];
        // obtain accidental
        acc = note[1];
        // obtain octave
        octave = note[2] - '0';
    }

    float freq = 440;

    // determine octave
    if (octave > 4)
    {
        freq = freq * ((octave - 4) * 2);
    }
    else if (octave < 4)
    {
        freq = freq / (abs((octave - 4)) * 2);
    }
    //determine letter
    if (letter >= 'C' && letter <= 'G')
    {
        float x = (float) 2;
        float y = (float)((2 * (float)(letter - 'A' - 7)) / 12);
        freq = freq * (float) pow(x, y);
        // compensate for missing accidental
        if (letter >= 'C' && letter <= 'E')
        {
            x = (float) 2;
            y = (float)(1.0 / 12.0);
            freq = freq * (float) pow(x, y);
        }
    }
    else if (letter == 'A' || letter == 'B')
    {
        float x = (float) 2;
        float y = (float)((2 * (float)(letter - 'A')) / 12);
        freq = freq * (float) pow(x, y);
    }
    // determing accidental
    if (noteLen == 3)
    {
        if (acc == '#')
        {
            float x = (float) 2;
            float y = (1.0 / 12.0);
            freq = freq * (float) pow(x, y);
        }
        else if (acc == 'b')
        {
            float x = (float) 2;
            float y = (1.0 / 12.0);
            freq = freq / (float) pow(x, y);
        }
        else
        {
            return (float) freq;
        }
    }
    // round final frequency
    float rndFreq = (float) round(freq);
    return rndFreq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
