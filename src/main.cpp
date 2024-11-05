#include <Arduino.h>

// Pin Definitions
#define RGB_RED_PIN 6
#define RGB_GREEN_PIN 5
#define RGB_BLUE_PIN 8
#define START_STOP_BUTTON_PIN 2
#define DIFFICULTY_BUTTON_PIN 3

// Game Variables
int difficultyLevel = 0; // 0: Easy, 1: Medium, 2: Hard
unsigned long roundStartTime;// Start time of the current round
int wordsCorrect = 0;// Number of correct words typed
bool gameActive = false; // Game state flag
const char* difficultyMessages[] = {"Easy mode on!", "Medium mode on!", "Hard mode on!"}; // Messages for each difficulty level
const int difficultyDelays[] = {3000, 2000, 1000}; // Delays in ms for Easy, Medium, Hard
unsigned long lastWordTime = 0;// Last time a word was generated
String currentWord = "";// Variable for current word to type
String wordList[] = {"hello", "world", "arduino", "race", "game", "play", "code", "learn", "fun", "build"}; // Dictionary
int numWords = sizeof(wordList) / sizeof(wordList[0]);// Number of words in the dictionary
volatile bool buttonPressed = false;// Button press flag
volatile bool difficultyButtonPressed = false;// Difficulty button press flag
const unsigned int endRoundTime = 30000;// Round duration in ms

// Variables for Debouncing
unsigned long lastDebounceTimeStart = 0;// Last time the start/stop button was pressed
unsigned long lastDebounceTimeDifficulty = 0;// Last time the difficulty button was pressed
const unsigned long debounceDelay = 50; // 50ms debounce delay

// New variable for user input
String userInput = "";

// Function to Set RGB LED Color
void setRGBColor(int red, int green, int blue) {
    analogWrite(RGB_RED_PIN, 255 - red);// Common Anode RGB LED
    analogWrite(RGB_GREEN_PIN, 255 - green);// Invert the color values
    analogWrite(RGB_BLUE_PIN, 255 - blue);// to match the common anode LED
}

// Function to handle the start/stop button press with debouncing logic
void handleStartStop() {
    unsigned long currentTime = millis();// Get the current time
    if ((currentTime - lastDebounceTimeStart) > debounceDelay) {// Check if the time difference is greater than the debounce delay
        buttonPressed = true;// Set the button press flag
        lastDebounceTimeStart = currentTime;// Update the last debounce time
    }
}

// Function to handle the difficulty button press and cycle through difficulty levels
void handleDifficulty() {
    unsigned long currentTime = millis();// Get the current time
    if ((currentTime - lastDebounceTimeDifficulty) > debounceDelay) {// Check if the time difference is greater than the debounce delay
        difficultyButtonPressed = true;// Set the button press flag
        lastDebounceTimeDifficulty = currentTime;// Update the last debounce time
    }
}

// Start Countdown Sequence
void startCountdown() {
    for (int i = 3; i > 0; i--) { // Countdown from 3 to 1
        setRGBColor(255, 255, 255); // LED White Blink
        delay(500); // LED White Blink
        setRGBColor(0, 0, 0); // LED Off
        delay(500);// LED Off
        Serial.println(i);// Print the countdown number
    }
}

// Generate Random Word
void generateWord() {
    int randomIndex = random(numWords);// Generate a random index
    currentWord = wordList[randomIndex];// Get the word at the random index
    Serial.println("Type the word: " + currentWord);// Print the word to the serial monitor
}

