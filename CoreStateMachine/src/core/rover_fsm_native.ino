const uint16_t STATE_DELAY = 1000;        // Time interval 
const uint8_t SENSORS = NULL;             // Entrada de sensores
const uint8_t JOYSTICK = NULL;            // Entrada de joystick
const uint8_t SWITCH_LAWNMOWER = NULL;    // Entrada de switch/boton activacion podadora
const uint8_t LAWNMOWER = NULL;           // Salida de podadora
const uint8_t MOTORS = NULL;              // Salida de motores

enum States {                             // Definicion de variable enum de la maquina de estado
  OFF,
  STOPPED,
  MOVING_FORWARD,
  PRUNING,
  MOVING_FORWARD_AND_PRUNING
};

States prior_state, state;


void stopped() {
  if (state != prior_state) {             // Si entramos al estado, hacer la inicializacion...
    prior_state = state;
    digitalWrite(LAWNMOWER, LOW);
    digitalWrite(MOTORS, LOW);
  }
  
  // Ejecutar tareas por estado
  
  // Evaluar la transicion de estados
  if (digitalRead(JOYSTICK) == HIGH) {
    state = MOVING_FORWARD;
  } else if (digitalRead(SWITCH_LAWNMOWER) == HIGH) {
    state = PRUNING;
  } else if (digitalRead(JOYSTICK) == HIGH && digitalRead(SWITCH_LAWNMOWER) == HIGH) {
    state = MOVING_FORWARD_AND_PRUNING;
  }
  
}

void pruning() {
  if (state != prior_state) {             // Si entramos al estado, hacer la inicializacion...
    prior_state = state;
    digitalWrite(LAWNMOWER, HIGH);
  }
  
  // Ejecutar tareas por estado
  
  // Evaluar la transicion de estados
  if (digitalRead(JOYSTICK) == HIGH) {
    state = MOVING_FORWARD_AND_PRUNING;
  }
  
  if (state != prior_state) {             // Si estamos dejando el estado, hacer "limpieza"...
    digitalWrite(LAWNMOWER, LOW);
  }

}

void movingForward() {
  if (state != prior_state) {             // Si entramos al estado, hacer la inicializacion...
    prior_state = state;
    digitalWrite(MOTORS, HIGH);
  }
  
  // Ejecutar tareas por estado
  
  // Evaluar la transicion de estados
  if (digitalRead(SENSORS) == HIGH) {
    state = STOPPED;
  }
  
  if (digitalRead(SWITCH_LAWNMOWER) == HIGH) {
    state = MOVING_FORWARD_AND_PRUNING;
  }
  
  if (state != prior_state) {             // Si estamos dejando el estado, hacer "limpieza"...
    digitalWrite(MOTORS, LOW);
  }
    
}

void movingForwardAndPruning() {
  if (state != prior_state) {             // Si entramos al estado, hacer la inicializacion...
    prior_state = state;
    digitalWrite(MOTORS, HIGH);
    digitalWrite(LAWNMOWER, HIGH);
  }
  
  // Ejecutar tareas por estado
  
  // Evaluar la transicion de estados
  if (digitalRead(SWITCH_LAWNMOWER) == LOW) {
    state = MOVING_FORWARD;
  } else if (digitalRead(JOYSTICK) == LOW || digitalRead(SENSORS) == HIGH) {
    state = PRUNING;
  } else if (digitalRead(JOYSTICK) == LOW && digitalRead(SWITCH_LAWNMOWER) == LOW) {
    state = STOPPED;
  }
  
  if (state != prior_state) {             // Si estamos dejando el estado, hacer "limpieza"...
    digitalWrite(MOTORS, LOW);
    digitalWrite(LAWNMOWER, LOW);
  }

}


void setup() {
  pinMode(SENSORS, INPUT);            // Configure SENSORS pin as a digital input
  pinMode(JOYSTICK, INPUT);           // Configure JOYSTICK pin as a digital input
  pinMode(SWITCH_LAWNMOWER, INPUT);   // Configure SW_LAWNMOWER pin as a digital input
  pinMode(MOTORS, OUTPUT);            // Configure MOTORS pin as a digital output
  pinMode(LAWNMOWER, OUTPUT);         // Configure LAWNMOWER pin as a digital output

  digitalWrite(LAWNMOWER, LOW);       // Set LAWNMOWER low initially
  digitalWrite(MOTORS, LOW);          // Set MOTORS low initially

  prior_state = OFF;
  state = STOPPED;

}

void loop() {
  switch (state) {
    case STOPPED:
      stopped();
      delay(STATE_DELAY);
      break;
    case PRUNING:
      pruning();
      delay(STATE_DELAY);
      break;
    case MOVING_FORWARD:
      movingForward();
      delay(STATE_DELAY);
      break;
    case MOVING_FORWARD_AND_PRUNING:
      movingForwardAndPruning();
      delay(STATE_DELAY);
      break;
  }
}























