  #include <Wire.h>
  #include <Keyboard.h>
  
  // �f�o�C�X�A�h���X(�X���[�u)
  int E03_DEVICE_ADDRESS = 0x40;
  int DISTANCE_ADDRESS = 0x5E;
  
  //�X�e�b�p�[�ƃZ���T�̋������Ƃ̊��蓖�ėp
  String key = "0";
  
  //�{�^���s���ݒ�
  const int LbtnPin = 7;
  const int RbtnPin = 5;
  
  //1�O�̃��[�v�̃{�^����ԕۑ��p
  volatile int BLbtnState = HIGH;
  volatile int BRbtnState = HIGH;
  
  int dist_step_old=9;  //������6�i�K1�O�̒l9�ŏ�����
  int dist_max=25;      //�����̍ő�l�ۑ��ϐ�25�ŏ�����
  int dist_min=10;      //�����̍ŏ��l�ۑ��ϐ�15�ŏ�����
  
  
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
    for (int i=0; i< 2; i++)   {
      while (Wire.available() == 0 ){}
      dis[i] = Wire.read();
    }
  
  // �����̌v�Z�@
    distance = dis[0]<<4;
    distance |= dis[1];
    distance = (distance / 16) / 4;
  
    Serial.println(distance);
  
  if(distance<dist_min) dist_min=distance; //min�l���X�V
  if(distance>dist_max && distance<40) dist_max=distance; //max�l���X�V
   if(distance>40) dist_max=28;
  
    
  
  /* �����L�[�ݒ�
  *  (dist_max-dist_min)/10��3,4,4,4,4,3����0�`5�̃X�e�b�v�Ɋ��蓖��
  */
    int distance_step;//������6�i�K�ۑ��ϐ�
    for(distance_step=0;distance_step<=5;distance_step++){
      if(distance < (distance_step*1+2)*(dist_max-dist_min)/8+dist_min)break;         
    }
    
    if(distance_step != dist_step_old){//�O�񑗐M�X�e�b�v�ƈقȂ鎞�̂ݏo��
      switch(distance_step){
        case 0:
        key = "0";
          break;
        case 1:
        key = "1";
          break;
        case 2:
        key = "2";
          break;
        case 3:
        key = "3";
          break;
        case 4:
        key = "4";
          break;
        case 5:
        key = "5";
          break;
      }
          Keyboard.print(key);
      dist_step_old=distance_step; //���M�X�e�b�v�̕ۑ�
    }
  
  // �{�^���L�[�ݒ�
    if(BLbtnState == HIGH){
      if(LbtnState == LOW){
        Keyboard.print("l");
      }
    }
    if(BRbtnState == HIGH){
      if(RbtnState == LOW){
        Keyboard.print("r");
      }
    }
  
  // �{�^���̏�Ԃ̏�������
    BLbtnState = LbtnState;
    BRbtnState = RbtnState;
    
    delay(100);
    
  }