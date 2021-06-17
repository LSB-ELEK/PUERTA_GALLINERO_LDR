#define FC_UP 12
#define FC_DOWN 11
#define SELECT 10
#define UP 9
#define DOWN 8
#define LDR A1

#define RELE1 2
#define RELE2 3

#define valor_max 650
#define valor_min 450

bool fc_up = 0;
bool fc_down = 0;
bool select = 0;
bool up = 0;
bool down = 0;
int ldr = 0;

bool primera = 1;
bool finales = 0;

int estado_man = 0;
int estado_aut = 0;


void setup() {
  pinMode(FC_UP, INPUT);
  pinMode(FC_DOWN, INPUT);
  pinMode(SELECT, INPUT);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  //Serial.begin(9600);
  
}

void loop() {
  fc_up = digitalRead(FC_UP);
  fc_down = digitalRead(FC_DOWN);
  select = digitalRead(SELECT);
  up = !digitalRead(UP);
  down = !digitalRead(DOWN);
  ldr = analogRead(LDR);

  //Serial.print("FC_UP: \t");Serial.println(fc_up);
  //Serial.print("FC_DOWN: \t");Serial.println(fc_down);
  //Serial.print("SELECT: \t");Serial.println(select);
  //Serial.print("UP: \t");Serial.println(up);
  //Serial.print("DOWN: \t");Serial.println(down);

  if((millis()<5000)&&(primera)&&(select)){
    if(!fc_up && !fc_down){
      while(!finales){
        if(fc_up || fc_down){
          finales = 1;
        }
        fc_up = digitalRead(FC_UP);
        fc_down = digitalRead(FC_DOWN);
        Serial.print("FC_UP: \t");Serial.println(fc_up);
        Serial.print("FC_DOWN: \t");Serial.println(fc_down);
        Serial.print("Finales: \t");Serial.println(finales);
        if((ldr>valor_max)&&(!fc_up)){
          SUBE();
        }else if((ldr<valor_min)&&(!fc_down)){
          BAJA();
        }
        Serial.println("en while");
      } 
    }
    Serial.println("PARAR");
    PARA();
    primera = 0;
  }
  
  if(select){
    estado_aut = 0;
    Serial.print("MANUAL");
      switch(estado_man){
        case 0:
          if(up && !fc_up){
            estado_man = 1;
          }else if(down && !fc_down){
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
  }else{
    estado_man = 0;
    Serial.print("AUTOMATICO");
    switch(estado_aut){
      case 0:
        PARA();
        if((ldr>valor_max)&&(!fc_up)){
          estado_aut = 1;
        }
        if((ldr<valor_min)&&(!fc_down)){
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
  Serial.print("\n==============\n\n");
  delay(100);
}

void SUBE(){
  digitalWrite(RELE1, LOW);
  digitalWrite(RELE2, HIGH);  
}
void BAJA(){
  digitalWrite(RELE1, HIGH);
  digitalWrite(RELE2, LOW);
}
void PARA(){
  digitalWrite(RELE1, HIGH);
  digitalWrite(RELE2, HIGH);
}
