#include <Keypad.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

#define Password_Lenght 7 // Give enough room for six chars + NULL char

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7

char Master[Password_Lenght] = "123456";

byte data_count = 0, master_count = 0;

bool Pass_is_good;

char customKey;

const byte ROWS = 4;

const byte COLS = 3;

char keys[ROWS][COLS] = {

  {'1', '2', '3'},

  {'4', '5', '6'},

  {'7', '8', '9'},

  {'*', '0', '#'}

};

bool door = true;

byte rowPins[ROWS] = {1, 2, 3, 4}; //connect to the row pinouts of the keypad

byte colPins[COLS] = {5, 6, 7}; //connect to the column pinouts of the keypad

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

void setup()

{

  lcd.begin(16, 2);

  lcd.print(" Pratz Door Lock");

  delay(2000);

  lcd.clear();

}

void loop()

{

  if (door == 0)

  {

    customKey = customKeypad.getKey();

    if (customKey == '#')

    {

      lcd.clear();

      lcd.print("  Door is close");

      delay(2000);

      door = 1;

    }

  }

  else Open();

}

void clearData()

{

  while (data_count != 0)

  { // This can be used for any array size,

    Data[data_count--] = 0; //clear array for new data

  }

  return;

}

void Open()

{

  lcd.setCursor(0, 0);

  lcd.print(" Enter Password ");

  customKey = customKeypad.getKey();

  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)

  {

    Data[data_count] = customKey; // store char into data array

    lcd.setCursor(data_count, 1); // move cursor to show each new char

    lcd.print(Data[data_count]); // print char at said cursor

    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered

  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master

  {

    if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)

    {

      lcd.clear();

      lcd.print(" Access Granted ");

      door = 0;

    }
    else 
    {
    
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Jldi Whn Se Hato"); 
      lcd.setCursor(0, 1);
      lcd.print("Hat BC utar Jldi"); 

      delay(3000);
      lcd.clear();

      door = 1;

    }

    clearData();

  }
}

   