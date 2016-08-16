void Led_setup() {
  pinMode(Mux_SIG, OUTPUT);
  digitalWrite(Mux_SIG, LOW);
}

void Led_change(int RLEDpin, int GLEDpin, bool RG, bool aTuneFin) {
  if (RG)
    Mux_switch(RLEDpin);
  else
    Mux_switch(GLEDpin);
  Led_setup();
  if (aTuneFin)
    digitalWrite(Mux_SIG, HIGH);
  else
    digitalWrite(Mux_SIG, LOW);
}

void Led_ON() {
  digitalWrite(Mux_SIG, HIGH);
}

void Led_OFF() {
  digitalWrite(Mux_SIG, LOW);
}
