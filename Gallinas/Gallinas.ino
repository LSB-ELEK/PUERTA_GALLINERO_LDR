#define FC_UP D12
#define FC_DOWN D11
#define SELECT D10
#define UP D9
#define DOWN D8
#define LDR A1

bool fc_up = 0;
bool fc_down = 0;
bool select = 0;
bool up = 0;
bool down = 0;
int ldr = 0;

int estado_man = 0;
int estado_aut = 0;

void setup() {
  pinMode(FC_UP, INPUT);
  pinMode(FC_DOWN, INPUT);
  pinMode(SELECT, INPUT);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  fc_up = !digitalRead(FC_UP);
  fc_down = !digitalRead(FC_DOWN);
  select = digitalRead(SELECT);
  up = digitalRead(UP);
  down = digitalRead(DOWN);
  ldr = analogRead(LDR);
  
  if(select){
    if(up){
      Serial.print("MANUAL");
      switch(estado_man){
        case 0:
          if(up){
            estado_man = 1;
          }else if(down){
            estado_man = 2;
          }
          PARA();
          Serial.println("\t 0");
          break;

        case 1:
          SUBE();
          if(fc_up){
            estado_man = 0;
            PARA();
          }
          Serial.println("\t 1");
          break;
        case 2:
          BAJA();
          if(fc_down){
            estado_man = 0;
            PARA();
          }
          Serial.println("\t 2");
          break;        
      }
    }
  }else{
    Serial.print("AUTOMATICO");
    switch(estado_aut){
      case 0:
        PARA();
        if((ldr>650)&&(!fc_up)){
          estado_aut = 1;
        }
        if((ldr<400)&&(!fc_down)){
          estado_aut = 2;
        }
        Serial.print("\t 0");
        break;
      case 1:
        SUBE();
        if(fc_up){
          estado_aut = 0;
          PARA();
        }
        Serial.print("\t 1");
        break;
      case 2:
        BAJA();
        if(fc_down){
          estado_aut = 0;
          PARA();
        }
        Serial.print("\t 2");
        break;
    }
    Serial.print("\t");Serial.println(ldr);
    
  }
  delay(100);
}

void SUBE(){
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);  
}
void BAJA(){
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
}
void PARA(){
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}
