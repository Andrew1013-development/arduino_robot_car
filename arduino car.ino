#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define TRIG_PIN 9
#define ECHO_PIN 10
#define MIN_SPEED 0
#define MAX_SPEED 255
#define DEG90 25

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  Serial.begin(9600);
}

void M1_Dung() {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
}

void M2_Dung() {
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void M1_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, 255 - speed);
}

void M1_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, speed);
}

void M2_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, speed);
}

void M2_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, 255 - speed);
}

void TienThang(int speed) {
  M1_Tien(speed);
  M2_Tien(speed);
} 

void LuiThang(int speed) {
  M1_Lui(speed);
  M2_Lui(speed);
}

void QueoPhai(int speed) {
  M1_Tien(speed);
  M2_Lui(speed);
}

void QueoTrai(int speed) {
  M1_Lui(speed);
  M2_Tien(speed);
}

void DungLai() {
  M1_Dung();
  M2_Dung();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG_PIN,LOW);
  delay(2);
  digitalWrite(TRIG_PIN,HIGH);
  delay(10);
  digitalWrite(TRIG_PIN,LOW);
  float duration = pulseIn(ECHO_PIN,HIGH);
  float distance = duration * 0.034 / 2; //ultrasonic distance
  if (distance <= 25) {
    DungLai();
    QueoPhai(MAX_SPEED);
    delay(DEG90);
    duration = pulseIn(ECHO_PIN,HIGH);
    float distance_right = duration * 0.034 / 2;
    QueoTrai(MAX_SPEED);
    delay(DEG90*2);
    duration = pulseIn(ECHO_PIN,HIGH);
    float distance_left = duration * 0.034 / 2;
    if (distance_left > distance_right) {
      TienThang(MAX_SPEED);
    } else {
      QueoPhai(DEG90);
    }
  } else {
    TienThang(MAX_SPEED);
  }
  //Serial.println(distance);
}