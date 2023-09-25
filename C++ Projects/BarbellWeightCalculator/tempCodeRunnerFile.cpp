#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include <limits>
using namespace std;
/*
This program will help a user calculate weight on the barbell with 2 options:
    Calculate Specific weight to load, or
    find current weight loaded
*/

string convertReadableColor(const string inputColor);
string convertlowerCase(string inputStr);
void calculateWeightLoaded();
void calculatePlatesToLoad();

int main() {
    int userInput;
    bool validInput = false;

    cout << "Please Select an option: (1 or 2)" << endl;    //output options to user
    cout << "1. Calculate Plates to Load" << endl;
    cout << "2. Calculate Weight Loaded" << endl;

    while (!validInput) {
    if (cin >> userInput && (userInput == 1 || userInput == 2)) {
        validInput = true; // Set validInput to true if the input is valid
    } else {
        cout << "Invalid option! Please choose 1 or 2: ";
        cin.clear(); // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear invalid input from the buffer
    }
}
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (userInput == 1){
        calculatePlatesToLoad();
    }
    else if(userInput == 2){
        calculateWeightLoaded();
    }
    system("pause");
    return 0;
}
/*calculatePlatesToLoad function will calculate proper plates to load based off user input.*/
void calculatePlatesToLoad(){
    double goalWeight;
    cout << "Please Enter Target Weight (in kg):\n";
    cin >> goalWeight;
    double remainingWeight = goalWeight - 20.0; //subtract 20kg for weight of barbell

    //find amount of specific plate by taking remaining weight and dividing by weight of plates as a pair
    //use cast as int to follow integer division; only want a whole number
    //update remainingWeight by subtracting the weight already accounted for
    
    int amountReds = static_cast<int>(remainingWeight / 50.0); 
    remainingWeight = remainingWeight - (amountReds * 50.0);
    int amountBlues = static_cast<int>(remainingWeight / 40.0);
    remainingWeight = remainingWeight - (amountBlues * 40.0);
    int amountYellows = static_cast<int>(remainingWeight / 30.0);
    remainingWeight = remainingWeight - (amountYellows * 30.0);
    int amountGreens = static_cast<int>(remainingWeight / 20.0);
    remainingWeight = remainingWeight - (amountGreens * 20.0);
    int amountWhites = static_cast<int>(remainingWeight / 10.0);
    remainingWeight = remainingWeight - (amountWhites * 10.0);
    int amountBlacks = static_cast<int>(remainingWeight / 5.0);
    remainingWeight = remainingWeight - (amountBlacks * 5.0);
    int amountSilvers = static_cast<int>(remainingWeight / 2.5);

    cout << "Load these on each side for : " << goalWeight << endl;
    if (amountReds > 0) {
        if(amountReds == 1) cout << "1 red plate\n";
        else cout << amountReds << " red plates\n";
    }
    if (amountBlues > 0) {
        if(amountBlues == 1) cout << "1 blue plate\n";
        else cout << amountBlues << " blue plates\n";
    }
    if (amountYellows > 0) {
        if(amountYellows == 1) cout << "1 yellow plate\n";
        else cout << amountYellows << " yellow plates\n";
    }
    if (amountGreens > 0) {
        if(amountGreens == 1) cout << "1 green plate\n";
        else cout << amountGreens << " green plates\n";
    }
    if (amountWhites > 0) {
        if(amountWhites == 1) cout << "1 white plate\n";
        else cout << amountWhites << " white plates\n";
    }
    if (amountBlacks > 0) {
        if(amountBlacks == 1) cout << "1 black plate\n";
        else cout << amountBlacks << " black plates\n";
    }
    if (amountSilvers > 0) {
        if(amountSilvers == 1) cout << "1 silver plate\n";
        else cout << amountSilvers << " silver plates\n";
    }

}
/*calculateWeightLoaded function will calculate weight already loaded on a bar*/
void calculateWeightLoaded(){
        const double barbellWeight = 20.0; //Weight of bar in kilograms

    //map holds weight of each type of plate in kilograms
    map<string, double> plateWeights;
    plateWeights["red"] = 25.0;
    plateWeights["blue"] = 20.0;
    plateWeights["yellow"] = 15.0;
    plateWeights["green"] = 10.0;
    plateWeights["white"] = 5.0;
    plateWeights["black"] = 2.5;
    plateWeights["silver"] = 1.25;
    
    string userInput;
    cout << "======= WEIGHT CALCULATOR =======\n";
    cout << "Please Enter amount of each plate loaded! (ex. 3 red plates 1 blue plates 1 black plate....)\n";

    getline(cin, userInput);

    istringstream iss(userInput);
    string word;
    map<string, int> plateQuantities; //new map holds amount/quantity of each plate

   int quantity = 0;
   while (iss >> word) {
        if (isdigit(word[0])) {
            // If the word starts with a digit, it's a quantity
            quantity = stoi(word);
            // next word after a quantity will be a plate color
            iss >> word;
            // Add the quantity to the plate color and reset the quantity
            string color = convertReadableColor(word);  //converts color to singular when plural "reds" to red.
            plateQuantities[color] += quantity; // adds the quantity to the map
        }
    }
    //Display Quantities
    cout << "Plate Quantities:\n";
    for (const auto& pair : plateQuantities) {
        const string& color = pair.first;
        int quantity = pair.second;
        cout << color << ": " << quantity << endl;
    }
    //Calculate totalWeight loaded

    double totalWeight = barbellWeight;
    for (const auto& pair: plateQuantities) {
        const string& color = pair.first;
        int quantity = pair.second;
        double plateWeight = plateWeights[color];
        totalWeight += quantity * (2*plateWeight);
    }
    cout << "Total weight loaded on the barbell: " << totalWeight << " kilograms/ " << totalWeight * 2.20462 << " pounds" << endl;
    //cout << "Total weight loaded on the barbell: " << totalWeight * 2.20462 << " pounds" << endl;

    

}
/*convertlowerCase function converts entire string to lowercase*/
string convertlowerCase(string inputStr){
    string str = inputStr;
    // loop converts string to lowercase
    for (char &c : str){
        c = tolower(c);
    }
    return str;
}
/*convertReadableColor function allows userInput to be flexible when typing amount of plates. "3 reds" can be read the same as "3 red plates"*/
string convertReadableColor(const string inputColor){

    //convert string to lowercase 
    string color;
    color = convertlowerCase(inputColor);

    if (color == "red" || color == "reds") {
        return "red";
    } else if (color == "blue" || color == "blues") {
        return "blue";
    } else if (color == "yellow" || color == "yellows") {
        return "yellow";
    } else if (color == "green" || color == "greens") {
        return "green";
    } else if (color == "white" || color == "whites") {
        return "white";
    } else if (color == "black" || color == "blacks") {
        return "black";
    } else if (color == "silver" || color == "silvers") {
        return "silver";
    } else {
        return color;
    }
}
