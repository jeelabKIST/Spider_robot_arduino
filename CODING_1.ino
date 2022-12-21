int motor_speed = 120;//*** 거미로봇 속도 (120~220 정도로 설정) (낮을수록 느리고, 높을수록 빠름)
int lr_speed_up = 20;//***  거미로봇 좌회 우회 속도만 좀더 빠르게 하고싶을때 (좌우회전이 로봇 구조상 전후진보다 힘이더듬)


int move_time = 10;//*** 거미로봇 동작시간 (초)
int break_time = 10;//*** 거미로봇 휴식시간 (초)

int move_mode = 1;//*** 0 = 패턴동작 , 1 = 랜덤동작

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

  delay(5000);//5초 휴식
  Serial.println("loop 실행");
}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

void loop() {



  currentMillis = millis();
  if (currentMillis - lastMillis >= 100) {
    lastMillis = currentMillis;
  }



  if (move_mode == 0) {//패턴동작 모드
    move_pattern();
    if (run_time > move_time) {
      Serial.println("");
      Serial.print(move_time);
      Serial.println("초 이상 움직였습니다.");
      Serial.print(break_time);
      Serial.println("초 휴식합니다.");
      Serial.println("");
      for (int i = 0; i < break_time; i++) {
        Serial.print(".");
        delay(1000);
      }
      Serial.println("");
      run_time = 0;
    }
  } else {//랜덤동작 모드
    random_pattern();
    if (run_time > move_time) {
      Serial.println("");
      Serial.print(move_time);
      Serial.println("초 이상 움직였습니다.");
      Serial.print(break_time);
      Serial.println("초 휴식합니다.");
      Serial.println("");
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

  int move_time_r = random(5, 30);//*** 랜덤 움직임 시간 (0.5초 ~ 3.0초사이 랜덤)
  int stay_time_r = random(1, 10);//*** 랜덤 움직임 후 정지 시간 (0.1초 ~ 1.0초사이 랜덤)

  //motor_speed = random(100, 200);

  int r = random(1, 6);//1~5의값을 r변수에 저장
  // 랜덤값 r에 따라 전진 후진 좌회 우회 정지 중에서 선택
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
  Serial.print("----- ----- 실행횟수 : ");
  Serial.print(run_count);

  Serial.print("     실행시간 : ");
  Serial.print(run_time);
  Serial.println("초");
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
  Serial.print("----- ----- 실행횟수 : ");
  Serial.print(run_count);

  Serial.print("     실행시간 : ");
  Serial.print(run_time);
  Serial.println("초");
}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

void go(int k, int i, int j) { //거미로봇 전진
  motor_speed = k;

  Serial.print("전진: ");
  Serial.print(i * 100.0 / 1000.0);
  Serial.println("(초)");

  analogWrite(motor_1, 0);
  analogWrite(motor_2, motor_speed);
  analogWrite(motor_3, motor_speed);
  analogWrite(motor_4, 0);
  delay(i * 100);
  stay(j);
}
void back(int k, int i, int j) { //거미로봇 후진
  motor_speed = k;

  Serial.print("후진: ");
  Serial.print(i * 100.0 / 1000.0);
  Serial.println("(초)");

  analogWrite(motor_1, motor_speed);
  analogWrite(motor_2, 0);
  analogWrite(motor_3, 0);
  analogWrite(motor_4, motor_speed);
  delay(i * 100);
  stay(j);
}
void right(int k, int i, int j) { //거미로봇 제자리 우회전
  motor_speed = k;

  Serial.print("우회: ");
  Serial.print(i * 100.0 / 1000.0);
  Serial.println("(초)");

  analogWrite(motor_1, 0);
  analogWrite(motor_2, motor_speed + lr_speed_up);
  analogWrite(motor_3, 0);
  analogWrite(motor_4, motor_speed + lr_speed_up);
  delay(i * 100);
  stay(j);
}
void left(int k, int i, int j) { //거미로봇 제자리 좌회전
  motor_speed = k;

  Serial.print("좌회: ");
  Serial.print(i * 100.0 / 1000.0);
  Serial.println("(초)");

  analogWrite(motor_1, motor_speed + lr_speed_up);
  analogWrite(motor_2, 0);
  analogWrite(motor_3, motor_speed + lr_speed_up);
  analogWrite(motor_4, 0);
  delay(i * 100);
  stay(j);
}
void stay(int i) {//거미로봇 정지
  Serial.print("정지: ");
  Serial.print(i * 100.0 / 1000.0);
  Serial.println("(초)");

  analogWrite(motor_1, 0);
  analogWrite(motor_2, 0);
  analogWrite(motor_3, 0);
  analogWrite(motor_4, 0);
  delay(i * 100);
}
