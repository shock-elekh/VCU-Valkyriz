int val_potentiometre = 0;


const int LED = 4;
const int port_potentiometre = A0;



void setup() {
  pinMode(port_potentiometre, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val_potentiometre = analogRead(port_potentiometre);
  int valeur = map(val_potentiometre, 0, 1023, 0, 255);
  analogWrite(LED, valeur);

Serial.println(val_potentiometre);
delay(200);

}
