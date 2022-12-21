int motor_speed = 120;//*** Speed of the robot (120~220 is appropriate; larger the number, faster the robot)
int lr_speed_up = 20;//*** To set turning speed separately (eg. faster than the motor_seed)


int move_time = 10;//*** Length of one moving time (seconds)
int break_time = 10;//*** Length of the pause time (seconds)

int move_mode = 1;//*** Movement type: 0 = Patterned movement, 1 = Random movement

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

int motor_1 = 5;
int motor_2 = 6;
int motor_3 = 10;
int motor_4 = 11;

unsigned long start_time = 0;
unsigned long end_time = 0;
double run_time = 0;
int run_count = 0;

long lastMillis = 0;
long currentMillis = 0;

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

void setup() {
  Serial.begin(9600);
  pinMode(motor_1, OUTPUT);
  pinMode(motor_2, OUTPUT);
  pinMode(motor_3, OUTPUT);
  pinMode(motor_4, OUTPUT);
  analogWrite(motor_1, 0);
  analogWrite(motor_2, 0);
  analogWrite(motor_3, 0);
  analogWrite(motor_4, 0);

  randomSeed(analogRead(A0));

  delay(5000);//Rest for 5 seconds
  Serial.println("Start executing the loop");
}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

void loop() {
  currentMillis = millis();
  if (currentMillis - lastMillis >= 100) {
    lastMillis = currentMillis;
  }

  if (move_mode == 0) {//Patterned movement mode
    move_pattern();
    if (run_time > move_time) {
      Serial.println("");
      Serial.print("Moved over ");
      Serial.print(move_time);
      Serial.println(" seconds.");
      Serial.print("Resting for ");
      Serial.print(break_time);
      Serial.println(" seconds.");
      for (int i = 0; i < break_time; i++) {
        Serial.print(".");
        delay(1000);
      }
      Serial.println("");
      run_time = 0;
    }
  } else {//Random movement mode
    random_pattern();
    if (run_time > move_time) {
      Serial.println("");
      Serial.print("Moved over ");
      Serial.print(move_time);
      Serial.println(" seconds.");
      Serial.print("Resting for ");
      Serial.print(break_time);
      Serial.println(" seconds.");
      for (int i = 0; i < break_time; i++) {
        Serial.print(".");
        delay(1000);
      }
      Serial.println("");
      run_time = 0;
    }
  }
}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

void random_pattern() {
  start_time = millis();

  int move_time_r = random(5, 30);//*** Length of random movement (0.5 ~ 3.0 seconds)
  int stay_time_r = random(1, 10);//*** Length of pause after random movement (0.1 ~ 1.0 second)

  //motor_speed = random(100, 200);

  int r = random(1, 6);// set 'r' as random integer from [1, 5]
  // Choose movement type based on the value in 'r' (among go, back, right, left & stay)
  if (r == 1) {
    go(motor_speed, move_time_r, stay_time_r);
  } else if (r == 2) {
    back(motor_speed, move_time_r, stay_time_r);
  } else if (r == 3) {
    right(motor_speed, move_time_r, stay_time_r);
  } else if (r == 4) {
    left(motor_speed, move_time_r, stay_time_r);
  } else if (r == 5) {
    stay(stay_time_r);
  }

  end_time = millis();
  run_time = run_time + ((end_time - start_time) / 1000.0);
  run_count++;
  Serial.print("----- ----- Num. Iteration : ");
  Serial.print(run_count);

  Serial.print("     Running time : ");
  Serial.print(run_time);
  Serial.println("s");
}

void move_pattern() {
  start_time = millis();
  // ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- *****

  go(120, 30, 15);
  go(180, 30, 15);
  back(180, 30, 15);
  right(120, 30, 10);
  left(120, 30, 10);

  // ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- *****
  end_time = millis();
  run_time = run_time + ((end_time - start_time) / 1000.0);
  run_count++;
  Serial.print("----- ----- Num. Iteration : ");
  Serial.print(run_count);

  Serial.print("     Rurnning time : ");
  Serial.print(run_time);
  Serial.println("s");
}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

void go(int k, int i, int j) { //Robot move forward
  motor_speed = k;

  Serial.print("Move forward: ");
  Serial.print(i * 100.0 / 1000.0);
  Serial.println("(s)");

  analogWrite(motor_1, 0);
  analogWrite(motor_2, motor_speed);
  analogWrite(motor_3, motor_speed);
  analogWrite(motor_4, 0);
  delay(i * 100);
  stay(j);
}
void back(int k, int i, int j) { //Robot move backward
  motor_speed = k;

  Serial.print("Move backward: ");
  Serial.print(i * 100.0 / 1000.0);
  Serial.println("(s)");

  analogWrite(motor_1, motor_speed);
  analogWrite(motor_2, 0);
  analogWrite(motor_3, 0);
  analogWrite(motor_4, motor_speed);
  delay(i * 100);
  stay(j);
}
void right(int k, int i, int j) { //Robot turn right
  motor_speed = k;

  Serial.print("Turn right: ");
  Serial.print(i * 100.0 / 1000.0);
  Serial.println("(s)");

  analogWrite(motor_1, 0);
  analogWrite(motor_2, motor_speed + lr_speed_up);
  analogWrite(motor_3, 0);
  analogWrite(motor_4, motor_speed + lr_speed_up);
  delay(i * 100);
  stay(j);
}
void left(int k, int i, int j) { //Robot turn left
  motor_speed = k;

  Serial.print("Trun left: ");
  Serial.print(i * 100.0 / 1000.0);
  Serial.println("(s)");

  analogWrite(motor_1, motor_speed + lr_speed_up);
  analogWrite(motor_2, 0);
  analogWrite(motor_3, motor_speed + lr_speed_up);
  analogWrite(motor_4, 0);
  delay(i * 100);
  stay(j);
}
void stay(int i) {//Robot stop
  Serial.print("Stop: ");
  Serial.print(i * 100.0 / 1000.0);
  Serial.println("(s)");

  analogWrite(motor_1, 0);
  analogWrite(motor_2, 0);
  analogWrite(motor_3, 0);
  analogWrite(motor_4, 0);
  delay(i * 100);
}
