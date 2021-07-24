// Interfaces
const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 8;
const int g = 9;
const int dotPin = 10;
const int dotListener = 11;
const int listener = 12;

// =========
int number = 0;
int displayDot = false;

int firstTimeDot = false;
int firstTimeIncrementation = false;
int currentNumber = 0;
const int d7[]{a, b, c, d, e, f, g};

const int numbers[][7]{{a, b, c, d, e, f}, {b, c}, {a, b, g, e, d}, {a, b, g, c, d}, {b, f, g, c}, {a, f, g, c, d}, {a, f, g, c, d, e}, {a, b, c}, {a, b, c, d, e, f, g}, {a, b, c, d, f, g}};

void changeDotState()
{
    displayDot = !displayDot;
    digitalWrite(dotPin, (displayDot ? HIGH : LOW));
}

void setNumberOnDisplay(unsigned short n)
{
    for (auto i : numbers[n])
        if (i > 0)
            digitalWrite(i, HIGH);
}

void turnOffAll()
{
    for (auto i : d7)
        digitalWrite(i, LOW);
}

void setup()
{
    for (auto i : d7)
        pinMode(i, OUTPUT);
    pinMode(dotPin, OUTPUT);
    pinMode(dotListener, INPUT);
    pinMode(listener, INPUT);
    setNumberOnDisplay(0);
}

void loop()
{
    while (digitalRead(dotListener) == HIGH)
    {
        delay(20);
        if (digitalRead(dotListener) == HIGH && firstTimeDot)
        {
            firstTimeDot = false;
            changeDotState();
        }
    }
    firstTimeDot = true;
    while (digitalRead(listener) == HIGH)
    {
        delay(20);
        if (digitalRead(listener) == HIGH && firstTimeIncrementation)
        {
            firstTimeIncrementation = false;
            currentNumber = (currentNumber == 9 ? 0 : ++currentNumber);
            turnOffAll();
            setNumberOnDisplay(currentNumber);
        }
    }
    firstTimeIncrementation = true;
}