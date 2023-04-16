
const char TERMINATING_CHAR = 0x10;
const unsigned int MAX_BYTES = 100;

const int CMD_TOKEN = 0;
const int TOKEN_LEFT_SPEED = 1;
const int TOKEN_RIGHT_SPEED = 2;
const int TOKEN_LEFT_DIRECTION = 3;
const int TOKEN_RIGHT_DIRECTION = 4;

const char CMD_MOVE = 0x20;

char bufferArray[MAX_BYTES];

const int E1 = 5;     
const int E2 = 6;     
const int M1 = 4;    
const int M2 = 7; 

void stop(void)                    
{
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
}

void move(char valLeft, char valRight, char directionLeft, char directionRight)          
{
  analogWrite (E1, valLeft);      
  digitalWrite(M1, directionLeft);
  analogWrite (E2, valRight);
  digitalWrite(M2, directionRight);
}

void setup(void)
{
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  Serial.begin(115200);  
  Serial.setTimeout(1000);
}

void loop(void)
{
  memset(bufferArray, 0, sizeof(bufferArray));
  if (Serial.available()) {
    Serial.readBytesUntil(TERMINATING_CHAR, bufferArray, MAX_BYTES);   
    char cmd = bufferArray[CMD_TOKEN];
    if (cmd == CMD_MOVE) {      
      move(bufferArray[TOKEN_LEFT_SPEED], bufferArray[TOKEN_RIGHT_SPEED], bufferArray[TOKEN_LEFT_DIRECTION], bufferArray[TOKEN_RIGHT_DIRECTION]);
      Serial.write("OK");      
    } else {
      Serial.write("FAIL");
    }
    Serial.flush();
  }
}
