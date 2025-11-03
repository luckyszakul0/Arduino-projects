//  dot - 1 unit
//  dash - 3 units
//  time between dot/dash - 1 unit
//  time between letters - 3 units
//  time between words - 7 units

struct Map {
    const char letter;
    const String config;
};

//  map for all letters in morse code - 1 means dash, 0 means dot
Map morseDict[] = {
    {'A', "01"},
    {'B', "1000"},
    {'C', "1010"},
    {'D', "100"},
    {'E', "0"},
    {'F', "0010"},
    {'G', "100"},
    {'H', "0000"},
    {'I', "00"},
    {'J', "0111"},
    {'K', "101"},
    {'L', "0100"},
    {'M', "11"},
    {'N', "10"},
    {'O', "111"},
    {'P', "0110"},
    {'Q', "1101"},
    {'R', "010"},
    {'S', "000"},
    {'T', "1"},
    {'U', "001"},
    {'V', "0001"},
    {'W', "011"},
    {'X', "1001"},
    {'Y', "1011"},
    {'Z', "1100"},
    {'1', "01111"},
    {'2', "00111"},
    {'3', "00011"},
    {'4', "00001"},
    {'5', "00000"},
    {'6', "10000"},
    {'7', "11000"},
    {'8', "11100"},
    {'9', "11110"},
    {'0', "11111"}
};
string sentence;

void setup(){
    Serial.begin(9600);
}

void loop(){
    Serial.println("Enter a sentence or word to encode into Morse code: ");
    while(Serial.available() == 0){}
    sentence = Serial.readString();
}