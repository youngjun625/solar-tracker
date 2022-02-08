//와이어 모터 설정
#define dirSun 2
#define stepSun 3
#define enaSun 4

//수직모터 설정
#define dirCyl 6
#define stepCyl 7
#define enaCyl 8

//조도 센서 4개 설정
int ldrlt = A0; // top left blue
int ldrrt = A1; // top rigtn  yellow  
int ldrld = A2; // down left  green
int ldrrd = A3 ; //down rigt  purple

//모터 최대값 설정을 위해 모터 현재 회전각도 추적 변수 설정
int cylPos = 0;
int sunPos = 0;

void setup() {
  
  Serial.begin(9600);
  //step = PULSE 핀, LOW HIGH한번씩 실행 = 스탭 실행
  //dir = DIRERCTION 핀, LOW = 시계방향 회전, HIGH = 반시계 방향 회전.
  //ena = //ENABLE 핀, LOW = 모터 활성, HIGH = 모터 비활성
  pinMode(stepSun, OUTPUT); 
  pinMode(dirSun, OUTPUT); 
  pinMode(enaSun, OUTPUT); 
  pinMode(stepCyl, OUTPUT);
  pinMode(dirCyl, OUTPUT);
  pinMode(enaCyl, OUTPUT);
  
  digitalWrite(enaSun, LOW); //와이어 모터 활성
  digitalWrite(enaCyl, LOW); //수직 모터 활성
  
}

void loop() {
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt
  
  int avt = (lt + rt) / 2; //위쪽 조도 센싱
  int avd = (ld + rd) / 2; //아래쪽 조도 센싱
  int avl = (lt + ld) / 2; //왼쪽 조도 센싱
  int avr = (rt + rd) / 2; //오른쪽 조도 센싱

  //모든 조도 센서의 값이 500이하일때 모터 비활성화
  if (avt < 500 && avd < 500 && avl < 500 && avr < 500 )
  {
    digitalWrite(enaSun, HIGH);
    digitalWrite(enaCyl, HIGH);
  }
  //그렇지 않으면 모터 구동
  else
    {

      if (avt > avd) //위쪽 조도 값이 더 클경우 와이어 모터를 반시계 방향으로 회전 시켜 아래로 내림
      {
        digitalWrite(enaSun, LOW); //모터 활성화
        digitalWrite(dirSun, HIGH); //모터 방향 조절
        if (sunPos <= 1600 && sunPos > -1600) //스텝을 조정하여 3200 스텝 = 1바퀴,+180도와 -180도를 최대 각도로 설정
        {
          digitalWrite(stepSun, HIGH);//모터 스텝 실행
          delayMicroseconds(500);
          digitalWrite(stepSun, LOW);
          delayMicroseconds(500);
          sunPos -= 32;
         }           
        digitalWrite(enaSun, HIGH); //모터 비활성화
      }
      else if (avt < avd) //아래쪽 조도 값이 더 클 경우 와이어 모터를 시계 방향으로 회전 시켜 위로 올림
      {
        digitalWrite(enaSun, LOW); //모터 활성화
        digitalWrite(dirSun, LOW); //모터 방향 조절
        if (sunPos <= 1600 && sunPos > -1600) //스텝을 조정하여 3200 스텝 = 1바퀴,+180도와 -180도를 최대 각도로 설정
        {
          digitalWrite(stepSun, HIGH);//모터 스텝 실행
          delayMicroseconds(500);
          digitalWrite(stepSun, LOW);
          delayMicroseconds(500);
          sunPos += 32;
         }    
        digitalWrite(enaSun, HIGH); //모터 비활성화     
      }   
      if (avl < avr) //오른쪽 조도 값이 더 클 경우 수직축 모터를 반시계 방향으로 돌려 오른쪽으로 회전
      {
        digitalWrite(enaCyl, LOW); //모터 활성화 
        digitalWrite(dirCyl, HIGH); //모터 방향 조절
        if (cylPos <= 1600 && cylPos > -1600) //스텝을 조정하여 3200 스텝 = 1바퀴,+180도와 -180도를 최대 각도로 설정
        {
          digitalWrite(stepCyl, HIGH); //모터 스텝 실행
          delayMicroseconds(500);
          digitalWrite(stepCyl, LOW);
          delayMicroseconds(500);
          cylPos -= 32;
         }        
        digitalWrite(enaCyl, HIGH); //모터 비활성화
      }
      else if (avl > avr) //왼쪽 조도 값이 더 클 경우 수직축 모터를 시계 방향으로 돌려 왼쪽으로 회전
      {
        digitalWrite(enaCyl, LOW); //모터 활성화 
        digitalWrite(dirCyl, LOW); //모터 방향 조절
        if (cylPos <= 1600 && cylPos > -1600) //스텝을 조정하여 3200 스텝 = 1바퀴,+180도와 -180도를 최대 각도로 설정
        {
          digitalWrite(stepCyl, HIGH); //모터 스텝 실행
          delayMicroseconds(500);
          digitalWrite(stepCyl, LOW);
          delayMicroseconds(500);
          cylPos += 32;
         }
        digitalWrite(enaCyl, HIGH); //모터 비활성화
      }
    }

  //조도값 모니터링을 위한 시리얼 프린트
  Serial.print("avt "); Serial.println(avt);
  Serial.print("avd "); Serial.println(avd);
  Serial.print("avr "); Serial.println(avr);
  Serial.print("avl "); Serial.println(avl);

  //딜레이 함수를 사용하여 모터 속도 조절
  delay(100);  
}