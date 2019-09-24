#include <Wire.h>
#include <Keyboard.h>

// �f�o�C�X�A�h���X(�X���[�u)
int E03_DEVICE_ADDRESS = 0x40;
int DISTANCE_ADDRESS = 0x5E;

//�X�e�b�p�[�ƃZ���T�̋������Ƃ̊��蓖�ėp
String key = "0";

//�{�^���s���ݒ�
const int LbtnPin = 7;
const int RbtnPin = 8;

//1�O�̃��[�v�̃{�^����ԕۑ��p
volatile int BLbtnState = HIGH;
volatile int BRbtnState = HIGH;

void setup() {
  Wire.begin();
  
  Keyboard.begin();

  pinMode(LbtnPin, INPUT_PULLUP);
  pinMode(RbtnPin, INPUT_PULLUP);
}

void loop(){
// �����v�Z�p     �@
  int dis[2];

// ����
  int distance;

// �{�^��
  int LbtnState = digitalRead(LbtnPin);
  int RbtnState = digitalRead(RbtnPin);

// �����Z���T����̎��ݒ�
  Wire.beginTransmission(E03_DEVICE_ADDRESS);   
  Wire.write(DISTANCE_ADDRESS);
  Wire.endTransmission();
// �����Z���T����̓ǂݎ��
  Wire.requestFrom(E03_DEVICE_ADDRESS, 2);
  for (int i=0; i< 2; i++){
    while (Wire.available() == 0 ){}
    dis[i] = Wire.read();
  }

// �����̌v�Z�@
  distance = dis[0]<<4;
  distance |= dis[1];
  distance = (distance / 16) / 4;

/* �����L�[�ݒ�
 * 28cm�ȏ�Ȃ�0
 * 23cm�ȏ�28cm�����Ȃ�1�܂���9
 * 18cm�ȏ�23cm�����Ȃ�2�܂���8
 * 13cm�ȏ�18cm�����Ȃ�3�܂���7
 * 8cm�ȏ�13cm�����Ȃ�4�܂���6
 * 8cm�����Ȃ�5���o��
 * 0����9�����ԂɃ��[�v�o��
 */
  if(distance >= 28){
    if(key == "9"){
      key = "0";
      Keyboard.print(key);
    }
  }
  if(distance < 28 && distance >= 23){
    if(key == "0"){
      key = "1";
      Keyboard.print(key);
    }
    else if(key == "8"){
      key = "9";
      Keyboard.print(key);
    }
  }
  if(distance < 23 && distance >= 18){
    if(key == "1"){
      key = "2";
      Keyboard.print(key);
    }
    else if(key == "7"){
      key = "8";
      Keyboard.print(key);
    }
  }
  if(distance < 18 && distance >= 13){
    if(key == "2"){
      key = "3";
      Keyboard.print(key);
    }
    else if(key == "6"){
      key = "7";
      Keyboard.print(key);
    }
  }
  if(distance < 13 && distance >= 8){
    if(key == "3"){
      key = "4";
      Keyboard.print(key);
    }
    else if(key == "5"){
      key = "6";
      Keyboard.print(key);
    }
  }
  if(distance < 8){
    if(key == "4"){
      key = "5";
      Keyboard.print(key);
    }
  }

// �{�^���L�[�ݒ�
  if(BLbtnState == HIGH){
    if(LbtnState == LOW){
      Keyboard.print("L");
    }
  }
  if(BRbtnState == HIGH){
    if(RbtnState == LOW){
      Keyboard.print("R");
    }
  }

// �{�^���̏�Ԃ̏�������
  BLbtnState = LbtnState;
  BRbtnState = RbtnState;
  
  delay(50);
  
}