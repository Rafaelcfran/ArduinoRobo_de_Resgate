class DCMotor {
    int spd = 255, pin1, pin2, enable;
   
    // Armazena se o motor já está se movendo
 
public:
    void Pinout(int in1, int in2, int enb) {
        pin1 = in1;
        pin2 = in2;
        enable = enb;
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        pinMode(enable, OUTPUT);
    }
 
    void Forward(int speed) { 
          spd = speed;
          digitalWrite(pin1, LOW);
          digitalWrite(pin2, HIGH);
          analogWrite(enable, spd);
           delay(25);

           digitalWrite(pin1, LOW);
           digitalWrite(pin2, LOW);
           analogWrite(enable, spd);
            delay(25);

    }

    void Backward(int speed) {
          spd = speed;
          digitalWrite(pin1, HIGH);
          digitalWrite(pin2, LOW);
          analogWrite(enable, spd);
            delay(50);
    }

    void Stop() {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
      
    }
};

DCMotor Motor1, Motor2;
     //Motor 2 = motor esquerdo 
     //Motor 1 = motor direito  

void forward(){
   Motor1.Forward(255);
   Motor2.Forward(255);
}

void curvadir(){
     // Só direito detecta a linha → virar para direita
  Motor1.Forward(255); 
  // direito para frente
  Motor2.Stop(); // esquerdo para trás
}

void curvaesq(){
    // Só esquerdo detecta a linha → virar para esquerda
  Motor2.Forward(255);  // esquerdo para frente
  Motor1.Stop(); // direito para trás 
  }

const int pinoTrig = 10; // Pino do Trigger
const int pinoEcho = 11; // Pino do Echo
unsigned long UScontadorMillis = millis();
unsigned long UScontadorMicros = micros();
float distancia;

int leituraIRe, leituraIRd,leituraIRpontaD,leituraIRpontaE;
int pinoIRpontaE = 12, pinoIRpontaD = 11, pinoIRe =2  ,pinoIRd =3;
bool flagdir = false, flagesq = false;
unsigned long IRcontadorMillis = millis();


void setup() {
    Motor1.Pinout(5, 4,6);
    Motor2.Pinout(7, 8,9);
    Serial.begin(9600);
    // pinMode(pinoEcho, INPUT);
    // pinMode(pinoTrig, OUTPUT);
    // digitalWrite(pinoTrig, LOW);
}

void loop() {
  /*  
    Motor1.Forward();   //nao funciona
    Motor2.Forward(); //motor funciona
    delay(2000);
    Motor1.Backward();  //motor funciona
    Motor2.Backward(); // Nao funciona
    delay(2000);
*/
    
  
//    if((millis() - UScontadorMillis) >= 1000 && digitalRead(pinoTrig) == LOW) {
//        digitalWrite(pinoTrig, HIGH);
//        UScontadorMillis = millis();
//        UScontadorMicros = micros();
//    }
//    if((micros() - UScontadorMicros) >= 10 && digitalRead(pinoTrig) == HIGH) {
//        digitalWrite(pinoTrig, LOW);
//        float deltaT = pulseIn(pinoEcho,HIGH);
//        distancia = deltaT * 0.034 / 2 ;
//        //Serial.print("Distancia em cm: ");
//        //Serial.println(distancia);
//    }
       
        leituraIRe = digitalRead(pinoIRe);
        leituraIRpontaD = digitalRead(pinoIRpontaD);
        leituraIRpontaE = digitalRead(pinoIRpontaE);
        leituraIRd = digitalRead(pinoIRd);

      if(leituraIRpontaD == HIGH){
        flagdir = true;
      }
      
          
      if(leituraIRpontaE == HIGH) flagesq = true;

     if((millis() - IRcontadorMillis) >= 100){
         Serial.print("leitura da infra da flag esquerda é " );
        Serial.println(leituraIRpontaE);
       Serial.print("leitura da flag esquerda é " );
        Serial.println(flagesq);
        Serial.print("leitura do infra esquerdo: ");
        Serial.println(leituraIRe);
          Serial.print("leitura do infra da flag direita é " );
        Serial.println(leituraIRpontaD);
         Serial.print("leitura da flag direito é " );
        Serial.println(flagdir);
        Serial.print("leitura do infra direito: ");
        Serial.println(leituraIRd);
        Serial.println(" ");
       IRcontadorMillis = millis();
     }

      if(flagdir == true){
           curvaesq();
      }
      if (flagesq == true){
           curvadir();
      }
  
      if((leituraIRd == LOW && leituraIRe == LOW) && (flagdir == false && flagesq == false)){
      
          forward();
      }
      
      if (leituraIRe == HIGH) {
        // detecta para fazer curva para a esquerda
          flagdir = false;
          if( flagesq == false)  curvadir();
        
          
      } 
      if ( leituraIRd == HIGH ) {
        // detecta para fazer curva para a direita
          flagesq = false;
          if(flagdir == false) curvaesq();
          
      }
     
      
}