// Setup Code
void setup() {
    Serial.begin(9600);// Initialize Serial Communication
    pinMode(RGB_RED_PIN, OUTPUT);// Set RGB LED RED Pin as Output
    pinMode(RGB_GREEN_PIN, OUTPUT);// Set RGB LED GREEN Pin as Output
    pinMode(RGB_BLUE_PIN, OUTPUT);// Set RGB BLUE LED Pin as Output
    pinMode(START_STOP_BUTTON_PIN, INPUT_PULLUP);// Set Start/Stop Button Pin as Input with Pull-up Resistor
    pinMode(DIFFICULTY_BUTTON_PIN, INPUT_PULLUP);// Set Difficulty Button Pin as Input with Pull-up Resistor

    attachInterrupt(digitalPinToInterrupt(START_STOP_BUTTON_PIN), handleStartStop, FALLING);// Attach Interrupt for Start/Stop Button
    attachInterrupt(digitalPinToInterrupt(DIFFICULTY_BUTTON_PIN), handleDifficulty, FALLING);// Attach Interrupt for Difficulty Button

    setRGBColor(255, 255, 255); // White for idle
    Serial.println("Game in idle mode. Set difficulty and press start to begin.");
}

// Main Loop
void loop() {
    // Handle Difficulty Button
    if (difficultyButtonPressed && !gameActive) {// Check if the difficulty button was pressed and the game is not active
        difficultyLevel = (difficultyLevel + 1) % 3;// Cycle through difficulty levels
        Serial.println(difficultyMessages[difficultyLevel]);// Print the difficulty message
        difficultyButtonPressed = false;// Reset the button press flag
    }

    // Handle Start/Stop Button
    if (buttonPressed) {
        buttonPressed = false;
        if (!gameActive) {
            gameActive = true;
            startCountdown();
            roundStartTime = millis();// Start the round timer
            setRGBColor(0, 255, 0); // Start with Green LED
            generateWord();// Generate the first word
            lastWordTime = millis();// Update the last word time
        } else {
            gameActive = false;
            Serial.print("Round ended. Words correct: ");// End the round
            Serial.println(wordsCorrect);// Print the number of correct words
            wordsCorrect = 0;// Reset the number of correct words
            setRGBColor(255, 255, 255); // Reset to idle color
        }
    }

    // Game Active Logic
    if (gameActive) {
        if (millis() - roundStartTime >= endRoundTime) {// End the round after 30 seconds
            // End Round after 30 seconds
            gameActive = false;// Set the game state to inactive
            Serial.print("Round ended. Words correct: ");// Print the number of correct words
            Serial.println(wordsCorrect);// Print the number of correct words
            wordsCorrect = 0;// Reset the number of correct words
            setRGBColor(255, 255, 255); // Reset to idle color
        }

        // Word Typing Logic with Backspace Handling
        if (Serial.available() > 0) {
            char incomingChar = Serial.read();

            if (incomingChar == '\b') {
                // Handle backspace: remove last character if possible
                if (userInput.length() > 0) {
                    userInput.remove(userInput.length() - 1);
                    Serial.print("\b \b"); // Remove character from display
                }
            } else if (incomingChar == '\n') {
                // Check if the user input matches the current word
                userInput.trim(); // Remove any extraneous whitespace
                if (userInput == currentWord) {
                    setRGBColor(0, 255, 0); // Green for correct word
                    wordsCorrect++;
                    generateWord(); // Generate new word immediately
                    lastWordTime = millis(); // Update the last word time
                } else {
                    setRGBColor(255, 0, 0); // Red for incorrect word
                }
                userInput = ""; // Clear user input for next round
                } else {
                    // Add character to input string if it’s not backspace or newline
                    userInput += incomingChar;
                    Serial.print(incomingChar); // Echo the character to the terminal
                }

                // Word Timeout Logic
                if (millis() - lastWordTime >= difficultyDelays[difficultyLevel]) {
                    lastWordTime = millis(); // Update the last word time
                    generateWord(); // Generate a new word
                }
            }

        // Word Timeout Logic
        if (millis() - lastWordTime >= difficultyDelays[difficultyLevel]) {// Generate a new word after the delay
            lastWordTime = millis();// Update the last word time
            generateWord();// Generate a new word
        }
    }
}